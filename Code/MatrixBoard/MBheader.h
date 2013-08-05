#ifndef MBHEADER_H
#define MBHEADER_H

#include "Arduino.h"

///////////////////////
// PINS
///////////////////////
typedef const byte pin;
pin pG0    = 0;
pin pR0    = 1;
pin pG1    = 2;
pin pR1    = 3;
pin pG2    = 4;
pin pR2    = 5;
pin pG3    = 6;
pin pR3    = 7;
//pin 8 unused
pin pClk0  = 9;
pin pClk1  = 10;
pin pEn    = 11;
pin pSync  = 12;
pin pTS0   = A0;
pin pTS1   = A1;
pin pTS2   = A2;
pin pTS3   = A3;
pin pBtn   = A4;
pin pSw    = A5;

#define PORTSR PORTD

///////////////////////
// CONSTANTS
///////////////////////
const byte PRESCALER = (1 << CS21) | (1 << CS20); //aka prescaler of 32 to get 500kHz
const byte OCR_VALUE = 208; //208 @ 500kHz = 2.404kHz

#define NUM_COLS 8
#define NUM_ROWS 24

#define FILL_BTN_HOLD 400 //in ms, time you must hold down fill btn to fill

#define TS_RESISTANCE 300 //!! measure and update

#define MAP_IN_X_LO 0    //!! these values will likely
#define MAP_IN_X_HI 1023    // need tweaking
#define MAP_IN_Y_LO 0
#define MAP_IN_Y_HI 1023
#define MAP_OUT_X_LO 0
#define MAP_OUT_X_HI 31
#define MAP_OUT_Y_LO 0
#define MAP_OUT_Y_HI 23

///////////////////////
// MACROS
///////////////////////
#define PULSE(x)  digitalWrite(x,HIGH); digitalWrite(x,LOW)



///////////////////////
// FUNCTIONS
///////////////////////

// this is a copy of the built-in Arduino "map" function, but altered to round instead of truncate
long map_r(long x, long in_min, long in_max, long out_min, long out_max)
{
  return ((((((x - in_min) * (out_max - out_min)) << 1) / (in_max - in_min)) + 1) >> 1) + out_min;
}



#endif
