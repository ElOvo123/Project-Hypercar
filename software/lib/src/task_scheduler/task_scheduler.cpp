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
    tasks[numTasks].enabled = true;  // Enable the task by default
    numTasks++;
  }
}

void TaskScheduler::EnableTask(int taskIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].enabled = true;
  }
}

void TaskScheduler::DisableTask(int taskIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].enabled = false;
  }
}

void TaskScheduler::Run() {
  unsigned long currentMillis = millis();

  for (int i = 0; i < numTasks; i++) {
    if (tasks[i].enabled && currentMillis - tasks[i].lastRun >= tasks[i].interval) {
      tasks[i].function();
      tasks[i].lastRun = currentMillis;
    }
  }
}
