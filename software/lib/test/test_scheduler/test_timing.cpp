#include "test_common.hpp"

void test_delay_and_unblock(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.delay_task(0, 5000);

    TEST_ASSERT_EQUAL(BLOCKED, s.get_task_state(0));

    while (s.get_current_time() < s.get_delay_until_unblock(0)) 
    {

    }
    
    s.run();
    
    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}

void test_task_execution_timing(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.set_task_state(0, READY);

    s.run();

    unsigned long last = s.get_task_last_run_time(0);
    
    s.run();

    TEST_ASSERT_EQUAL(last, s.get_task_last_run_time(0));
}

void test_task_unblocks_exactly_on_time(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.delay_task(0, 200);

    while (s.get_current_time() < s.get_delay_until_unblock(0)) 
    {

    }
    
    s.run();

    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}

void test_task_runs_again_after_period(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 500, 2, 500);
    s.set_task_state(0, READY);

    s.run();
    
    unsigned long first = s.get_task_last_run_time(0);
    
    while (s.get_current_time() < first + 500) 
    {

    }
    
    s.run();
    
    TEST_ASSERT_TRUE(s.get_task_last_run_time(0) > first);
}

void test_get_current_time_increases(void) {
    scheduler s(3);

    unsigned long t1 = s.get_current_time();

    while (s.get_current_time() <= t1) 
    {

    }
    unsigned long t2 = s.get_current_time();

    TEST_ASSERT_TRUE(t2 > t1);
}

void test_task_period_not_elapsed_skips_execution(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_state(0, READY);
    
    s.run();

    unsigned long first_run = s.get_task_last_run_time(0);
    
    s.run();

    TEST_ASSERT_EQUAL(first_run, s.get_task_last_run_time(0));
}

void test_multiple_tasks_unblock_simultaneously(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);

    s.delay_task(0, 1000);
    s.delay_task(1, 1000);

    unsigned long unblock_time = s.get_delay_until_unblock(0);

    while (s.get_current_time() < unblock_time) 
    {

    }

    s.run();

    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
    TEST_ASSERT_EQUAL(READY, s.get_task_state(1));
}

void test_zero_running_period(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 0, 1, 500);
    
    s.set_task_state(0, READY);

    s.run();

    TEST_ASSERT_NOT_EQUAL(0, s.get_task_last_run_time(0));
}

void test_redundant_delay_call(void) {
    scheduler s(3);

    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.delay_task(0, 1000);
    
    unsigned long first_unblock = s.get_delay_until_unblock(0);

    s.delay_task(0, 2000);
    
    unsigned long updated_unblock = s.get_delay_until_unblock(0);

    TEST_ASSERT_TRUE(updated_unblock > first_unblock);
}

void run_timing_tests(void) {
    RUN_TEST(test_delay_and_unblock);
    RUN_TEST(test_task_execution_timing);
    RUN_TEST(test_task_unblocks_exactly_on_time);
    RUN_TEST(test_task_runs_again_after_period);
    RUN_TEST(test_get_current_time_increases);
    RUN_TEST(test_task_period_not_elapsed_skips_execution);
    RUN_TEST(test_multiple_tasks_unblock_simultaneously);
    RUN_TEST(test_zero_running_period);
    RUN_TEST(test_redundant_delay_call);
}
