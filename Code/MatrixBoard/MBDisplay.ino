#include "MBheader.h"


/// set up all the pins and whatnot
void initDisplay()
{
  curRow = -1;
  
  pinMode(pG0, OUTPUT);
  pinMode(pR0, OUTPUT);
  pinMode(pG1, OUTPUT);
  pinMode(pR1, OUTPUT);
  pinMode(pG2, OUTPUT);
  pinMode(pR2, OUTPUT);
  pinMode(pG3, OUTPUT);
  pinMode(pR3, OUTPUT);
  
  pinMode(pClk0, OUTPUT);
  pinMode(pClk1, OUTPUT);
  pinMode(pEn,   OUTPUT);
  pinMode(pSync, OUTPUT);
  
  digitalWrite(pEn, HIGH); //disable SR outputs
  digitalWrite(pClk0, LOW);
  digitalWrite(pClk1, LOW);
  digitalWrite(pSync, LOW);
  
  PORTSR = 0xFF;
  //clear out regs
  for(char c = 0; c < 8; c++)
  {
    PULSE(pClk0);
    PULSE(pClk1);
  }
  
  for(char c = 0; c < 8; c++)
  {
    for(char r = 0; r < 24; r++)
    {
      colorMatrix[c][r] = 0;
    }
  }
}

/// starts drawing the display; provides sync pulse and first row
void drawDisplayStart()
{
  digitalWrite( pEn, HIGH );
  digitalWrite( pSync, HIGH ); //start sync pulse
  PULSE( pClk1 ); //clock in the sync pulse
  digitalWrite( pSync, LOW );
  
  curRow = 0;
  for (char curCol = 0; curCol < NUM_COLS; curCol++)
  {
    PORTSR = colorMatrix[curCol][curRow];
    PULSE(pClk0);
  }
  PULSE(pClk1);
  digitalWrite(pEn,LOW);
}

/// draw the next row of the matrix
void drawNextRow()
{
  curRow++;
  for (char curCol = 0; curCol < NUM_COLS; curCol++)
  {
    PORTSR = colorMatrix[curCol][curRow];
    PULSE(pClk0);
  }
  PULSE(pClk1);
}

/// Test all the colors of the screen
void testLED()
{
  
  digitalWrite(pEn, LOW);
  //LIGHT UP GREEN
  PORTSR = 0xAA;
  digitalWrite(pSync, HIGH);
  for(char c = 0; c < 8; c++) {
    PULSE(pClk0);
    PULSE(pClk1);
  }
  PULSE(pClk1);
  
  delay(1000);
  
  //LIGHT UP RED
  PORTSR = 0x55;
  for(char c = 0; c < 8; c++) {
    PULSE(pClk0);
    PULSE(pClk1);
  }
  PULSE(pClk1);
  
  delay(1000);
  
  //LIGHT UP BOTH
  PORTSR = 0x00;
  for(char c = 0; c < 8; c++) {
    PULSE(pClk0);
    PULSE(pClk1);
  }
  PULSE(pClk1);
  
  delay(1000);
  
  //TURN OFF
  PORTSR = 0xFF;
  for(char c = 0; c < 8; c++) {
    PULSE(pClk0);
    PULSE(pClk1);
  }
  PULSE(pClk1);
  digitalWrite(pEn, HIGH);
}
