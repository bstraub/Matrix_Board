void initTimer()
{
  cli();
  
  TCCR2A |= (1 << WGM21); //turn on CTC mode for timer 2
  TCCR2B |= PRESCALER; //set up prescaler
  OCR2A = OCR_VALUE; //set up compare register
  TIMSK2 |= (1 << OCIE2A); //enable timer interrupt
  
  sei();
}

/// ISR for the timer interrupt (2.404kHz)
ISR(TIMER2_COMPA_vect)
{
  if (curRow == -1 || curRow == NUM_COLS-1)
    drawDisplayStart();
  else
    drawNextRow();
}
