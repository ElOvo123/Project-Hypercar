#include "test_common.hpp"

void test_delay_and_unblock() {
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

void test_task_execution_timing() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.set_task_state(0, READY);

    s.run();

    unsigned long last = s.get_task_last_run_time(0);
    
    s.run();

    TEST_ASSERT_EQUAL(last, s.get_task_last_run_time(0));
}

void test_task_unblocks_exactly_on_time() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.delay_task(0, 200);

    while (s.get_current_time() < s.get_delay_until_unblock(0)) 
    {

    }
    
    s.run();

    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}

void test_task_runs_again_after_period() {
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

void test_get_current_time_increases() {
    scheduler s(3);

    unsigned long t1 = s.get_current_time();

    while (s.get_current_time() <= t1) 
    {

    }
    unsigned long t2 = s.get_current_time();

    TEST_ASSERT_TRUE(t2 > t1);
}

void run_timing_tests() {
    RUN_TEST(test_delay_and_unblock);
    RUN_TEST(test_task_execution_timing);
    RUN_TEST(test_task_unblocks_exactly_on_time);
    RUN_TEST(test_task_runs_again_after_period);
    RUN_TEST(test_get_current_time_increases);
}
