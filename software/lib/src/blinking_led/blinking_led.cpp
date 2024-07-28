#include "Arduino.h"
#include "blinking_led.h"

int ledPin = 0;
int ledState = LOW;
unsigned long previousMillis = 0;
long interval = 0;

void SetLedPin(int pin) {
    ledPin = pin;
}

void SetLedState(bool state) {
    ledState = state;
}

void SetBlinkInterval(long blinkInterval) {
    interval = blinkInterval;
}

void SetPreviousMillis(unsigned long millis) {
    previousMillis = millis;
}

bool GetLedState(void) {
    return ledState;
}

void InitBlinkLed(int pin, bool state, unsigned long prevMillis, long blinkInterval) {
    SetLedPin(pin);
    SetBlinkInterval(blinkInterval);
    SetPreviousMillis(prevMillis);
    SetLedState(state);

    pinMode(ledPin, OUTPUT);
}

void BlinkLed(void) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        SetPreviousMillis(currentMillis);

        if (ledState == GetLedState()) {
            SetLedState(HIGH);
        } else {
            SetLedState(LOW);
        }

        digitalWrite(ledPin, ledState);
    }
}
