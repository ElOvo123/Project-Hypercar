#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

enum task_state
{
    READY,
    RUNNING,
    BLOCKED,
    SUSPENDED,
    TASK_FAILED
};

struct task_control_block
{
    void (*task_function)();
    unsigned long running_period;
    unsigned long last_run_time;
    int priority;
    bool task_is_running;
    task_state current_state;
    unsigned long delay_until_unblock;
    unsigned long max_execution_time;
    int failures;
};

class scheduler
{
private:
    static const int max_number_of_tasks = 10;
    int task_count;
    int retry_limit;
    task_control_block task_list[max_number_of_tasks];

    void run_task(int task);
    void add_task_count(void);

    void set_task_function(int task, void (*task_function)());
    void set_running_period(int task,unsigned long running_period);
    void set_last_run_time(int task, unsigned long last_run_time);
    void set_priority(int task, int priority);
    void set_task_is_running(int task, bool task_is_running);
    void set_task_state(int task, task_state current_state);
    void set_delay_until_unblock(int task, unsigned long delay_until_unblock);
    void set_max_execution_time(int task, unsigned long max_execution_time);
    void set_number_failures(int task, int number_of_failures);
    void retry_task(int task);

    unsigned long get_current_time(void);
    unsigned long get_task_last_run_time(int task);
    unsigned long get_task_running_period(int task);
    unsigned long get_delay_until_unblock(int task);
    unsigned long get_max_execution_time(int task);

    int get_max_number_of_tasks(void);
    int get_task_priority(int task);
    int get_number_of_failures(int task);

    task_state get_task_state(int task);

public:
    scheduler(void);
    void add_task(void (*task_function)(), unsigned long running_period, unsigned long priority, unsigned long max_execution_time);
    void delay_task(int task, unsigned long delay_until_unblock);
    void run(void);
    ~scheduler(void);
};

#endif