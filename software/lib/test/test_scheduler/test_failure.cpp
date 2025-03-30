#include "test_common.hpp"

int failure_counter = 0;

void flakyTask(void) {
    if (++failure_counter < 2) 
    {

    }
}

void test_task_retry(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_number_failures(0, 3);
    
    s.retry_task(0);

    TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
}

void test_retry_until_limit_then_fail(void) {
    scheduler s(2);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    s.set_number_failures(0, 0);
    
    s.retry_task(0);
    
    TEST_ASSERT_NOT_EQUAL(TASK_FAILED, s.get_task_state(0));

    s.set_number_failures(0, 1);
    
    s.retry_task(0);

    TEST_ASSERT_NOT_EQUAL(TASK_FAILED, s.get_task_state(0));

    s.set_number_failures(0, 2);

    s.retry_task(0);

    TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
}

void test_escalate_failure_only_called_on_failure(void) {
    scheduler s(2);
    
    s.add_task(dummyTaskFunction, mockFailure, 1000, 1, 500);
    
    failure_called = false;
    
    s.set_number_failures(0, 1);
    
    s.retry_task(0);
    
    TEST_ASSERT_FALSE(failure_called);

    s.set_number_failures(0, 2);
    
    s.retry_task(0);

    TEST_ASSERT_TRUE(failure_called);
}

void test_retry_loop_does_not_hang(void) {
    scheduler s(2);

    
    s.add_task(dummyTaskFunction, mockFailure, 100, 1, 50);
    
    for (int i = 0; i < 100; ++i) 
    {
        s.set_number_failures(0, 2);
        
        s.retry_task(0);

        TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
    }
}

void test_retry_then_recovery(void) 
{
    scheduler s(3);
    
    s.add_task(flakyTask, mockFailure, 1000, 1, 500);
    
    s.set_number_failures(0, 1);
    
    s.retry_task(0);

    TEST_ASSERT_NOT_EQUAL(TASK_FAILED, s.get_task_state(0));
}

void test_null_task_function_does_not_crash(void) {
    scheduler s(3);
    
    s.add_task(nullptr, dummyFailureProcedure, 1000, 1, 500);

    s.set_task_state(0, READY);
    s.set_last_run_time(0, 0);

    while (s.get_current_time() < 1000) {}

    s.run();

    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(0));
}

void test_null_failure_procedure_does_not_crash(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, nullptr, 1000, 1, 500);

    s.set_number_failures(0, 3);
    
    s.retry_task(0);

    TEST_ASSERT_TRUE(true);
}


void run_failure_tests(void) {
    RUN_TEST(test_task_retry);
    RUN_TEST(test_retry_until_limit_then_fail);
    RUN_TEST(test_escalate_failure_only_called_on_failure);
    RUN_TEST(test_retry_loop_does_not_hang);
    RUN_TEST(test_retry_then_recovery);
    RUN_TEST(test_null_task_function_does_not_crash);
    RUN_TEST(test_null_failure_procedure_does_not_crash);
}
