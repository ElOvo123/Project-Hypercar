#ifndef BLINKING_LED_H
#define BLINKING_LED_H

#include <Arduino.h>

class BlinkingLed {
private:
    int ledPin;
    int ledState;
    unsigned long previousMillis;
    long interval;

    void setLedPin(int pin);
    void setLedState(bool state);
    void setBlinkInterval(long blinkInterval);
    void setPreviousMillis(unsigned long millis);
    bool getLedState() const;

public:
    BlinkingLed(int pin, bool state, unsigned long prevMillis, long blinkInterval);

    void InitBlinkLed();
    void BlinkLed();
};

#endif
