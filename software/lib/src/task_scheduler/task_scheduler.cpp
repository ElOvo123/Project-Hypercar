#include "task_scheduler.h"
#include <Arduino.h>

TaskScheduler::TaskScheduler(int maxTasks) : maxTasks(maxTasks), numTasks(0) {
  tasks = new Task[maxTasks];
}

TaskScheduler::~TaskScheduler() {
  delete[] tasks;
}

void TaskScheduler::AddTask(TaskFunction function, unsigned long interval, int priority, bool oneTime, int maxErrors) {
  if (numTasks < maxTasks) {
    tasks[numTasks].function = function;
    tasks[numTasks].interval = interval;
    tasks[numTasks].lastRun = 0;
    tasks[numTasks].enabled = true;
    tasks[numTasks].suspended = false;
    tasks[numTasks].oneTime = oneTime;
    tasks[numTasks].priority = priority;
    tasks[numTasks].errorCount = 0;
    tasks[numTasks].maxErrors = maxErrors;
    tasks[numTasks].dependencyIndex = -1;
    tasks[numTasks].totalTime = 0;
    tasks[numTasks].lastExecutionTime = 0;
    numTasks++;
    SortTasksByPriority();
  }
}

void TaskScheduler::RemoveTask(int taskIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    for (int i = taskIndex; i < numTasks - 1; i++) {
      tasks[i] = tasks[i + 1];
    }
    numTasks--;
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

void TaskScheduler::SuspendTask(int taskIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].suspended = true;
  }
}

void TaskScheduler::ResumeTask(int taskIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].suspended = false;
  }
}

void TaskScheduler::SetTaskDependency(int taskIndex, int dependencyIndex) {
  if (taskIndex >= 0 && taskIndex < numTasks && dependencyIndex >= 0 && dependencyIndex < numTasks) {
    tasks[taskIndex].dependencyIndex = dependencyIndex;
  }
}

void TaskScheduler::Run() {
  unsigned long currentMillis = millis();

  for (int i = 0; i < numTasks; i++) {
    if (tasks[i].enabled && !tasks[i].suspended && currentMillis - tasks[i].lastRun >= tasks[i].interval) {
      if (tasks[i].dependencyIndex == -1 || tasks[tasks[i].dependencyIndex].lastExecutionTime > tasks[i].lastExecutionTime) {
        bool success = tasks[i].function();
        UpdateTaskStats(i);
        if (!success) {
          tasks[i].errorCount++;
          if (tasks[i].errorCount >= tasks[i].maxErrors) {
            tasks[i].enabled = false;
          }
        } else {
          tasks[i].errorCount = 0;
        }
        tasks[i].lastRun = currentMillis;
        tasks[i].lastExecutionTime = currentMillis;
        tasks[i].totalTime += millis() - tasks[i].lastExecutionTime;

        if (tasks[i].oneTime) {
          RemoveTask(i);
          i--;
        }
      }
    }
  }
}

void TaskScheduler::SortTasksByPriority() {
  for (int i = 0; i < numTasks - 1; i++) {
    for (int j = 0; j < numTasks - i - 1; j++) {
      if (tasks[j].priority < tasks[j + 1].priority) {
        Task temp = tasks[j];
        tasks[j] = tasks[j + 1];
        tasks[j + 1] = temp;
      }
    }
  }
}

void TaskScheduler::UpdateTaskStats(int taskIndex) {
  unsigned long currentMillis = millis();
  tasks[taskIndex].totalTime += currentMillis - tasks[taskIndex].lastExecutionTime;
}

void TaskScheduler::PrintTaskStats() {
  Serial.println("Task Statistics:");
  for (int i = 0; i < numTasks; i++) {
    Serial.print("Task ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("Total Time: ");
    Serial.print(tasks[i].totalTime);
    Serial.print(" ms, Last Execution: ");
    Serial.println(tasks[i].lastExecutionTime);
  }
}
