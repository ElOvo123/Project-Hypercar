#include <Arduino.h>
#include "src/blinking_led/blinking_led.h"
#include "src/task_scheduler/task_scheduler.h"

BlinkingLed led1(LED_BUILTIN, LOW);

#define NUM_TASKS 5

TaskScheduler scheduler(NUM_TASKS);

bool TaskBlinkLed1() {
    led1.BlinkLed();
    return true;
}

bool TaskPrint() {
    Serial.println("Welcome to the Hypercar Project");
    return true;
}

bool TaskError() {
    Serial.println("This task will always fail.");
    return false;
}

void setup() {
    Serial.begin(9600);
    led1.InitBlinkLed();

    scheduler.AddTask(TaskBlinkLed1, 1000, 2, false);
    scheduler.AddTask(TaskPrint, 2000, 1, true);
    scheduler.AddTask(TaskError, 3000, 3, false, 2);

    scheduler.SetTaskDependency(2, 1);

    delay(5000);
    scheduler.DisableTask(1);
}

void loop() {
    scheduler.Run();
    scheduler.PrintTaskStats();
    delay(10000);
}
