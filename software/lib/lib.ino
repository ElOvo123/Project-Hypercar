#include <Arduino.h>
#include "src/debounce_button/debounce_button.h"
#include "src/blinking_led/blinking_led.h"

BlinkingLed led1(LED_BUILTIN, LOW, 0, 1000);
BlinkingLed led2(13, LOW, 0, 500);
DebouncingButton button1(2, LOW, LOW, 50, 0);
DebouncingButton button2(1, LOW, LOW, 50, 0);

void setup() {
    Serial.begin(9600);
    led1.InitBlinkLed();
    led2.InitBlinkLed();
    button1.InitDebounceButton();
    button2.InitDebounceButton();
}

void loop() {
    led1.BlinkLed();
    led2.BlinkLed();
    bool button1State = button1.Debounce();
    bool button2State = button2.Debounce();
}
