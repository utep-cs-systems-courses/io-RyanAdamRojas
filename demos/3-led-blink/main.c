//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

// global state var to count time
int tick = 0;
const int cycle = 50;
int interval = 0;

int main(void) {
    P1DIR |= LEDS;
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */

  or_sr(0x18);			/* CPU off, GIE on */
}

void on_()
{
    P1OUT |= LED_GREEN;
    P1OUT |= LED_RED;
}

void off()
{
    P1OUT &= ~LED_GREEN;
    P1OUT &= ~LED_RED;
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts (ticks) per second */
{
    // Code below blinks SOS
    tick ++;
    if (tick == cycle) {
        interval ++;
        tick = 0;
    }
switch (interval) {
        // S: ... (dot-dot-dot)
        case 1: on_(); break;  // Dot
        case 2: off(); break;
        case 3: on_(); break;  // Dot
        case 4: off(); break;
        case 5: on_(); break;  // Dot
        case 6: off(); break;

        // O: --- (dash-dash-dash)
        case 9: on_(); break;  // Dash (Start after 2 cycles of space)
        case 12: off(); break;
        case 13: on_(); break; // Dash
        case 16: off(); break;
        case 17: on_(); break; // Dash
        case 20: off(); break;

        // S: ... (dot-dot-dot)
        case 23: on_(); break; // Dot (Start after 2 cycles of space)
        case 24: off(); break;
        case 25: on_(); break; // Dot
        case 26: off(); break;
        case 27: on_(); break; // Dot
        case 28: off(); break;

        // Reset interval after 7 cycles of space (word pause)
        case 45: interval = 0; break; // Reset after 7 cycles of space

        default: break;
    }
}
/*
make clean
make all
make load

*/