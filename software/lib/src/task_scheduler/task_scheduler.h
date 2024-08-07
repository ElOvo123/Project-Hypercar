#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

typedef void (*TaskFunction)();

class TaskScheduler {
public:
    TaskScheduler(int maxTasks);
    ~TaskScheduler();

    void AddTask(TaskFunction function, unsigned long interval);
    void Run();

private:
    struct Task {
        TaskFunction function;
        unsigned long interval;
        unsigned long lastRun;
    };

    Task* tasks;
    int maxTasks;
    int numTasks;
};

#endif
