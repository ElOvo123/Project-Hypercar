#include "test_common.hpp"

void test_add_task() {
    scheduler s(3);

    TEST_ASSERT_TRUE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
    
    TEST_ASSERT_EQUAL(1, s.get_current_number_of_tasks());
}

void test_task_parameters() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_running_period(0, 2000);
    s.set_priority(0, 2);
    s.set_max_execution_time(0, 300);

    TEST_ASSERT_EQUAL(2000, s.get_task_running_period(0));
    TEST_ASSERT_EQUAL(2, s.get_task_priority(0));
    TEST_ASSERT_EQUAL(300, s.get_max_execution_time(0));
}

void test_task_parameters_update_correctly() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    
    s.set_task_function(0, dummyTaskFunction);
    
    s.set_priority(0, 7);

    TEST_ASSERT_EQUAL(7, s.get_task_priority(0));
}

void test_invalid_task_access_is_safe() {
    scheduler s(3);

    TEST_ASSERT_FALSE(s.is_task_valid(-1));
    TEST_ASSERT_FALSE(s.is_task_valid(100));

    TEST_ASSERT_EQUAL(0, s.get_task_priority(999));
}

void test_max_task_limit() {
    scheduler s(3);
    
    int max = s.get_max_number_of_tasks();
    
    for (int i = 0; i < max; ++i) 
    {
        TEST_ASSERT_TRUE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
    }
    
    TEST_ASSERT_FALSE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
}

void test_mixed_ready_blocked_tasks() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    unsigned long now = s.get_current_time();
    s.set_delay_until_unblock(0, now + 99999);
    s.set_task_state(0, BLOCKED);

    s.set_task_state(1, READY);
    s.set_last_run_time(0, 0);
    s.set_last_run_time(1, 0);

    while (s.get_current_time() < 2000) {}

    s.run();

    unsigned long run_time_0 = s.get_task_last_run_time(0);
    unsigned long run_time_1 = s.get_task_last_run_time(1);

    TEST_ASSERT_EQUAL(0, run_time_0);
    TEST_ASSERT_NOT_EQUAL(0, run_time_1);
}

void test_run_with_no_tasks() {
    scheduler s(3);
    
    s.run();

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
}

void run_core_tests() {
    RUN_TEST(test_add_task);
    RUN_TEST(test_task_parameters);
    RUN_TEST(test_task_parameters_update_correctly);
    RUN_TEST(test_invalid_task_access_is_safe);
    RUN_TEST(test_max_task_limit);
    RUN_TEST(test_mixed_ready_blocked_tasks);
    RUN_TEST(test_run_with_no_tasks);
}
