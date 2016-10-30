#include "PCA9536_RGB.h"

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);

const byte PIN_D2 = 2;

volatile boolean switchFlag;

void setup() {
    pinMode(PIN_D2, INPUT_PULLUP);
    switchFlag = digitalRead(PIN_D2) ? false : true;
    attachInterrupt (digitalPinToInterrupt (PIN_D2), switchPressed, CHANGE);
    Wire.begin();
    rgb.init();
    rgb.blinkSetup(500);
}

void loop() {
    switchCondition();
}

void switchPressed() {
      switchFlag = digitalRead(PIN_D2) ? false : true;
}

void switchCondition() {
    if (switchFlag) rgb.blink(GREEN);  
    else if (rgb.state(GREEN)) rgb.turnOff(GREEN);
}


