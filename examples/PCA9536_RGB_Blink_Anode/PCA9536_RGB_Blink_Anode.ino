/*
    PCA9536_RGB LIBRARY - BLINK COLOR EXAMPLE (COMMON-ANODE)
    --------------------------------------------------------

    INTRODUCTION
    ------------
    This sketch offers a simple code illustrating the use of the blink() function of the PCA9536_RGB library.

    The blinking function uses an ISR (Interrupt Service Routine) based on overflow of Arduino Timer 1 (not to
    be confused with the ISR used for monitoring the state of the push-button switch use below)

    INPORTANT: The current library depends on the Arduino IDE's native 'Wire' library for I2C communication between the Arduino (Master) and the PCA9536 (Slave).

    WIRING DIAGRAM
    --------------

               PCA9536
               -------
        IO0 --| •     |-- VCC
              |       |
        IO1 --|       |-- SDA
              |       |
        IO2 --|       |-- SCL
              |       |
        GND --|       |-- IO3
               -------

    This sketch should be used with the following hookup:

    PIN 1 (IO0) - Connect to Common-Anode RGB Led BLUE  pin via appropriate series resistor
    PIN 2 (IO1) - Connect to Common-Anode RGB Led GREEN pin via appropriate series resistor
    PIN 3 (IO2) - Connect to Common-Anode RGB Led RED   pin via appropriate series resistor
    PIN 4 (GND) - Connect to Arduino GND
    PIN 5 (IO3) - Leave unconnected for the purpose of this sketch
    PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 8 (VCC) - Connect to Arduino 5V output
    DECOUPING   - Connect a 0.1uF Ceramic Capacitor between the PCA9536's VCC & GND pins

    RGB LED COMMON-ANODE PIN - Connect to Arduino 5V output

    PUSH-BUTTON SWITCH - Connect one end to Arduino Digital Pin 2, and the other end to Arduino GND

    RUNNING THE SKETCH
    ------------------
    1. Hook-up the PCA9536 and RGB Led (Common-Anode) as instructed above
    2. Upload the sketch to the Arduino
    3. Press the push-button switch to see the blinking in action

    BUG REPORTS
    -----------
    Please report any bugs/issues/suggestions in the Github Repository of this library at:
    https://github.com/nadavmatalon/PCA9536_RGB/issues

    LICENSE
    -------

    The MIT License (MIT)
    Copyright (c) 2016 Nadav Matalon

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without
    limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "PCA9536_RGB.h"

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);                        // construct a new PCA9536_RGB instance

const color_t BLINK_COLOR = GREEN;                              // selected color to be blinked
const unsigned int BLINK_RATE = 600;                            // blink rate (= color 'ON' period; equal to 'OFF' period) in mS

void setup() {
    DDRD &= ~bit(DDD2);                                         // pinMode(digital pin 2, INPUT)
    EICRA |= bit(ISC00);                                        // trigger INT0 on any state CHANGE (both button pressed and released)
    EIMSK |= bit(INT0);                                         // enable external interrupt INT0
    Wire.begin();                                               // join the I2C Bus
    rgb.init();                                                 // initialize the PCA9536_RGB instance with the above defined configuration
    rgb.blinkSetup(BLINK_RATE);                                 // set blink rate in mS
}

void loop() {
    if (GPIOR0) rgb.blink(BLINK_COLOR);                         // if button is being pressed, blink selected color
    else if (rgb.state(BLINK_COLOR)) rgb.turnOff(BLINK_COLOR);  // if button has been released, but selected color remains ON, turn off color
}

ISR(INT0_vect, ISR_NAKED) {                                     // Part I of ISR for INT0 (on digital pin 2)
    asm volatile (                                              // bitWrite(GPIOR0, 0, ~PIND2)
    "    sbic %[pin], %[bit]    \n"                             // if !bitRead(PIND, 2), skip the next instruction
    "    cbi %[gpio], 0         \n"                             // bitClear(GPIO0, 0)
    "    sbis %[pin], %[bit]    \n"                             // if bitRead(PIND, 2), skip the next instruction
    "    sbi %[gpio], 0         \n"                             // bitSet(GPIO0, 0)
    "    rjmp INT0_vect_part_2  \n"                             // move on to part 2 of the ISR for INT0
    :: [pin]  "I" (_SFR_IO_ADDR(PIND)),                         // selected register to be tied to GPIOR0 (in this case: PIND)
       [bit]  "I" (2),                                          // specific bit number in above register to be tied to first bit og GPIOR0 
       [gpio] "I" (_SFR_IO_ADDR(GPIOR0)));                      // selected GPIOR register (in this case: GPIOR0)
}

ISR(INT0_vect_part_2) {}                                        // Part II of ISR for INT0 (on digital pin 2) - needed for compilation
