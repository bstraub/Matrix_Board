#include "MBheader.h"

void initInput()
{
  pinMode( pSw, INPUT );
  pinMode( pBtn, INPUT );
}

//sets switch state to 0-7, bit 0 = green, bit 1 = red, bit 2 = mode
void checkSwitch()
{
  int raw = analogRead(pSw); // ab c000 0000
  switchState = ((raw+0x40)>>6);
}

boolean checkBtn()
{
  static long holdStart = 0;
  static boolean holding = false;
  
  boolean reading = digitalRead(pBtn);
  if (reading)
  {
    if (!holding)
    {
      holding = true;
      holdStart = millis();
      return false;
    } else if ((millis()-holdStart) >= FILL_BTN_HOLD)
    {
      return true;
    }
  } else {
    holding = false;
    return false;
  }
  return false;
}

