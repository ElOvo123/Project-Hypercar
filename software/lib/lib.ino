#include <Arduino.h>
#include "src/debounce_button/debounce_button.h"
#include "src/blinking_led/blinking_led.h"

void setup() {
    Serial.begin(9600);
    InitBlinkLed(LED_BUILTIN, LOW, 0, 1000);
}

void loop() {
    sayHello();
    BlinkLed();
}
