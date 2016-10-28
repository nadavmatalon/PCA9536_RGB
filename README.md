# PCA9536 RGB LED DRIVER

[![Platform Badge](https://img.shields.io/badge/platform-Arduino-orange.svg)](https://www.arduino.cc/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![SemVer](https://img.shields.io/badge/SemVer-1.0.0-brightgreen.svg)](http://semver.org/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![SemVer](https://img.shields.io/badge/eagle-pcb-yellow.svg)](https://cadsoft.io/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## INTRODUCTION

The PCA9536_RGB library provides an API for controlling a single RGB Led (Common-Anode or Common-Cathode) via the I2C Bus.

Communication between the Arduino (master) and the RGB Led (slave) is handled by the PCA9536, a 4-Channel I2C GPIO (General Purpose I/O) Expander.

The basis of the current API comes from the [PCA9536 Library](https://github.com/nadavmatalon/PCA9536), which is expanded here to include the relevant functions, including: Turning on a specific color (or all colors) on and off, Toggling a color, and an independent Blinking functionality for each color which doesn't make use of delays and therefore does not interrupt other routines running simultaniously in the code.


This library provides an API for controlling a single RGB Led (Common-Cathode or Common-Anode) via the I2C Bus. Communication between the Arduino (master) and the RGB Led (slave) is handled by the PCA9536, a 4-Channel I2C GPIO (General Purpose I/O) Expander. The basis of the current API comes from the PCA9536 Library (https://github.com/nadavmatalon/PCA9536), which is expanded here to include the relevant functions, including: Turning on a specific color (or all colors) on and off, Toggling a color, and an independent Blinking functionality for each color which doesn't make use of delays and therefore does not interrupt other routines running simultaniously in the code.

[PCA9536 DATASHEET](http://www.nxp.com/documents/data_sheet/PCA9536.pdf)

## REPOSITORY CONTENTS

- **PCA9536_RGB.h** - Library Header file.
- **PCA9536_RGB.cpp** - Library Compilation.
- **/examples**  
  - **/PCA9536_Usage**
  - **PCA9536_Usage.ino** - A sketch providing illustration of how to use the different functions of this library.
- **/extras** 
  - **License.txt** - A cope of the end-user license agreement.  
  - **/eagle**
    - **PCA9536_RGB.sch** - Schematic file for the PCA9536 &amp; Broadcom's [HSMF-C118](http://www.avagotech.com/products/leds-and-displays/chip-leds/multi-color-surface-mount/hsmf-c118) (or any other SMD Common-Anode RGB Led in a 1210 package) breakout board.
    - **PCA9536_RGB.brd** - Board layout file for the PCA9536 &amp; Broadcom's [HSMF-C118](http://www.avagotech.com/products/leds-and-displays/chip-leds/multi-color-surface-mount/hsmf-c118) (or any other SMD Common-Anode RGB Led in a 1210 package) breakout board.
- **keywords.txt** - Keywords for this library which will be highlighted in sketches within the Arduino IDE. 
- **library.properties** - General library properties for the Arduino's IDE (>1.5) Library Package Manager.
- **README.md** - The readme file for this library.
- **library.json** - JSON file for the Arduino's IDE (>1.5) Package Manager.

## HOOK-UP

PINS 1, 2, 3, 5 (IO0, IO1, IO2, IO3) - Connect to Led's pins pin via an appropriate resistors (fourth IO pin can be used for other user-defined purposes or tied to GND). If Led is Common-Anode connect its fourth pin to the Arduino 5V output. If the Led is Common-Cathode, connect the fourth pin to the Arduino GND.
PIN 4 (GND) - Connect to Arduino GND
PIN 6 (SCL) - Connect to Arduino Pin A5 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
PIN 7 (SDA) - Connect to Arduino Pin A4 with a 2K2 (400MHz) or 10K (100MHz) pull-up resistor
PIN 8 (VCC) - Connect to Arduino 5V output
DECOUPING   - Connect a 0.1uF Ceramic Capacitor between the PCA9536's VCC & GND pins

IMPORTANT: It is possible to connect any type of RGB Led (Commone-Anode / Common-Cathode) to any of the PCA9536's I/O pins (IO0, IO1, IO2, IO3), but then it is necessary to update the constructor's configuration accordingly in the sketch itself.


## GENERAL NOTES

1) __I2C Communications Library Dependency__

This library depends on the Arduino IDE's native '[Wire](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire)' library for I2C communication between the Arduino (Master) and the PCA9536 (Slave). 

2) __Constructor &amp; Destructor__

When an PCA9536_RGB instance is initialized without parameters by using the default constructor, the constructor and destructor have a slightly unconventional format in that they do not include the usual parentheses at the end. For more details, see 'LIBRARY INSTALLATION & SETUP' section below.

3) __BLINK() vs DELAY()__

It is not currently possible to use the library's blink() functionality in tandem with Arduino's delay() or delayMicroseconds() functions as the latter will mess up the timing for the former.

## I2C ADDRESS

The PCA9536 has a single I2C address (factory hardwired):

| PART NO.  | BIN      | HEX  | DEC | MARKING |
|-----------|----------|------|-----|---------|
| PCA9536D  | 01000001 | 0x41 | 65  | PCA9536 |

## LIBRARY INSTALLATION & SETUP

Begin by installing the [MCP9536 library](https://github.com/nadavmatalon/PCA9536) and the [MCP9536_RGB Library](https://github.com/nadavmatalon/PCA9536_RGB) either by using the Arduino IDE's Installation Wizard (Arduino Version >1.5) or simply by directly downloading the librarys' ZIP folders from Github, extracting them, and copying the extraxcted folders into your Arduino '/libraries' folder (don't forget to re-start the Arduino IDE after copying the folders so that the new libraries will show up in the list of installed libraries).

Next, include the PCA9536_RGB library at the top of the sketch as follows:

(Note that there is no need to include the base PCA9536 library)

```
#include "PCA9536_RGB.h"
```

At this point you can construct a new PCA9536_RGB default object by using the following command (at the top of the sketch after the 'include' line):

```
PCA9536_RGB device_name;  // Notice that the default constructor doesn't use parenthesis after device_name if using the default settings! (see Note #2 above)
```

The defualt constructor will automatically define the following configuration:
- LED TYPE: COMMON-ANODE
- PIN IO0: RED
- PIN IO1: GREEN
- PIN IO2: BLUE

(The fourth pin of the PCA9536 - in this case: IO3 - may be left unconnected or could be used for other user-defined purposes).

Alternatively, it is possible to emply a custom constructor to define a given configuration based on the actual hookup of the PCA9536 to the RGB Led. This constructor takes 4 parameters: 3 pin color assignments (IO0 / IO1 / IO2 / IO3 assigned according to the order: RED, GREEN, and BLUE) and the Led type (C_ANODE / C_CATHODE), for example:

```
PCA9536_RGB device_name(IO3, IO0, IO1, C_CATHODE);
```

In this example, the following configuration is defined:

- LED TYPE: COMMON-ANODE
- PIN IO3: RED
- PIN IO0: GREEN
- PIN IO1: BLUE

>When using either the default or the custom constructors, replace '__device_name__' above with a name of your choice. As the PCA9536 comes with a single hardwired I2C address, initializations of the class instance is done automatically to that address.

Next, make sure to inlude an instruction for initializing the I2C Bus for the [Wire Library](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire), as follows:

(There's no need to include the Wire Library at the top of the sketch as it's already included by the PCA9536 Library)

```
void setup() {
    Wire.begin();
    // ...other setup code...
}
```

## LIBRARY FUNCTIONS

With the library installed & included in the sketch, and an PCA9536 instance created, the following functions are available (see the usage example sketch for a detailed implementation):

__init();__  
Parameters:&nbsp;&nbsp;&nbsp;None  
Description:&nbsp;&nbsp;initializes the MCP9536_RGB instance with the constructor defined settings  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__turnOn();__  
Parameters:&nbsp;&nbsp;&nbsp;Optional: color_t(RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns on either all three colors (when no parameter is given) or a specified color (when a single color parameter is given)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__turnOff();__  
Parameters:&nbsp;&nbsp;&nbsp;Optional: color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns off either all three colors (when no parameter is given) or a specified color (when a single color parameter is given)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__toggle();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;toggles a specified color (i.e. if color is 'ON', it switches it to 'OFF', and vice versa)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__blinkSetup();__  
Parameters:&nbsp;&nbsp;&nbsp; color_t (RED / GREEN / BLUE), Optional: unsigned int   
Description:&nbsp;&nbsp;sets up the blink configuration for a specified color. If no second parameter is given, blink 'onTime' (and, equally, 'offTime') is set to 500mS by default. Otherwise, it is possible to custom set the duration of the 'ON' (and 'OFf') period by specifying a value for the second parameter. This function is necessary to enable the blinkOn() and blinkOff() functions. It is best to place it in the Setup() section of the sketch so that it's only executed once at runtime.  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__blinkOn();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns on the blinking of a specified color based on the settings defined in blinkSetup() for that color. Requires pre-setting the blink configuration for the specified color via blinkSetup().  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__blinkOff();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns off the blinking of the specified color  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  


## RUNNING THE EXAMPLE SKETCH

1) Start the Arduino IDE and open the example sketch
1) Hook-up the PCA9536 to the Arduino as explained in the sketch's notes   
2) Upload the relevant example sketch to the Arduino
3) Open the Serial Communications Window (make sure the baud-rate is set to 9600 or change it in the sketch to match your Serial Port's buad-rate).  

## BUG REPORTS

Please report any issues/bugs/suggestions at the [Issues](https://github.com/nadavmatalon/PCA9536_RGB/issues) section of this Github repository.

## TODO

* Formulate an automatic interrupt-based mechanism for the blink functionality (?)

## VERSION HISTORY

__Ver. 1.0.0__ - First release (24.10.16)  

## LICENSE

[The MIT License (MIT)](https://opensource.org/licenses/MIT)
Copyright (c) 2016 Nadav Matalon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
