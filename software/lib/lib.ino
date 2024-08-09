#include <Arduino.h>
#include "src/blinking_led/blinking_led.h"

BlinkingLed led1(LED_BUILTIN, LOW, 0, 1000);
BlinkingLed led2(13, LOW, 0, 500);

void setup() {
    Serial.begin(9600);
    led1.InitBlinkLed();
}

void loop() {
    led1.BlinkLed();
    Serial.println("Welcome to the Hypercar Project");
}
