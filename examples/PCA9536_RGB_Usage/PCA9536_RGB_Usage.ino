/* 
  PCA9536_RGB LIBRARY - USAGE EXAMPLE
  -----------------------------------

  INTRODUCTION
  ------------ 

  This sketch offers a complete usage illustration of how to use the PCA9536_RGB library.

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

    This following hookup can be used with any Common-Anode RGB Led and the present sketch:

    PIN 1 (IO0) - Connect to Led's BLUE  pin via an appropriate resistor
    PIN 2 (IO1) - Connect to Led's GREEN pin via an appropriate resistor
    PIN 3 (IO2) - Connect to Led's RED   pin via an appropriate resistor
    PIN 4 (GND) - Connect to Arduino GND
    PIN 5 (IO3) - Connect to Arduino GND
    PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
    PIN 8 (VCC) - Connect to Arduino 5V output
    DECOUPING   - Connect a 0.1uF Ceramic Capacitor between the PCA9536's VCC & GND pins

    RGB LED COMMON-ANODE PIN - Connect to Arduino 5V output

    IMPORTANT: It is possible to connect any type of RGB Led (Commone-Anode / Common-Cathode)
               to any of the PCA9536's I/O pins (IO0, IO1, IO2, IO3), but then it is necessary
               to update the constructor's configuration accordingly in the sketch itself.

  I2C ADDRESS
  -----------
  The PCA9536 has a single I2C address (factory hardwired):
 
        PART               DEVICE I2C ADDRESS          PART
       NUMBER          (BIN)      (HEX)     (DEC)     MARKING
      --------        --------    -----     -----     -------
      PCA9536D        01000001    0x41       65       PCA9536

  Note: The 'D' suffix of the Part Number denotes the SOIC-8 package

  BUG REPORTS
  -----------
  Please report any bugs/issues/suggestions in the Github Repository of this library at: https://github.com/nadavmatalon/PCA9536_RGB/issues

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

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);

boolean alarmConditions = true;
unsigned long count = 0;

void setup() {
    Wire.begin();
    rgb.init();
    rgb.blinkSetup(GREEN);
}

void loop() {
    if (alarmConditions) rgb.blinkOn(GREEN);
    else rgb.blinkOff(GREEN);
    count++;
    if (count >= 1000 && count < 2000) alarmConditions = false;
    if (count >= 2000) {
        alarmConditions = true;
        count = 0;
    }
}