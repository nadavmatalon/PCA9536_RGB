/*==============================================================================================================*

    @file     PCA9536_RGB.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon
 
    PCA9536 RGB LED Driver
 
    Ver. 1.0.0 - First release (25.10.16)
    Ver. 1.1.0 - Interupt-based Blink (31.10.16)

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
    _firstBlink = 1;
    for (byte i=0; i<3; i++) {
        setMode(getPin(i), _ledType);
        setState(getPin(i), ~_ledType);
    }
}

/*==============================================================================================================*
    TURN ON A SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::turnOn(color_t color) {                                        // PARAMS: RED / GREEN / BLUE
    setState(getPin(color), _ledType);
}

/*==============================================================================================================*
    TURN ON ALL THREE COLORS
 *==============================================================================================================*/

void PCA9536_RGB::turnOn() {
    for (byte i=0; i<3; i++) setState(getPin(i), _ledType);
}

/*==============================================================================================================*
    TURN OFF A SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::turnOff(color_t color) {                                       // PARAM: RED / GREEN / BLUE
    setState(getPin(color), ~_ledType);
}

/*==============================================================================================================*
    TURN OFF ALL THREE COLORS
 *==============================================================================================================*/

void PCA9536_RGB::turnOff() {
    for (byte i=0; i<3; i++) setState(getPin(i), ~_ledType);
}

/*==============================================================================================================*
    TOGGLE SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::toggle(color_t color) {                                        // PARAMS: RED / GREEN / BLUE
    toggleState(getPin(color));
}

/*==============================================================================================================*
    BLINK SINGLE COLOR SETUP
 *==============================================================================================================*/

// onTime = length of time (in mS) of led 'ON' state (duty cycle: 50%, default: 500mS)

void PCA9536_RGB::blinkSetup(unsigned int onTime) {
    _blinkFlag = 0;
    byte clockSelectBits;
    unsigned int pwmPeriod;
    unsigned long cycles = (F_CPU / 2000) * onTime;
    cli();
        TCCR1B = bit(WGM13);
        TCCR1A = 0;
        if (cycles < TIMER1_RES) {
            clockSelectBits = bit(CS10);
            pwmPeriod = cycles;
        } else if (cycles < TIMER1_RES * 8) {
            clockSelectBits = bit(CS11);
            pwmPeriod = cycles / 8;
        } else if (cycles < TIMER1_RES * 64) {
            clockSelectBits = bit(CS11) | bit(CS10);
            pwmPeriod = cycles / 64;
        } else if (cycles < TIMER1_RES * 256) {
            clockSelectBits = bit(CS12);
            pwmPeriod = cycles / 256;
        } else if (cycles < TIMER1_RES * 1024) {
            clockSelectBits = bit(CS12) | bit(CS10);
            pwmPeriod = cycles / 1024;
        } else {
            clockSelectBits = bit(CS12) | bit(CS10);
            pwmPeriod = TIMER1_RES - 1;
        }
        ICR1   = pwmPeriod;
        TCCR1B = bit(WGM13) | clockSelectBits;
        TIMSK1 = bit(TOIE1);
    sei();
}

/*==============================================================================================================*
     BLINK SINGLE COLOR
 *==============================================================================================================*/

void PCA9536_RGB::blink(color_t color) {
    if (_blinkFlag) {
        _blinkFlag = 0;
        if (_firstBlink) {
            _firstBlink = 0;
            turnOn(color);
        } else toggle(color);
    }
}

/*==============================================================================================================*
    GET COLOR STATE ( 0 = OFF / 1 = ON)
 *==============================================================================================================*/

byte PCA9536_RGB::state(color_t color) {
    return getState(getPin(color)) ? _ledType : ~_ledType;
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

/*==============================================================================================================*
    BLINK TIMER 1 ISR
 *==============================================================================================================*/

ISR(TIMER1_OVF_vect) {
    _blinkFlag = 1;
}

