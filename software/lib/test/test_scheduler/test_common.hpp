#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <stdio.h>
#include <unity.h>
#include <scheduler.h>

extern bool failure_called;

void dummyTaskFunction();
void dummyFailureProcedure();
void mockFailure();

void run_core_tests();
void run_timing_tests();
void run_priority_tests();
void run_failure_tests();
void run_edge_case_tests();

#endif
