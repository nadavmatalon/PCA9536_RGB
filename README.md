# PCA9536 RGB LED DRIVER

[![Platform Badge](https://img.shields.io/badge/platform-Arduino-orange.svg)](https://www.arduino.cc/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![SemVer](https://img.shields.io/badge/SemVer-1.2.0-brightgreen.svg)](http://semver.org/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![SemVer](https://img.shields.io/badge/eagle-pcb-yellow.svg)](https://cadsoft.io/)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## INTRODUCTION

The PCA9536_RGB library provides an API for controlling a single RGB Led (Common-Anode or Common-Cathode) via the I2C Bus.

Communication between the Arduino (master) and the RGB Led (slave) is handled by the PCA9536, a 4-Channel I2C GPIO (General Purpose I/O) Expander.

The basis of the current API comes from the [PCA9536 Library](https://github.com/nadavmatalon/PCA9536), which is expanded here to include the relevant functions, including: Turning on a specific color (or all colors) on and off, Toggling a color, and an independent Blinking functionality for each color which doesn't make use of delays and therefore does not interrupt other routines running simultaniously in the code.

[PCA9536 DATASHEET](http://www.nxp.com/documents/data_sheet/PCA9536.pdf)

## REPOSITORY CONTENTS

- **PCA9536_RGB.h** - Library Header file.
- **PCA9536_RGB.cpp** - Library Compilation.
- **/examples**  
  - **/PCA9536_Usage_Anode**
    - **PCA9536_Usage_Anode.ino** - A sketch providing illustration of how to use the basic functions of this library with a Common-Anode RGB Led.
  - **/PCA9536_Usage_Cathode**
    - **PCA9536_Usage_Cathode.ino** - A sketch providing illustration of how to use the basic functions of this library with a Common-Cathode RGB Led.
  - **/PCA9536_Blink_Anode**
    - **PCA9536_Blink_Anode.ino** - A sketch providing illustration of how to use the blink() functionality with a Common-Cathode RGB Led.
  - **/PCA9536_Blink_Cathode**
    - **PCA9536_Blink_Cathode.ino** - A sketch providing illustration of how to use the blink() functionality with a Common-Cathode RGB Led.
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

## GENERAL NOTES

1) __I2C Communications Library Dependency__

This library depends on the Arduino IDE's native [Wire](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire) library for I2C communication between the Arduino (Master) and the PCA9536 (Slave). 

2) __Constructor &amp; Destructor__

When an PCA9536_RGB instance is initialized __without__ parameters by using the default constructor, the constructor (and destructor if used) has a slightly unconventional format in that it does not include the usual parentheses at the end. For more details, see 'LIBRARY INSTALLATION & SETUP' section below.

3) __BLINK() vs DELAY()__

It is not currently possible to use the library's blink() functionality in tandem with Arduino's delay() or delayMicroseconds() functions as the latter will mess up the timing of the former.

## I2C ADDRESS

The PCA9536 has a single I2C address (factory hardwired):

| PART NO.  | BIN      | HEX  | DEC | MARKING |
|-----------|----------|------|-----|---------|
| PCA9536D  | 01000001 | 0x41 | 65  | PCA9536 |

## LIBRARY INSTALLATION & SETUP

Begin by installing the current [MCP9536_RGB](https://github.com/nadavmatalon/PCA9536_RGB) library and the base [MCP9536 Library](https://github.com/nadavmatalon/PCA9536) either by using the Arduino IDE's Installation Wizard (Arduino Version >1.5) or simply by directly downloading the librarys' ZIP folders from Github, extracting them, and copying the extraxcted folders into your Arduino '/libraries' folder (don't forget to re-start the Arduino IDE after copying the folders so that the new libraries will show up in the list of installed libraries).

Next, include the PCA9536_RGB library at the top of the sketch as follows:

(The base PCA9536 library will be included automatically and so there's no need to include it here)

```
#include "PCA9536_RGB.h"
```

At this point you can construct a new PCA9536_RGB (default) instance by using the following command (place at the top of the sketch after the 'include' line):

```
PCA9536_RGB device_name;  // Notice that this constructor doesn't have parenthesis after device_name! (see Note #2 above)
```

The defualt constructor will automatically define the following configuration:
- LED TYPE&nbsp; -> &nbsp;&nbsp;COMMON-ANODE
- RED&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO0
- GREEN&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO1
- BLUE&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO2


(The fourth pin of the PCA9536 - in this case: IO3 - may be left unconnected or could be used for other user-defined purposes).

Alternatively, it is possible to employ a custom constructor to define a given configuration based on the actual hookup of the PCA9536 to the RGB Led. This constructor takes 4 parameters: 3 Pin-Color assignments (IO0 / IO1 / IO2 / IO3 assigned according to the order: RED, GREEN, and BLUE) and the Led type (C_ANODE / C_CATHODE), for example:

```
PCA9536_RGB device_name(IO3, IO0, IO1, C_CATHODE);
```

In this example, the following configuration is defined:

- LED TYPE&nbsp; -> &nbsp;&nbsp;COMMON-CATHODE
- RED&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO3
- GREEN&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO0
- BLUE&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;PIN IO1


Next, make sure to inlude an instruction for initializing the I2C Bus for the [Wire](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire) Library, as well as the newly created __PCA9536_RGB instance__, as follows:


>NB The order here is important: __device_name.init()__ must come AFTER __Wire.begin()__ - this is necessary because __init()__ sets the registrs' values of the device and so depends on Wire being active.

>NB There's no need to include the [Wire](https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire) Library at the top of the sketch as it's already included by the PCA9536_RGB Library).

```
void setup() {
    Wire.begin();
    device_name.init();
    // ...other setup code...
}
```
>NB When using either the default or the custom constructors, replace __device_name__ above with a name of your choice. As the PCA9536 comes with a single hardwired I2C address, initializations of the class instance is done automatically to that address.

## LIBRARY FUNCTIONS

With the library installed & included in the sketch, and an PCA9536 instance created, the following functions are available (see the usage example sketch for a detailed implementation):

__init();__  
Parameters:&nbsp;&nbsp;&nbsp;None  
Description:&nbsp;&nbsp;initializes the MCP9536_RGB instance  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__turnOn();__  
Parameters:&nbsp;&nbsp;&nbsp;Optional: color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns on all three colors (when no parameter is given) or a specified color (when a single color parameter is given)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__turnOff();__  
Parameters:&nbsp;&nbsp;&nbsp;Optional: color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;turns off all three colors (when no parameter is given) or a specified color (when a single color parameter is given)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__toggle();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;toggles a specified color (i.e. if color is 'ON', it switches it to 'OFF', and vice versa)  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__blinkSetup();__  
Parameters:&nbsp;&nbsp;&nbsp; color_t (RED / GREEN / BLUE), Optional: unsigned int   
Description:&nbsp;&nbsp;sets up the blink configuration for a specified color. If no second parameter is given, blink 'onTime' (and, equally, 'offTime') is set to 500mS by default. Otherwise, it is possible to custom set the duration of the 'ON' (and 'OFf') period by specifying a value for the second parameter. This function is necessary to enable the blinkOn() and blinkOff() functions. It is best to place it in the Setup() section of the sketch so that it'll only executed once at runtime.  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__blink();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;blinks the specified color based on the settings defined in blinkSetup().  
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;None  

__state();__  
Parameters:&nbsp;&nbsp;&nbsp;color_t (RED / GREEN / BLUE)  
Description:&nbsp;&nbsp;returns the specified color's current state (0 = OFF / 1 = ON)   
Returns:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Byte  

## RUNNING THE EXAMPLE SKETCHES

1) Start the Arduino IDE and open the relevant example sketch  
2) Hook-up the PCA9536 to the Arduino as explained in the sketch's notes  
3) Upload the sketch to the Arduino 
4) Follow the specific instructions for running the sketch as explained in the sketch's notes

## BUG REPORTS

Please report any issues/bugs/suggestions in the [Issues](https://github.com/nadavmatalon/PCA9536_RGB/issues) section of this Github repository.

## TODO

## VERSION HISTORY

__Ver. 1.0.0__ - First release (24.10.16)  
__Ver. 1.1.0__ - Interrupt-Based Blink (31.10.16)  
__Ver. 1.2.0__ - Code odifications for C-CATHODE Leds (4.11.16)

## LICENSE

[The MIT License (MIT)](https://opensource.org/licenses/MIT)
Copyright (c) 2016 Nadav Matalon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
