#include "PCA9536_RGB.h"

PCA9536_RGB rgb(IO2, IO1, IO0, C_ANODE);

volatile boolean switchFlag;

void setup() {
    DDRD &= ~(1 << DDD2); PORTD |= (1 << PORTD2);                               // pinMode(PIN_D2, INPUT_PULLUP)
    switchFlag = !bitRead(PIND, 2);                                             // !digitalRead(PIN_D2)
    EICRA |= (1 << ISC01);                                                      // Trigger INT0 on falling edge
    EIMSK |= (1 << INT0);                                                       // Enable external interrupt INT0
    sei();                                                                      // Enable global interrupts
    Wire.begin();
    rgb.init();
    rgb.blinkSetup(500);
}

void loop() {
    switchCondition();
}

ISR(EXT_INT0_vect) {
    switchFlag = !bitRead(PIND, 2);
}

void switchCondition() {
    if (switchFlag) rgb.blink(GREEN);
    else if (rgb.state(GREEN)) rgb.turnOff(GREEN);
}

