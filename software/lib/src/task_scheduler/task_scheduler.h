#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

typedef bool (*TaskFunction)();

class TaskScheduler {
public:
    TaskScheduler(int maxTasks);
    ~TaskScheduler();

    void AddTask(TaskFunction function, unsigned long interval, int priority, bool oneTime = false, int maxErrors = 3);
    void RemoveTask(int taskIndex);
    void EnableTask(int taskIndex);
    void DisableTask(int taskIndex);
    void SuspendTask(int taskIndex);
    void ResumeTask(int taskIndex);
    void SetTaskDependency(int taskIndex, int dependencyIndex);
    void Run();
    void PrintTaskStats();
    
private:
    struct Task {
        TaskFunction function;
        unsigned long interval;
        unsigned long lastRun;
        bool enabled;
        bool suspended;
        bool oneTime;
        int priority;
        int errorCount;
        int maxErrors;
        int dependencyIndex;
        unsigned long totalTime;
        unsigned long lastExecutionTime;
    };

    Task* tasks;
    int maxTasks;
    int numTasks;

    void SortTasksByPriority();
    void UpdateTaskStats(int taskIndex);
};

#endif
