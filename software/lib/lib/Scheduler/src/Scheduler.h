#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

const int NO_PRIORITY = -1;
const int INITIAL_FAILURES = 0;
const int INVALID_TASK = -1;

enum task_state
{
    READY,
    RUNNING,
    BLOCKED,
    TASK_FAILED
};

struct task_control_block
{
    void (*task_function)();
    void (*task_failure_procedure)();

    unsigned long running_period;
    unsigned long last_run_time;
    unsigned long delay_until_unblock;
    unsigned long max_execution_time;
    
    int priority;
    int failures;
    int original_priority;

    bool task_is_running;
    
    task_state current_state;
};

class scheduler
{
private:
    static const int max_number_of_tasks = 10;
    int task_count;
    int retry_limit;
    task_control_block task_list[max_number_of_tasks];

    bool run_task(int task);
    void add_task_count(void);

    void set_task_function(int task, void (*task_function)());
    void set_task_failure_procedure(int task, void (*task_failure_procedure)());
    void set_running_period(int task,unsigned long running_period);
    void set_last_run_time(int task, unsigned long last_run_time);
    void set_priority(int task, int priority);
    void set_task_is_running(int task, bool task_is_running);
    void set_task_state(int task, task_state current_state);
    void set_delay_until_unblock(int task, unsigned long delay_until_unblock);
    void set_max_execution_time(int task, unsigned long max_execution_time);
    void set_number_failures(int task, int number_of_failures);
    void set_original_priority(int task, int original_priority);
    void retry_task(int task);
    void escalate_task_failure(int task);
    void lock_resource(int task);
    void unlock_resource(int task);

    unsigned long get_current_time(void);
    unsigned long get_task_last_run_time(int task);
    unsigned long get_task_running_period(int task);
    unsigned long get_delay_until_unblock(int task);
    unsigned long get_max_execution_time(int task);

    int get_max_number_of_tasks(void);
    int get_task_priority(int task);
    int get_number_of_failures(int task);
    int get_task_original_priority(int task);
    int get_current_number_of_tasks(void);

    bool is_task_valid(int task);
    bool get_is_task_running(int task);

    task_state get_task_state(int task);

public:
    scheduler(int retry_limit);
    bool add_task(void (*task_function)(), void (*task_failure_procedure)(), unsigned long running_period, unsigned long priority, unsigned long max_execution_time);
    void delay_task(int task, unsigned long delay_until_unblock);
    void run(void);
    ~scheduler(void);
};

#endif