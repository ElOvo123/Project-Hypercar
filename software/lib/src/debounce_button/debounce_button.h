#ifndef DEBOUNCE_BUTTON_H
#define DEBOUNCE_BUTTON_H

class DebouncingButton
{
private:
    int buttonPin;
    bool buttonState;
    bool lastButtonState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay ; 

    void SetButtonPin(int pin);
    void SetButtonState(int state);
    void SetLastButtonState(int lastState);
    void SetDebounceDelay(unsigned long delay);
    void SetLastDebounceTime(unsigned long time);
    bool GetButtonState(void);
    bool GetLastButtonState(void);
    unsigned long GetDebounceDelay(void);
    unsigned long GetLastDebounceTime(void);
public:
    DebouncingButton(int pin, bool state, bool lastState, unsigned long delay, unsigned long time);

    void InitDebounceButton();
    bool Debounce();
    
};

#endif
