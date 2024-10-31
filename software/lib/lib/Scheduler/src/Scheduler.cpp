#include "Scheduler.h"
#include "Arduino.h"

scheduler::scheduler() : task_count(0){
}

scheduler::~scheduler(){
}

void scheduler::run_task(int task){
    task_list[task].task_function();
}

void scheduler::add_task_count(){
    task_count++;
}

void scheduler::set_task_function(int task, void (*task_function)()){
    task_list[task].task_function = task_function;
}

void scheduler::set_running_period(int task, unsigned long running_period){
    task_list[task].running_period = running_period;
}

void scheduler::set_last_run_time(int task, unsigned long last_run_time){
    task_list[task].last_run_time = last_run_time;
}

void scheduler::set_priority(int task, int priority){
    task_list[task].priority = priority;
}

void scheduler::set_task_is_running(int task, bool task_is_running){
    task_list[task].task_is_running = task_is_running;
}

void scheduler::set_task_state(int task, task_state current_state){
    task_list[task].current_state = current_state;
}

void scheduler::set_delay_until_unblock(int task, unsigned long delay_until_unblock){
    task_list[task].delay_until_unblock = delay_until_unblock;
}

void scheduler::set_max_execution_time(int task, unsigned long max_execution_time){
    task_list[task].max_execution_time = max_execution_time;
}

void scheduler::set_number_failures(int task, int number_of_failures){
    task_list[task].failures = number_of_failures;
}

void scheduler::retry_task(int task){
    if (get_number_of_failures(task) < retry_limit)
    {
        run_task(task);
    }else{
        escalate_task_failure();
        
    }
}

unsigned long scheduler::get_current_time(){
    return millis();
}

unsigned long scheduler::get_task_last_run_time(int task){
    return task_list[task].last_run_time;
}

unsigned long scheduler::get_task_running_period(int task){
    return task_list[task].running_period;
}

unsigned long scheduler::get_delay_until_unblock(int task){
    return task_list[task].delay_until_unblock;
}

unsigned long scheduler::get_max_execution_time(int task){
    return task_list[task].max_execution_time;
}

int scheduler::get_max_number_of_tasks(){
    return max_number_of_tasks;
}

int scheduler::get_task_priority(int task){
    return task_list[task].priority;
}

int scheduler::get_number_of_failures(int task){
    return task_list[task].failures;
}

task_state scheduler::get_task_state(int task){
    return task_list[task].current_state;
}

void scheduler::add_task(void (*task_function) (), unsigned long running_period, unsigned long priority, unsigned long max_execution_time){
    if (task_count < max_number_of_tasks)
    {
        set_task_function(task_count, task_function);
        set_running_period(task_count, running_period);
        set_last_run_time(task_count, 0);
        set_priority(task_count, priority);
        set_task_is_running(task_count, false);
        set_task_state(task_count, READY);
        set_delay_until_unblock(task_count, 0);
        set_number_failures(task_count, 0);
        set_max_execution_time(task_count, max_execution_time);
        add_task_count();
    }
}

void scheduler::delay_task(int task, unsigned long delay_until_unblock){
    set_task_state(task, BLOCKED);
    set_delay_until_unblock(task, get_current_time() + delay_until_unblock);
}

void scheduler::run(void){
    unsigned long current_time = get_current_time();
    int highest_priority_task = -1;
    int max_priority = -1;

    for (int task = 0; task < get_max_number_of_tasks(); task++)
    {   
        if (get_task_state(task) == BLOCKED)
        {
            if (current_time >= get_delay_until_unblock(task))
            {
                set_task_state(task, READY);
            }else{
                continue;
            }
        }

        if (get_task_state(task) == READY)
        {
            if (current_time - get_task_last_run_time(task) >=  get_task_running_period(task))
            {
                if (get_task_priority(task) > max_priority)
                {
                    highest_priority_task = task;
                    max_priority = get_task_priority(task);
                }
            }
        }
    }

    if(highest_priority_task != -1){
        set_last_run_time(highest_priority_task, current_time);
        set_task_state(highest_priority_task, RUNNING);
 
        unsigned long start_time = get_current_time();

        run_task(highest_priority_task);

        unsigned long execution_time = get_current_time() - start_time;

        if (execution_time > get_max_execution_time(highest_priority_task))
        {
            if (get_number_of_failures(highest_priority_task) < retry_limit)
            {
                

            }else{
                set_task_state(highest_priority_task, TASK_FAILED);

            }
        }else{
            set_task_state(highest_priority_task, READY);
        }
    }
}