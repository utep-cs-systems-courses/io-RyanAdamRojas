//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int blinkLimit = 10;  // duty cycle = 1/blinkLimit
int blinkGreenCount = 10;  // cycles 0...blinkLimit-1
int blinkRedCount = 10;  // cycles 0...blinkLimit-1
int tick = 1000; // state var representing repeating time 0…1s
int limitIsIncreasing = 0;

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking
  blinkGreenCount ++;
  if (blinkGreenCount >= blinkLimit) {   // on for 1 interrupt period
    blinkGreenCount = 0;
    P1OUT |= LED_GREEN;
  } else {		                    // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;
  }

  blinkRedCount++;
  if (blinkRedCount >= (8 - blinkLimit)) { // on for 1 interrupt period
    blinkRedCount = 0;
    P1OUT |= LED_RED;
  } else {		                    // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_RED;
  }

  // measure a second
  tick ++;
  if (tick >= 25) {  // 250 roughly equals one second
    tick = 0;

    if (limitIsIncreasing == 1)   // reduce duty cycle
        blinkLimit ++;
    else if (limitIsIncreasing == 0)
        blinkLimit --;

    if (blinkLimit >= 8)         // but don't let duty cycle go below 1/7.
        limitIsIncreasing = 0;
    else if (blinkLimit <= 0)
        limitIsIncreasing = 1;
    }
/*
make clean
make all
make load

*/
}