#include "blinking_led.h"
#include <Arduino.h>

BlinkingLed::BlinkingLed(int pin, bool state)
    : ledPin(pin), ledState(state) {
}

void BlinkingLed::setLedPin(int pin) {
    ledPin = pin;
}

void BlinkingLed::setLedState(bool state) {
    ledState = state;
}

bool BlinkingLed::getLedState() const {
    return ledState;
}

void BlinkingLed::InitBlinkLed() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState ? HIGH : LOW);
}

void BlinkingLed::BlinkLed() {
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
}
