#include "test_common.hpp"

void test_delay_prevents_early_run() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.delay_task(0, 2000);
    
    s.run();
    
    TEST_ASSERT_EQUAL(BLOCKED, s.get_task_state(0));
}

void test_double_unlock_restores_priority_once() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    
    s.set_task_is_running(0, true);
    
    s.lock_resource(0);
    
    s.unlock_resource(0);
    s.unlock_resource(0);

    TEST_ASSERT_EQUAL(1, s.get_task_priority(0));
}

void test_task_reset_after_failure() {
    scheduler s(2);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_state(0, TASK_FAILED);
    
    TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
    
    s.set_task_state(0, READY);
    
    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}

void test_task_starvation_prevention_basic() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 10, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_state(0, READY);
    s.set_task_state(1, READY);
    
    while (s.get_current_time() < 10000) 
    {

    }
    
    s.run();
    
    s.set_task_state(0, BLOCKED);
    
    s.run();
    
    TEST_ASSERT_NOT_EQUAL(0, s.get_task_last_run_time(1));
}

void test_blocked_task_does_not_run_even_if_high_priority() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, BLOCKED);
    
    s.set_delay_until_unblock(0, s.get_current_time() + 10000);
    
    s.run();
    
    TEST_ASSERT_EQUAL(BLOCKED, s.get_task_state(0));
    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(0));
}

void test_priority_restoration_on_unlock_only_once() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);
    
    s.set_task_is_running(0, true);
    
    s.lock_resource(0);
    
    TEST_ASSERT_EQUAL(5, s.get_task_priority(0));
    
    s.unlock_resource(0);
    s.unlock_resource(0);
    
    TEST_ASSERT_EQUAL(2, s.get_task_priority(0));
}

void test_run_does_nothing_when_no_tasks_ready() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_state(0, BLOCKED);
    
    s.set_delay_until_unblock(0, s.get_current_time() + 10000);
    
    unsigned long before = s.get_task_last_run_time(0);
    
    s.run();
    
    unsigned long after = s.get_task_last_run_time(0);
    
    TEST_ASSERT_EQUAL(before, after);
}

void test_task_can_be_reset_and_reused() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_state(0, TASK_FAILED);
    s.set_task_state(0, READY);
    
    s.set_number_failures(0, 0);
    
    s.run();
    
    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}

void test_failure_procedure_is_isolated() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, mockFailure, 1000, 1, 500);
    
    failure_called = false;
    
    s.set_number_failures(0, 5);
    
    s.retry_task(0);

    TEST_ASSERT_TRUE(failure_called);
    TEST_ASSERT_TRUE(s.is_task_valid(0));
}

void run_edge_case_tests() {
    RUN_TEST(test_delay_prevents_early_run);
    RUN_TEST(test_double_unlock_restores_priority_once);
    RUN_TEST(test_task_reset_after_failure);
    RUN_TEST(test_task_starvation_prevention_basic);
    RUN_TEST(test_blocked_task_does_not_run_even_if_high_priority);
    RUN_TEST(test_priority_restoration_on_unlock_only_once);
    RUN_TEST(test_run_does_nothing_when_no_tasks_ready);
    RUN_TEST(test_task_can_be_reset_and_reused);
    RUN_TEST(test_failure_procedure_is_isolated);
}
