/*==============================================================================================================*

    @file     PCA9536_RGB.h
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon
 
    PCA9536 RGB LED Driver
 
    Ver. 1.0.0 - First release (25.10.16)

 *===============================================================================================================*
    INTRODUCTION
 *===============================================================================================================*
 
    This library provides an API for controlling a single RGB Led (Common-Anode or Common-Cathode) via the I2C Bus.
 
    Communication between the Arduino (master) and the RGB Led (slave) is handled by the PCA9536, a 4-Channel 
    I2C GPIO (General Purpose I/O) Expander.
 
    The basis of the current API comes from the PCA9536 Library (https://github.com/nadavmatalon/PCA9536), 
    which is expanded here to include the relevant functions, including: Turning on a specific color (or all 
    colors) on and off, Toggling a color, and an independent Blinking functionality for each color which doesn't 
    make use of delays and therefore does not interrupt other routines running simultaniously in the code.
 
 *===============================================================================================================*
 I2C ADDRESS
 *===============================================================================================================*
 
 The PCA9536 has a single I2C address (factory hardwired):
 
 PART               DEVICE I2C ADDRESS          PART
 NUMBER          (BIN)      (HEX)     (DEC)     MARKING
 PCA9536D        01000001     0x41       65      PCA9536
 
 *===============================================================================================================*
 REGISTER POINTERS
 *===============================================================================================================*
 
 REG_INPUT           0x00        // Input Port Register           (R)    B00000000 (Default)
 REG_OUTPUT          0x01        // Output Port Register          (R/W)  B00000001
 REG_POLARITY        0x02        // Polarity Inversion Register   (R/W)  B00000010
 REG_CONFIG          0x03        // Configuration Register        (R/W)  B00000011
 
 *===============================================================================================================*
 REGISTER 0: INPUT REGIASTER - READ ONLY (0 = LOW / 1 = HIGH)
 *===============================================================================================================*
 
 DEFAULT (WITH NO EXTENRAL INPUT SIGNAL CONNECTED): 'HIGH' (ALL IO PINS HAVE WEAK PULL-UP RESISTORS)
 
 DEFAULT
 PIN_IO0             BIT 0          1
 PIN_IO1             BIT 1          1
 PIN_IO2             BIT 2          1
 PIN_IO3             BIT 3          1
 
 BITS 4-7: NOT USED (DEFAULT: 1)
 
 *===============================================================================================================*
 REGISTER 1: OUTPUT REGIASTER - READ / WRITE (0 = LOW / 1 = HIGH)
 *===============================================================================================================*
 
 DEFAULT
 IO0                 BIT 0          1
 IO1                 BIT 1          1
 IO2                 BIT 2          1
 IO3                 BIT 3          1
 
 BITS 4-7: NOT USED (DEFAULT: 1) - MAY BE SET AS '0' OR '1'
 
 *===============================================================================================================*
 REGISTER 2: POLARITY REGIASTER - READ / WRITE (0 = NON-INVERTED / 1 = INVERTED)
 *===============================================================================================================*
 
 DEFAULT
 PIN_IO0             BIT 0         0
 PIN_IO1             BIT 1         0
 PIN_IO2             BIT 2         0
 PIN_IO3             BIT 3         0
 
 BITS 4-7: NOT USED (DEFAULT: 0) - MAY BE SET AS '0' OR '1'
 
 *===============================================================================================================*
 REGISTER 3: CONFIGURATION - READ / WRITE (0 = OUTPUT / 1 = INPUT)
 *===============================================================================================================*
 
 POWER-UP DEFAULT: ALL PINS ARE SET AS 'INPUT' (1)
 
 DEFAULT
 PIN_IO0             BIT 0         1
 PIN_IO1             BIT 1         1
 PIN_IO2             BIT 2         1
 PIN_IO3             BIT 3         1
 
 BITS 4-7: NOT USED (DEFAULT: 1) - MAY BE SET AS '0' OR '1'
 
*===============================================================================================================*
    LICENSE
*===============================================================================================================*
 
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

#if 1
__asm volatile ("nop");
#endif

#ifndef PCA9536_RGB_h
#define PCA9536_RGB_h

#if !defined(ARDUINO_ARCH_AVR)
#error “The PCA9536 RGB LED Driver library only supports AVR processors.”
#endif

#include <Arduino.h>
#include "PCA9536.h"

namespace Pca9536_Rgb {
    
    typedef enum:byte {
        C_ANODE   = 0,
        C_CATHODE = 1
    } led_type_t;

    typedef enum:byte {
        RED   = 0,
        GREEN = 1,
        BLUE  = 2
    } color_t;

     typedef struct blink {
        color_t color;
        unsigned int  onTime;
        unsigned long tick;
        unsigned long tock;
        boolean active;
     } blink;

    class PCA9536_RGB: private PCA9536 {
        public:
            PCA9536_RGB(pin_t pin1 = IO0, pin_t pin2 = IO1, pin_t pin3 = IO2, led_type_t ledType = C_ANODE);
            ~PCA9536_RGB();
            void init();
            void turnOn(color_t color);
            void turnOn();
            void turnOff(color_t color);
            void turnOff();
            void toggle(color_t color);
            void blinkSetup(color_t color, unsigned int onTime = 500);
            void blinkOn(color_t color);
            void blinkOff(color_t color);
        private:
            byte state(color_t color);
            byte getPin(color_t color);
            byte _ledType;
            byte _red;
            byte _green;
            byte _blue;
            blink blinks[3];
    };
}

using namespace Pca9536_Rgb;

#endif
