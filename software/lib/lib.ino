#include <Arduino.h>
#include "src/task_scheduler/task_scheduler.h"

#define NUM_TASKS 5

TaskScheduler scheduler(NUM_TASKS);

bool TaskBlinkLed1() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
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

bool TaskEventCheck() {
    return false;
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    scheduler.AddTask(TaskBlinkLed1, 1000, 2, false);
    scheduler.AddTask(TaskPrint, 2000, 1, true);
    scheduler.AddTask(TaskError, 3000, 3, false, 2, 1000, nullptr);

    int taskIndices[] = {0, 1};
    scheduler.AddTaskGroup(taskIndices, 2);

    scheduler.SetTaskDependency(2, 1);
}

void loop() {
    scheduler.Run();
    scheduler.PrintTaskStats();
    scheduler.MonitorResources();
    delay(10000);
}
