#include <Arduino.h>
#include "src/debounce_button/debounce_button.h"
#include "src/blinking_led/blinking_led.h"

BlinkingLed led1(LED_BUILTIN, LOW, 0, 1000);
BlinkingLed led2(13, LOW, 0, 500);

void setup() {
    Serial.begin(9600);
    led1.InitBlinkLed();
    led2.InitBlinkLed();
}

void loop() {
    sayHello();
    led1.BlinkLed();
    led2.BlinkLed();
}
