#include "PCA9536_RGB.h"

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);

boolean alertOn = false;

void setup() {
Wire.begin();
rgb.init();
rgb.blinkSetup(500);
}

void loop() {
if (alertOn) rgb.blink(GREEN);
}