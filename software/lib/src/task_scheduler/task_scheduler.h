#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <Arduino.h>

typedef bool (*TaskFunction)();

enum PriorityMode {
    FIXED_PRIORITY,
    ROUND_ROBIN,
    WEIGHTED_PRIORITY
};

class TaskScheduler {
public:
    TaskScheduler(int maxTasks);
    ~TaskScheduler();

    void AddTask(TaskFunction function, unsigned long interval, int priority, bool oneTime = false, int maxErrors = 3, unsigned long timeout = 1000, TaskFunction fallbackFunction = nullptr);
    void RemoveTask(int taskIndex);
    void EnableTask(int taskIndex);
    void DisableTask(int taskIndex);
    void SuspendTask(int taskIndex);
    void ResumeTask(int taskIndex);
    void SetTaskDependency(int taskIndex, int dependencyIndex);
    void SetTaskInterval(int taskIndex, unsigned long newInterval);
    void SetPriorityMode(PriorityMode mode);
    void Run();
    void PrintTaskStats();
    void BoostTaskPriority(int taskIndex, int boostAmount);
    void AddTaskGroup(int* taskIndices, int numTasks);
    void EnableTaskGroup(int groupIndex);
    void DisableTaskGroup(int groupIndex);
    void MonitorResources();

private:
    struct Task {
        TaskFunction function;
        TaskFunction fallbackFunction;
        TaskFunction eventCheckFunction;
        unsigned long interval;
        unsigned long lastRun;
        unsigned long timeout;
        bool enabled;
        bool suspended;
        bool oneTime;
        int priority;
        int errorCount;
        int maxErrors;
        int dependencyIndex;
        unsigned long totalTime;
        unsigned long lastExecutionTime;
        bool timedOut;
        unsigned long minExecutionTime;
        unsigned long maxExecutionTime;
        unsigned long avgExecutionTime;
        unsigned long executionCount;
        unsigned int memoryUsage;
        unsigned int cpuUsage;
        bool eventTriggered;
    };

    struct TaskGroup {
        int* taskIndices;
        int numTasks;
    };

    Task* tasks;
    int maxTasks;
    int numTasks;
    TaskGroup* taskGroups;
    int numGroups;
    PriorityMode currentPriorityMode;

    void SortTasksByPriority();
    void UpdateTaskStats(int taskIndex, unsigned long executionTime);
};

#endif
