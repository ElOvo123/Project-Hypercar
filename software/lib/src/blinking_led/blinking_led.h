#ifndef BLINKING_LED_H
#define BLINKING_LED_H

class BlinkingLed {
private:
    int ledPin;
    int ledState;

    void setLedPin(int pin);
    void setLedState(bool state);
    bool getLedState() const;

public:
    BlinkingLed(int pin, bool state);

    void InitBlinkLed();
    void BlinkLed();
};

#endif
