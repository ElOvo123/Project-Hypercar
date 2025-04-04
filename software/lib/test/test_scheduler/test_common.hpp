#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <stdio.h>
#include <unity.h>
#include <string>
#include <scheduler.h>

extern bool failure_called;

void dummyTaskFunction(void);
void dummyFailureProcedure(void);
void mockFailure(void);
void add_random_tasks(scheduler &s, int count);
void seed_random(void);
void add_mixed_state_tasks(scheduler &s, int count);
void log_to_csv(int task_id, int priority, const char *event);

void run_stress_tests(void);
void run_core_tests(void);
void run_timing_tests(void);
void run_priority_tests(void);
void run_failure_tests(void);
void run_edge_case_tests(void);
void run_utility_tests(void);
void run_dynamic_tests(void);
void run_preempt_tests(void);
void run_interrupt_tests(void);

#endif