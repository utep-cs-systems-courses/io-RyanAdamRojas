//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN; // Turns on
  P1OUT |= LED_RED;   // Turns on
  // To turn off use "P1OUT &= ~LED_..."
  
  or_sr(0x18);		/* CPU off, GIE on [General Interrupt Enable]*/
}