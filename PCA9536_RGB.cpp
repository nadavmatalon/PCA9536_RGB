/*==============================================================================================================*

    @file     PCA9536_RGB.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon
 
    PCA9536 RGB LED Driver
 
    Ver. 1.0.0 - First release (25.10.16)
 
 *==============================================================================================================*
    LICENSE
 *==============================================================================================================*
 
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

 *==============================================================================================================*/

#include "PCA9536_RGB.h"

/*==============================================================================================================*
    CONSTRUCTOR
 *==============================================================================================================*/

                                                   // PARAMS: IO0 / IO1 / IO2 / IO3 | C_ANODE / C_CATHODE
                                                   // [defaults: _red = IO0, _green = IO1, _red = IO2 | C_ANODE]
PCA9536_RGB::PCA9536_RGB(pin_t pin1, pin_t pin2, pin_t pin3, led_type_t ledType) {
    _red   = pin1;
    _green = pin2;
    _blue  = pin3;
    _ledType = ledType;
}

/*==============================================================================================================*
    DESTRUCTOR
 *==============================================================================================================*/

PCA9536_RGB::~PCA9536_RGB() {}

/*==============================================================================================================*
    INITIALIZE
 *==============================================================================================================*/

void PCA9536_RGB::init() {
    for (byte i=0; i<3; i++) {
        setMode(getPin(i), _ledType ? IO_INPUT : IO_OUTPUT);
        setState(getPin(i), _ledType ? IO_LOW : IO_HIGH);
    }
}

/*==============================================================================================================*
    TURN ON A SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::turnOn(color_t color) {                                        // PARAMS: RED / GREEN / BLUE
    setState(getPin(color), _ledType ? IO_HIGH : IO_LOW);
}

/*==============================================================================================================*
    TURN ON ALL THREE COLORS
 *==============================================================================================================*/

void PCA9536_RGB::turnOn() {
    for (byte i=0; i<3; i++) setState(getPin(i), _ledType ? IO_HIGH : IO_LOW);
}

/*==============================================================================================================*
    TURN OFF A SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::turnOff(color_t color) {                                       // PARAM: RED / GREEN / BLUE
    setState(getPin(color), _ledType ? IO_LOW : IO_HIGH);
}

/*==============================================================================================================*
    TURN OFF ALL THREE COLORS
 *==============================================================================================================*/

void PCA9536_RGB::turnOff() {
    for (byte i=0; i<3; i++) setState(getPin(i), _ledType ? IO_LOW : IO_HIGH);
}

/*==============================================================================================================*
    TOGGLE SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::toggle(color_t color) {                                        // PARAMS: RED / GREEN / BLUE
    toggleState(getPin(color));
}

/*==============================================================================================================*
     SETUP BLINK SINGLE COLOR
 *==============================================================================================================*/

// onTime = length of time (in mS) of led 'ON' state (duty cycle: 50%, default: 500mS)

void PCA9536_RGB::blinkSetup(color_t color, unsigned int onTime) {               // PARAMS: RED / GREEN / BLUE
    blinks[color] = blink { color, onTime, 0, 0, false };
}

/*==============================================================================================================*
     TURN ON BLINK SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::blinkOn(color_t color) {
    if (blinks[color].onTime > 0) {
        if (!blinks[color].active) blinks[color].active = true;
        blinks[color].tock = millis();
        if ((blinks[color].tock - blinks[color].tick) >= blinks[color].onTime) {
            blinks[color].tick = blinks[color].tock;
            toggle(blinks[color].color);
        }
    }
}

/*==============================================================================================================*
    TURN OFF BLINK SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::blinkOff(color_t color) {
    if (blinks[color].active && state(color)) turnOff(blinks[color].color);
    blinks[color].active = false;
}

/*==============================================================================================================*
    GET COLOR STATE ( 0 = OFF / 1 = ON)
 *==============================================================================================================*/

byte PCA9536_RGB::state(color_t color) {
    return getState(getPin(color)) ? _ledType : _ledType ? IO_LOW : IO_HIGH;
}

/*==============================================================================================================*
    GET PIN COLOR
 *==============================================================================================================*/

byte PCA9536_RGB::getPin(color_t color) {
    switch (color) {
        case (RED):   return _red;   break;
        case (GREEN): return _green; break;
        case (BLUE):  return _blue;  break;
    }
}
