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
  
  or_sr(0x18);		/* CPU off, GIE on */
}

void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN; // Sets green to on
  } else {
    P1OUT &= ~LED_GREEN; // Sets green to off
  }
}

// blink state machine
static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++; // (Moves along the time interval)
  if (blinkCount >= blinkLimit) { // Once the time interval is reached
    blinkCount = 0;  // (Rests to the beginning of the time interval)
    greenControl(1); // (Sets green to on)
  } else
    greenControl(0); // (Sets green to off)
}

void oncePerSecond()    // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;        // reduce duty cycle (lengthens time interval)
  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7. (time interval can be too large)
    blinkLimit = 0;     // Resets time interval to 0 (very small).
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++; // (Increments at a rate of 1/250th of a second)
  if (secondCount >= 250) { // once each second
    secondCount = 0; // (Resets each second)
    oncePerSecond(); // (Updates the limit of the time interval)
  }
}

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}


void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking   
  timeAdvStateMachines();
} 

