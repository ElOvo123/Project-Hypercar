#include "scheduler.h"

#ifndef ARDUINO
#include <chrono>

unsigned long millis() {
    static auto start_time = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
    return duration.count();
}
#endif


scheduler::scheduler(int retry_limit) : task_count(0), retry_limit(retry_limit){
}

scheduler::~scheduler(){
}

bool scheduler::run_task(int task) {
    if (is_task_valid(task)) 
    {
        if (!task_list[task].task_function) 
        {
            return false;
        }

        task_list[task].task_function();
        
        set_number_failures(task, INITIAL_FAILURES);

        return true;
    }

    return false;
}


void scheduler::add_task_count(){
    task_count++;
}

void scheduler::set_task_function(int task, void (*task_function)()){
    if (is_task_valid(task))
    {
        task_list[task].task_function = task_function;   
    }
}

void scheduler::set_task_failure_procedure(int task, void (*task_failure_procedure)()){
    if (is_task_valid(task))
    {
        task_list[task].task_failure_procedure = task_failure_procedure;
    }
}

void scheduler::set_running_period(int task, unsigned long running_period){
    if (is_task_valid(task))
    {
        task_list[task].running_period = running_period;   
    }
}

void scheduler::set_last_run_time(int task, unsigned long last_run_time){
    if (is_task_valid(task))
    {
        task_list[task].last_run_time = last_run_time;
    }
}

void scheduler::set_priority(int task, int priority){
    if (is_task_valid(task))
    {
        task_list[task].priority = priority;
    }
}

void scheduler::set_task_is_running(int task, bool task_is_running){
    if (is_task_valid(task))
    {
        task_list[task].task_is_running = task_is_running;
    }
}

void scheduler::set_task_state(int task, task_state current_state){
    if (is_task_valid(task)) 
    {
        task_list[task].current_state = current_state;
    }
}


void scheduler::set_delay_until_unblock(int task, unsigned long delay_until_unblock){
    if (is_task_valid(task))
    {
        task_list[task].delay_until_unblock = delay_until_unblock;
    }
}

void scheduler::set_max_execution_time(int task, unsigned long max_execution_time){
    if (is_task_valid(task))
    {
        task_list[task].max_execution_time = max_execution_time;
    }
}

void scheduler::set_number_failures(int task, int number_of_failures){
    if (is_task_valid(task))
    {
        task_list[task].failures = number_of_failures;
    }
}

void scheduler::set_original_priority(int task, int original_priority){
    if (is_task_valid(task))
    {
        task_list[task].original_priority = original_priority;
    }
}

void scheduler::retry_task(int task){
    if (!is_task_valid(task)) 
    {
        return;
    }

    if (get_number_of_failures(task) < retry_limit) 
    {
        run_task(task);
    } else {
        set_task_state(task, TASK_FAILED);
        escalate_task_failure(task);
    }
}


void scheduler::escalate_task_failure(int task)
{
    if (!is_task_valid(task)) {
        return;
    }

    if (!task_list[task].task_failure_procedure) {
        return;
    }

    task_list[task].task_failure_procedure();
}



void scheduler::lock_resource(int task){
    if (is_task_valid(task) && get_is_task_running(task)) 
    {
        for (int current_task = 0; current_task < get_current_number_of_tasks(); current_task++) 
        {
            if (current_task != task && get_task_state(current_task) == READY && get_task_priority(current_task) > get_task_priority(task)) 
            {
                set_original_priority(task, get_task_priority(task));
                set_priority(task, get_task_priority(current_task));
                break;
            }
        }
    }
}

void scheduler::unlock_resource(int task){
    int original_priority = get_task_original_priority(task);

    if (original_priority != NO_PRIORITY) 
    {
        set_priority(task, original_priority);
        set_original_priority(task, NO_PRIORITY);
    }
}


unsigned long scheduler::get_current_time(){
    return millis();
}

unsigned long scheduler::get_task_last_run_time(int task){
    if (is_task_valid(task))
    {
        return task_list[task].last_run_time;
    }else{
        return 0;
    }
}

unsigned long scheduler::get_task_running_period(int task){
    if (is_task_valid(task))
    {
        return task_list[task].running_period;
    }else{
        return 0;
    }
}

unsigned long scheduler::get_delay_until_unblock(int task){
    if (is_task_valid(task))
    {
        return task_list[task].delay_until_unblock;
    }else{
        return 0;
    }
}

unsigned long scheduler::get_max_execution_time(int task){
    if (is_task_valid(task))
    {
        return task_list[task].max_execution_time;
    }else{
        return 0;
    }
}

int scheduler::get_max_number_of_tasks(){
    return max_number_of_tasks;
}

int scheduler::get_task_priority(int task){
    if (is_task_valid(task))
    {
        return task_list[task].priority;
    }else{
        return 0;
    }
}

int scheduler::get_number_of_failures(int task){
    if (is_task_valid(task))
    {
        return task_list[task].failures;
    }else{
        return 0;
    }
}

