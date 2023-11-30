#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

int SECOND = 256;
int tick = 0;
int count = 0;
int i = 0;
char *californiaLove[] = {
        "C-4", "C-4", "C-4", "---",  "E-4", "E-4", "---", "---",  "G-4", "G-4", "G-4", "---",  "G-4", "G-4", "G-4", "G-4",
        "G-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "C-4", "---", "---", "---",
        "C-4", "C-4", "C-4", "---",  "C-4", "---", "---", "---",  "B-4", "B-4", "B-4", "B-4",  "B-4", "---", "---", "---",
        "C-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",

        "C-4", "C-4", "C-4", "---",  "E-4", "E-4", "---", "---",  "G-4", "G-4", "G-4", "---",  "G-4", "G-4", "G-4", "G-4",
        "G-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "C-4", "---", "---", "---",
        "C-4", "C-4", "C-4", "---",  "C-4", "---", "---", "---",  "B-4", "B-4", "B-4", "B-4",  "B-4", "---", "---", "---",
        "C-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",

//        "G-4", "G-4", "G-4", "---",  "G-4", "G-4", "G-4", "---",  "E-4", "E-4", "E-4", "---",  "E-4", "E-4", "E-4", "E-4",
//        "D-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "C-4", "---", "---", "---",
//        "C-4", "C-4", "C-4", "---",  "C-4", "---", "---", "---",  "B-4", "B-4", "B-4", "B-4",  "B-4", "---", "---", "---",
//        "C-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---"

//        "C-4", "C-4", "C-4", "---",  "E-4", "E-4", "---", "---",  "G-4", "G-4", "G-4", "---",  "G-4", "G-4", "G-4", "G-4",
//        "G-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "C-4", "---", "---", "---",
//        "C-4", "C-4", "C-4", "---",  "C-4", "---", "---", "---",  "B-4", "B-4", "B-4", "B-4",  "B-4", "---", "---", "---",
//        "C-4", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",  "---", "---", "---", "---",

    };
int note_values[] =
    {
      39510,
      37293,
      35200,
      33224,
      31359,
      29599,
      27938,
      26370,
      24890,
      23493,
      22174,
      20930,
      19755,
      18646,
      17600,
      16612,
      15679,
      14799,
      13969,
      13185,
      12445,
      11746,
      11087,
      10465,
       9877,
       9323,
       8800,
       8306,
       7839,
       7399,
       6984,
       6592,
       6222,
       5873,
       5543,
       5232,
       4938,
       4661,
       4400,
       4153,
       3920,
       3699,
       3492,
       3296,
       3111,
       2936,
       2771,
       2616,
       2469,
       2330,
       2200,
       2076,
       1960,
       1850,
       1746,
       1648,
       1555,
       1468,
       1385,
       1308,
       1234,
       1165,
       1100,
       1038,
        980,
        925,
        873,
        824,
        777,
        734,
        693,
        654,
        617,
        582,
        550,
        519,
        490,
        462,
        436,
        412,
        388,
        367,
        346,
        327,
        308,
        291,
        275,
        259,
        245,
        231,
        218,
        206,
        194,
        183,
        173,
        163
    };

int to_frequency_of(int frequency) {
    return frequency/2;
}

