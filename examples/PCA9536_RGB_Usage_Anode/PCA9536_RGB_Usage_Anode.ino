/*
    PCA9536_RGB LIBRARY - USAGE EXAMPLE (COMMON-ANODE)
    --------------------------------------------------

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

    RUNNING THE SKETCH
    ------------------
    1. Hook-up the PCA9536 and RGB Led (Common-Cathode) as instructed above
    2. Upload the sketch to the Arduino
    3. (Optional) Open the Serial Port (make sure the baid-rate is to 9600)
    4. Sit back and watch the pretty lights :-)

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

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);

color_t colors[3] = { RED, GREEN, BLUE };
String colorNames[3] = { "RED", "GREEN", "BLUE" };
 
void setup() {
    Serial.begin(9600);
    Wire.begin();
    rgb.init();
    rgb.turnOff();
    longDelay();
    printDivider();
    Serial.print(F("\nPCA9536 RGB LED LIBRARY USAGE\n"));
    printDivider();
    longDelay();
    colorsOnOff(); 
    colorsToggle();  
}

void loop() {}

void colorsOnOff() {
   Serial.print(F("\nTURN ON ALL THREE COLORS\n"));
    rgb.turnOn();
    longDelay();
    Serial.print(F("\nTURN OFF ALL THREE COLORS\n"));
    rgb.turnOff();
    printDivider();
    longDelay();
    Serial.print(F("\nTURN COLORS ON AND OFF INDIVIDUALLY\n"));
    for (byte i=0; i<3; i++) {
        Serial.print(F("\nTURN ON "));
        Serial.print(colorNames[i]);
        Serial.print(F("\n"));
        rgb.turnOn(colors[i]);
        longDelay();
        Serial.print(F("\nTURN OFF "));
        Serial.print(colorNames[i]);
        Serial.print(F("\n"));
        rgb.turnOff(colors[i]);
        longDelay();
    }
    printDivider();
    Serial.print(F("\nTURN COLORS ON SEQUENTIALLY\n"));
    for (byte i=0; i<3; i++) {
        Serial.print(F("\nTURN ON "));
        Serial.print(colorNames[i]);
        Serial.print(F("\n"));
        rgb.turnOn(colors[i]);
        longDelay();
    }
    Serial.print(F("\nTURN COLORS OFF SEQUENTIALLY\n"));
    for (byte i=3; i>0; i--) {
        Serial.print(F("\nTURN OFF "));
        Serial.print(colorNames[i-1]);
        Serial.print(F("\n"));
        rgb.turnOff(colors[i-1]);
        longDelay();
    }  
    printDivider();
    longDelay();
}

void colorsToggle() {
    Serial.print(F("\nTOGGLE COLORS INDIVIDUALY\n"));
    for (byte i=0; i<3; i++) {
        Serial.print(F("\nTOGGLE "));
        Serial.print(colorNames[i]);
        Serial.print(F("\n"));
        for (byte j=0; j<10; j++) { 
            rgb.toggle(colors[i]);
            shortDelay();
        }
        longDelay();
    }
    printDivider(); 
    Serial.print(F("\nDONE\n"));
    printDivider(); 
}

void printDivider() {
    Serial.print(F("\n-----------------------------\n"));
}

void shortDelay() {
    delay(250);
}

void longDelay() {
    delay(1750);
}