int scheduler::get_task_original_priority(int task){
    if (is_task_valid(task))
    {
        return task_list[task].original_priority;
    }else{
        return 0;
    }
}

int scheduler::get_current_number_of_tasks(){
    return task_count;
}

bool scheduler::is_task_valid(int task){
    if (task >= 0 && task < get_current_number_of_tasks())
    {
        return true;
    }else{
        return false;
    }
}

bool scheduler::get_is_task_running(int task){
    if (is_task_valid(task))
    {
        return task_list[task].task_is_running;
    }else{
        return false;
    }
}

task_state scheduler::get_task_state(int task){
    if (!is_task_valid(task)) 
    {
        return BLOCKED;
    }

    return task_list[task].current_state;
}


bool scheduler::add_task(void (*task_function)(), void (*task_failure_procedure)(), unsigned long running_period, unsigned long priority, unsigned long max_execution_time) {

    if (task_count >= max_number_of_tasks) 
    {
        return false;
    }

    int task = task_count;

    task_list[task].task_function = task_function;
    task_list[task].task_failure_procedure = task_failure_procedure;
    task_list[task].running_period = running_period;
    task_list[task].last_run_time = 0;
    task_list[task].priority = priority;
    task_list[task].task_is_running = false;
    task_list[task].current_state = READY;
    task_list[task].delay_until_unblock = 0;
    task_list[task].failures = 0;
    task_list[task].max_execution_time = max_execution_time;
    task_list[task].original_priority = priority;

    task_count++;
    return true;
}


void scheduler::delay_task(int task, unsigned long delay_until_unblock){
    set_task_state(task, BLOCKED);
    set_delay_until_unblock(task, get_current_time() + delay_until_unblock);
}

void scheduler::run(void){
    unsigned long current_time = get_current_time();
    int highest_priority_task = INVALID_TASK;
    int max_priority = NO_PRIORITY;

    for (int task = 0; task < task_count; task++) {

        if (get_task_state(task) == BLOCKED && current_time >= get_delay_until_unblock(task)) 
        {
            set_task_state(task, READY);
        }

        if (get_task_state(task) == READY && (current_time - get_task_last_run_time(task) >= get_task_running_period(task)))
        {
            
            int priority = get_task_priority(task);
            if (highest_priority_task == INVALID_TASK || priority > max_priority) 
            {
                highest_priority_task = task;
                max_priority = priority;
            }
        }
    }

    if (highest_priority_task != INVALID_TASK) {
        get_current_time();

        bool success = run_task(highest_priority_task);

        if (success) 
        {
            set_last_run_time(highest_priority_task, current_time);
            set_task_state(highest_priority_task, READY);
        } else {
            set_task_state(highest_priority_task, TASK_FAILED);
        }

        unlock_resource(highest_priority_task);
    }

}

void scheduler::reset(void) {
    task_count = 0;

    for (int i = 0; i < max_number_of_tasks; ++i) 
    {
        task_list[i] = task_control_block{};
    }
}

bool scheduler::remove_task(int task_id) {

    if (!is_task_valid(task_id))
    {
        return false;
    } 

    for (int i = task_id; i < task_count - 1; ++i) 
    {
        task_list[i] = task_list[i + 1];
    }

    task_list[task_count - 1] = task_control_block{};
    
    task_count--;
    
    return true;
}

void scheduler::promote_task_priority(int task_id, int new_priority) {
    if (is_task_valid(task_id)) 
    {
        if (new_priority > get_task_priority(task_id)) 
        {
            set_priority(task_id, new_priority);
        }
    }
}

void scheduler::preempt_running_task(int new_task_id) {
    if (!is_task_valid(new_task_id)) 
    {
        return;
    }

    int current_running = INVALID_TASK;

    for (int i = 0; i < task_count; ++i) 
    {
        if (task_list[i].current_state == RUNNING) 
        {
            current_running = i;
            break;
        }
    }

    if (current_running != INVALID_TASK && get_task_priority(new_task_id) > get_task_priority(current_running)) 
    {
        set_task_state(current_running, READY);
        set_task_state(new_task_id, RUNNING);
        set_last_run_time(new_task_id, get_current_time());
    }
}

bool scheduler::run_interrupt_safe(void) {
    int task_to_run = INVALID_TASK;
    unsigned long now = get_current_time();
    int max_priority = NO_PRIORITY;

    for (int i = 0; i < task_count; ++i) 
    {
        if (task_list[i].current_state == READY && now - task_list[i].last_run_time >= task_list[i].running_period && task_list[i].priority > max_priority) 
        {
            task_to_run = i;
            max_priority = task_list[i].priority;
        }
    }

    if (task_to_run == INVALID_TASK)
    {
        return false;
    }

    set_last_run_time(task_to_run, now);
    task_list[task_to_run].current_state = RUNNING;
    
    run_task(task_to_run);
    task_list[task_to_run].current_state = READY;

    return true;
}
