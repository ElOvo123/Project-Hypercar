#include "blinking_led.h"
#include <Arduino.h>

BlinkingLed::BlinkingLed(int pin, bool state)
    : ledPin(pin), ledState(state){
}

void BlinkingLed::setLedPin(int pin) {
    ledPin = pin;
    return;
}

void BlinkingLed::setLedState(bool state) {
    ledState = state;
    return;
}

bool BlinkingLed::getLedState() const {
    return ledState;
}

void BlinkingLed::InitBlinkLed() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
}

void BlinkingLed::BlinkLed() {
    digitalWrite(ledPin, !ledState);
}
