#include "task_scheduler.h"
#include <Arduino.h>

TaskScheduler::TaskScheduler(int maxTasks) : maxTasks(maxTasks), numTasks(0) {
    tasks = new Task[maxTasks];
}

TaskScheduler::~TaskScheduler() {
    delete[] tasks;
}

void TaskScheduler::AddTask(TaskFunction function, unsigned long interval) {
    if (numTasks < maxTasks) {
        tasks[numTasks].function = function;
        tasks[numTasks].interval = interval;
        tasks[numTasks].lastRun = 0;
        numTasks++;
    }
}

void TaskScheduler::Run() {
    unsigned long currentMillis = millis();

    for (int i = 0; i < numTasks; i++) {
        if (currentMillis - tasks[i].lastRun >= tasks[i].interval) {
            tasks[i].function();
            tasks[i].lastRun = currentMillis;
        }
    }
}
