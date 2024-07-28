#include <Arduino.h>
#include "src/debounce_button/debounce_button.h"
#include "src/blinking_led/blinking_led.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    sayHello();
    sayHelloAgain();
}
