#include "task_scheduler.h"

#ifndef ULONG_MAX
#define ULONG_MAX 4294967295UL // Maximum value for a 32-bit unsigned long
#endif

TaskScheduler::TaskScheduler(int maxTasks) : maxTasks(maxTasks), numTasks(0), numGroups(0), currentPriorityMode(FIXED_PRIORITY) {
  tasks = new Task[maxTasks];
  taskGroups = nullptr;
}

TaskScheduler::~TaskScheduler() {
  delete[] tasks;
  if (taskGroups != nullptr) {
    delete[] taskGroups;
  }
}

void TaskScheduler::AddTask(TaskFunction function, unsigned long interval, int priority, bool oneTime, int maxErrors, unsigned long timeout, TaskFunction fallbackFunction) {
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
    tasks[numTasks].timeout = timeout;
    tasks[numTasks].timedOut = false;
    tasks[numTasks].minExecutionTime = ULONG_MAX;
    tasks[numTasks].maxExecutionTime = 0;
    tasks[numTasks].avgExecutionTime = 0;
    tasks[numTasks].executionCount = 0;
    tasks[numTasks].memoryUsage = 0;
    tasks[numTasks].cpuUsage = 0;
    tasks[numTasks].eventTriggered = false;
    tasks[numTasks].fallbackFunction = fallbackFunction;
    tasks[numTasks].eventCheckFunction = nullptr;

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

void TaskScheduler::SetTaskInterval(int taskIndex, unsigned long newInterval) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].interval = newInterval;
  }
}

void TaskScheduler::SetPriorityMode(PriorityMode mode) {
  currentPriorityMode = mode;
}

void TaskScheduler::BoostTaskPriority(int taskIndex, int boostAmount) {
  if (taskIndex >= 0 && taskIndex < numTasks) {
    tasks[taskIndex].priority += boostAmount;
    SortTasksByPriority();
  }
}

void TaskScheduler::AddTaskGroup(int* taskIndices, int numTasks) {
  TaskGroup* newGroups = new TaskGroup[numGroups + 1];

  for (int i = 0; i < numGroups; i++) {
    newGroups[i] = taskGroups[i];
  }

  newGroups[numGroups].taskIndices = taskIndices;
  newGroups[numGroups].numTasks = numTasks;
  numGroups++;

  if (taskGroups != nullptr) {
    delete[] taskGroups;
  }

  taskGroups = newGroups;
}

void TaskScheduler::EnableTaskGroup(int groupIndex) {
  if (groupIndex >= 0 && groupIndex < numGroups) {
    for (int i = 0; i < taskGroups[groupIndex].numTasks; i++) {
      EnableTask(taskGroups[groupIndex].taskIndices[i]);
    }
  }
}

void TaskScheduler::DisableTaskGroup(int groupIndex) {
  if (groupIndex >= 0 && groupIndex < numGroups) {
    for (int i = 0; i < taskGroups[groupIndex].numTasks; i++) {
      DisableTask(taskGroups[groupIndex].taskIndices[i]);
    }
  }
}

void TaskScheduler::Run() {
  unsigned long currentMillis = millis();

  for (int i = 0; i < numTasks; i++) {
    if (tasks[i].enabled && !tasks[i].suspended && (tasks[i].eventTriggered || currentMillis - tasks[i].lastRun >= tasks[i].interval)) {
      if (tasks[i].eventCheckFunction != nullptr) {
        tasks[i].eventTriggered = tasks[i].eventCheckFunction();
      }

      if (tasks[i].dependencyIndex == -1 || tasks[tasks[i].dependencyIndex].lastExecutionTime > tasks[i].lastExecutionTime) {
        unsigned long startTime = millis();
        bool success = tasks[i].function();
        unsigned long executionTime = millis() - startTime;

        UpdateTaskStats(i, executionTime);

        if (!success) {
            tasks[i].errorCount++;
            if (tasks[i].fallbackFunction != nullptr) {
                tasks[i].fallbackFunction();
            }
            if (tasks[i].errorCount >= tasks[i].maxErrors) {
                DisableTask(i);
            }
        } else {
            tasks[i].errorCount = 0;
        }

        tasks[i].lastRun = currentMillis;

        if (tasks[i].oneTime) {
            DisableTask(i);
        }
      }
    }
  }
}

void TaskScheduler::MonitorResources() {
  extern int __heap_start, *__brkval;
  int v;
  int freeMemory = (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);

  unsigned long totalTaskTime = 0;
  
  for (int i = 0; i < numTasks; i++) {
    totalTaskTime += tasks[i].totalTime;
  }

  unsigned long cpuUsage = (totalTaskTime * 100) / millis();

  Serial.print("Free Memory: ");
  Serial.print(freeMemory);
  Serial.println(" bytes");

  Serial.print("CPU Usage: ");
  Serial.print(cpuUsage);
  Serial.println(" %");

  for (int i = 0; i < numTasks; i++) {
    tasks[i].totalTime = 0;
  }
}

void TaskScheduler::PrintTaskStats() {
  Serial.println("Task Stats:");
  for (int i = 0; i < numTasks; i++) {
    Serial.print("Task ");
    Serial.print(i);
    Serial.print(": Priority: ");
    Serial.print(tasks[i].priority);
    Serial.print(", Interval: ");
    Serial.print(tasks[i].interval);
    Serial.print(", Last Run: ");
    Serial.print(tasks[i].lastRun);
    Serial.print(", Avg Exec Time: ");
    Serial.print(tasks[i].avgExecutionTime);
    Serial.println(" ms");
  }
}

void TaskScheduler::SortTasksByPriority() {
  for (int i = 0; i < numTasks - 1; i++) {
    for (int j = i + 1; j < numTasks; j++) {
      if (tasks[i].priority < tasks[j].priority) {
        Task temp = tasks[i];
        tasks[i] = tasks[j];
        tasks[j] = temp;
      }
    }
  }
}

void TaskScheduler::UpdateTaskStats(int taskIndex, unsigned long executionTime) {
  Task& task = tasks[taskIndex];
  task.executionCount++;
  task.totalTime += executionTime;

  task.minExecutionTime = min(task.minExecutionTime, executionTime);
  task.maxExecutionTime = max(task.maxExecutionTime, executionTime);
  task.avgExecutionTime = task.totalTime / task.executionCount;

  if (executionTime > task.timeout) {
    task.timedOut = true;
  }
}
