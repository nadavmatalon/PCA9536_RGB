/*
    PCA9536_RGB LIBRARY - BLINK COLOR EXAMPLE
    -----------------------------------------

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

    PIN 1 (IO0) - Connect BLUE  pin of a Common-Anode RGB Led via appropriate series resistor
    PIN 2 (IO1) - Connect GREEN pin of a Common-Anode RGB Led via appropriate series resistor
    PIN 3 (IO2) - Connect RED   pin of a Common-Anode RGB Led via appropriate series resistor
    PIN 4 (GND) - Connect to Arduino GND
    PIN 5 (IO3) - Leave unconnected for the purpose of this sketch
    PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 8 (VCC) - Connect to Arduino 5V output
    DECOUPING   - Connect a 0.1uF Ceramic Capacitor between the PCA9536's VCC & GND pins

    RGB LED COMMON-ANODE PIN - Connect to Arduino 5V output

    PUSH BUTTON SWITCH - connect a push-button switch between Arduino Digital Pin 2 and GND.


    IMPORTANT: It is possible to connect any type of RGB Led (Commone-Anode / Common-Cathode)
               to any of the PCA9536's I/O pins (IO0, IO1, IO2, IO3), but then it is necessary
               to update the constructor's configuration accordingly in the sketch itself.

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

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);              // construct a new PCA9536_RGB instance

volatile byte switchFlag;                             // a flag is needed since running the blinking inside the ISR 
                                                      // takes too long
void setup() {
    DDRD &= ~bit(DDD2); PORTD |= bit(PORTD2);         // pinMode(digital pin 2, INPUT_PULLUP)
    switchFlag = !bitRead(PIND, PIND2);               // set/clear switchFlag according to buton state (pressed or not)
    EICRA |= bit(ISC00);                              // Trigger INT0 on CHANGE
    EIMSK |= bit(INT0);                               // Enable external interrupt INT0
    sei();                                            // Enable global interrupts
    Wire.begin();                                     // Join the I2C Bus
    rgb.init();                                       // Initialize the RGB Led instance
    rgb.blinkSetup(500);                              // Set blinking rate (= onTime) to 500mS
  }

void loop() {
    switchCondition();                                // check if button is pressed or not and blink accordingly
}

ISR(EXT_INT0_vect) {                                  // ISR for external interrupt on digital pin 2
    switchFlag = 1;                                   // if interrupt fires (button is pressed), set switchFlag
}

void switchCondition() {
    if (bitRead(PIND, PIND2)) switchFlag = false;     // if button is not pressed (line is HIGH) clear switchFlag
    if (switchFlag) rgb.blink(GREEN);                 // if switchFlag is set (button is pressed), blink GREEN color
    else if (rgb.state(GREEN)) rgb.turnOff(GREEN);    // otherwise, if GREEN color remains ON, turn it OFF
}
