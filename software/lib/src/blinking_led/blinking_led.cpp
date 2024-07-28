#include "blinking_led.h"
#include <Arduino.h>

BlinkingLed::BlinkingLed(int pin, bool state, unsigned long prevMillis, long blinkInterval)
    : ledPin(pin), ledState(state), previousMillis(prevMillis), interval(blinkInterval) {
}

void BlinkingLed::setLedPin(int pin) {
    ledPin = pin;
    return;
}

void BlinkingLed::setLedState(bool state) {
    ledState = state;
    return;
}

void BlinkingLed::setBlinkInterval(long blinkInterval) {
    interval = blinkInterval;
    return;
}

void BlinkingLed::setPreviousMillis(unsigned long millis) {
    previousMillis = millis;
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
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        setPreviousMillis(currentMillis);

        if (ledState == getLedState()) {
            setLedState(HIGH);
        } else {
            setLedState(LOW);
        }

        digitalWrite(ledPin, ledState);
    }
}
