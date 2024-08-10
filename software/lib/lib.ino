#include <Arduino.h>
#include "src/blinking_led/blinking_led.h"
#include "src/task_scheduler/task_scheduler.h"

BlinkingLed led1(LED_BUILTIN, LOW);

#define NUM_TASKS 3

TaskScheduler scheduler(NUM_TASKS);

void TaskBlinkLed1() {
    led1.BlinkLed();
}

void TaskPrint() {
    Serial.println("Welcome to the Hypercar Project");
}

void setup() {
    Serial.begin(9600);
    led1.InitBlinkLed();

    scheduler.AddTask(TaskBlinkLed1, 1000);
    scheduler.AddTask(TaskPrint, 2000);
    
    delay(5000);
    scheduler.DisableTask(1);
}

void loop() {
    scheduler.Run();
}