int note(const char *key) {
    // Design choice, key is formatted as [letter, if-sharp, octave] like in 317"

    // Converts string to integer (ASCII 45)
    int keycode = 0;
    if (key[0] != 45) {                 // If not '-' (ASCII 45)
        keycode = (key[0] - 64) * 100;  // Converts letters A-G to numbers 1-7 (ASCII)
    if (key[1] == '#')                  // Where natural ('-' = 0) and sharp ('#' = 1)
            keycode += 10;
    keycode += key[2] - 48;
       // Parses integer
    }
    switch (keycode) {
        case   0: return     0; // Pause

        case 301: return 39510; // C-1
        case 311: return 37293; // C#1
        case 401: return 35200; // D-1
        case 411: return 33224; // D#1
        case 501: return 31359; // E-1
        case 601: return 29599; // F-1
        case 611: return 27938; // F#1
        case 701: return 26370; // G-1
        case 711: return 24890; // G#1
        case 101: return 23493; // A-1
        case 111: return 22174; // A#1
        case 201: return 20930; // B-1

        case 302: return 19755; // C-2
        case 312: return 18646; // C#2
        case 402: return 17600; // D-2
        case 412: return 16612; // D#2
        case 502: return 15679; // E-2
        case 602: return 14799; // F-2
        case 612: return 13969; // F#2
        case 702: return 13185; // G-2
        case 712: return 12445; // G#2
        case 102: return 11746; // A-2
        case 112: return 11087; // A#2
        case 202: return 10465; // B-2

        case 303: return  9877; // C-3
        case 313: return  9323; // C#3
        case 403: return  8800; // D-3
        case 413: return  8306; // D#3
        case 503: return  7839; // E-3
        case 603: return  7399; // F-3
        case 613: return  6984; // F#3
        case 703: return  6592; // G-3
        case 713: return  6222; // G#3
        case 103: return  5873; // A-3
        case 113: return  5543; // A#3
        case 203: return  5232; // B-3

        case 304: return  4938; // C-4
        case 314: return  4661; // C#4
        case 404: return  4400; // D-4
        case 414: return  4153; // D#4
        case 504: return  3920; // E-4
        case 604: return  3699; // F-4
        case 614: return  3492; // F#4
        case 704: return  3296; // G-4
        case 714: return  3111; // G#4
        case 104: return  2936; // A-4
        case 114: return  2771; // A#4
        case 204: return  2616; // B-4

        case 305: return  2469; // C-5
        case 315: return  2330; // C#5
        case 405: return  2200; // D-5
        case 415: return  2076; // D#5
        case 505: return  1960; // E-5
        case 605: return  1850; // F-5
        case 615: return  1746; // F#5
        case 705: return  1648; // G-5
        case 715: return  1555; // G#5
        case 105: return  1468; // A-5
        case 115: return  1385; // A#5
        case 205: return  1308; // B-5

        case 306: return  1234; // C-6
        case 316: return  1165; // C#6
        case 406: return  1100; // D-6
        case 416: return  1038; // D#6
        case 506: return   980; // E-6
        case 606: return   925; // F-6
        case 616: return   873; // F#6
        case 706: return   824; // G-6
        case 716: return   777; // G#6
        case 106: return   734; // A-6
        case 116: return   693; // A#6
        case 206: return   654; // B-6

        case 307: return   617; // C-7
        case 317: return   582; // C#7
        case 407: return   550; // D-7
        case 417: return   519; // D#7
        case 507: return   490; // E-7
        case 607: return   462; // F-7
        case 617: return   436; // F#7
        case 707: return   412; // G-7
        case 717: return   388; // G#7
        case 107: return   367; // A-7
        case 117: return   346; // A#7
        case 207: return   327; // B-7

        case 308: return   308; // C-8
        case 318: return   291; // C#8
        case 408: return   275; // D-8
        case 418: return   259; // D#8
        case 508: return   245; // E-8
        case 608: return   231; // F-8
        case 618: return   218; // F#8
        case 708: return   206; // G-8
        case 718: return   194; // G#8
        case 108: return   183; // A-8
        case 118: return   173; // A#8
        case 208: return   163; // B-8
        default: return 0;
    }
}

int main() {
    configureClocks();
    buzzer_init();
    int lengthOfSong = sizeof(californiaLove) / sizeof(californiaLove[0]);
    while (1) {
        tick++;
        if (tick == 128) {
            buzzer_set_period(to_frequency_of(note(californiaLove[i])));
            i++;
            tick = 0;
        }
        if (i == lengthOfSong) {
            i = 0;
        }
        __delay_cycles(8000); // Delay for a bit before next update
    }
    or_sr(0x18);          // CPU off, GIE on
}