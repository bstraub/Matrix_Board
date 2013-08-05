#include "MBheader.h"
#include <TouchScreen.h>

char curRow;
byte colorMatrix[8][24];
byte switchState;
TouchScreen ts = TouchScreen(pTS0, pTS1, pTS2, pTS3, TS_RESISTANCE); //!! may need to change these pins

void setup()
{
  initDisplay();
  testLED();
  initInput();
}

void loop()
{
  checkBtn();
  Point p = ts.getPoint();
  if( p.z > ts.pressureThreshhold )
  {
    checkSwitch();
    changeScreen(p.x, p.y);
  }
}



void changeScreen( int x_in, int y_in )
{
  int x, y;
  byte xIndex;
  byte xBit;
  byte xBitmask;
  
  x = map_r( x_in, MAP_IN_X_LO, MAP_IN_X_HI, MAP_OUT_X_LO, MAP_OUT_X_HI );
  y = map_r( y_in, MAP_IN_Y_LO, MAP_IN_Y_HI, MAP_OUT_Y_LO, MAP_OUT_Y_HI );
  
  xIndex = x && 0x7;
  xBit = 6 - ((x >> 2) && 0x6); // should be 0, 2, 4, or 6
  xBitmask = (switchState && 0x3) << xBit; // should be 0x01, 0x04, 0x10, or 0x40 times 00, 01, 10, or 11
  
  if ((switchState & 0x4) == 0) //erase mode
  {
    colorMatrix[xIndex][y] &= (~xBitmask); //clear bits
  } else {
    colorMatrix[xIndex][y] |= (xBitmask); //set bits
  }
}
