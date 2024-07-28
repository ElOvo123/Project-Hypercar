#include <Arduino.h>
#include "debounce_button.h"

DebouncingButton::DebouncingButton(int pin, bool state, bool lastState, unsigned long delay, unsigned long time)
: buttonPin(pin), buttonState(state), lastButtonState(lastState), debounceDelay(delay), lastDebounceTime(time){
}

void DebouncingButton::SetButtonPin(int pin){
    buttonPin = pin;
    return;
}

void DebouncingButton::SetButtonState(int state){
    buttonState = state;
    return;
}

void DebouncingButton::SetLastButtonState(int lastState){
    lastButtonState = lastState;
    return;
}

void DebouncingButton::SetDebounceDelay(unsigned long delay){
    debounceDelay = delay;
    return;
}

void DebouncingButton::SetLastDebounceTime(unsigned long time){
    lastDebounceTime = time;
    return;
}

bool DebouncingButton::GetButtonState(void){
    return buttonState;
}

bool DebouncingButton::GetLastButtonState(void){
    return lastButtonState;
}

unsigned long DebouncingButton::GetDebounceDelay(void){
    return debounceDelay;
}

unsigned long DebouncingButton::GetLastDebounceTime(void){
    return lastDebounceTime;
}

void DebouncingButton::InitDebounceButton(){
    pinMode(buttonPin, INPUT);
    return;
}

bool DebouncingButton::Debounce(){
    int reading = digitalRead(buttonPin);
    bool buttonValue = LOW;

    if (reading != GetLastButtonState()) {

        SetLastDebounceTime(millis());
    }

    if ((millis() - lastDebounceTime) > GetDebounceDelay()) {

        if (reading != GetButtonState()) {
            SetButtonState(reading);

            if (GetButtonState() == HIGH) {
                SetLastButtonState(reading);
                return GetButtonState();
            }
        }
    }

    SetLastButtonState(reading);
    
}