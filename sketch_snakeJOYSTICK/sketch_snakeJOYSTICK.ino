#include "LedControl.h"

/*
Snake Arduino:
  - LED MATRIX 8 x 8
  - JOYSTICK
  */

// LED MATRIX PINS
const int DIN = 12;
const int CS = 11;
const int CLK = 10;

// JOYSTICK PINS
const int XAXIS = 0;
const int YAXIS = 1;
const int SWITCH = 2;

LedControl lc = LedControl(DIN,CLK,CS,1);
              
/* snake initilize */             
int x = 0;
int y = 0;
int food_x = rand() % 8;
int food_y = rand() % 8;
int length = 3;
int c = 0;
/* 64 is max length for 8 x 8 MATRIX */
int coordinates[64][2];

//movement
boolean up = false;
boolean down = false;
boolean right = true;
boolean left = false;

void reset() {
  x = 0;
  y = 0;
  length = 3;
  c = 0;
  up = false;
  down = false;
  right = true;
  left = false;
  delay(500);
}


void setup() {
  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH);
  Serial.begin(9600);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  /* start position */
  //setPoint(x,y);
  lc.setLed(0,x,y,true);
  
}


void loop() {
  int xAxis = analogRead(XAXIS);
  int yAxis = analogRead(YAXIS);
  
  //user input
   if (xAxis > 600 && left == false) {
    down = false;
    up = false;
    left = false;
    right = true;
  } else if (xAxis < 400 && right == false) {
    down = false;
    up = false;
    left = true;
    right = false;
  } else if (yAxis > 600 && up == false) {
    down = true;
    up = false;
    left = false;
    right = false;
  } else if (yAxis < 400 && down == false) {
    down = false;
    up = true;
    left = false;
    right = false;
  }
  
  if (right == true) {
    x++;
  } else if (left == true) {
    x--;
  } else if (down == true) {
    y++;
  } else if (up == true) {
    y--;
  }
   //check boarder
  if (x > 7) {
    x = 0;
  } 
  if (x < 0) {
    x = 7;
  }
  
  if (y > 7) {
    y = 0;
  } 
  if (y < 0) {
    y = 7;
  }
  //check if snake hits tail
 for (int i = 0; i < length; i++) {
   int i_x = coordinates[i][0];
   int i_y = coordinates[i][1];
   if (x == i_x && y == i_y) {
     reset();
   }
 }
  
  if (x == food_x && y == food_y) {
    food_x = rand() % 8;
    food_y = rand() % 8;
    length++;
    coordinates[length-1][0] = x;
    coordinates[length-1][1] = y;
  }
  
  coordinates[c][0] = x;
  coordinates[c][1] = y;
  
  c++;
  if (c >= length) {
    c = 0;
  }
  
  
  
  lc.clearDisplay(0);
  
  for (int i = 0; i < length; i++) {
    int i_x = coordinates[i][0];
    int i_y = coordinates[i][1];
    lc.setLed(0,i_y,i_x,true);
  }
  
  lc.setLed(0,food_y, food_x, true);
  
   if (digitalRead(SWITCH) == LOW) {
     reset();
   }
 
   //FPS
  delay(130);
  
}
