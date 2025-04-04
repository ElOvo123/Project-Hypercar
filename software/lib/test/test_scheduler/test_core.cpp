#include "test_common.hpp"

void test_add_task(void) {
    scheduler s(3);

    TEST_ASSERT_TRUE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
    log_to_csv(0, 1, "add_task");

    TEST_ASSERT_EQUAL(1, s.get_current_number_of_tasks());
}

void test_task_parameters(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    log_to_csv(0, 1, "add_task");

    s.set_running_period(0, 2000);
    s.set_priority(0, 2);
    s.set_max_execution_time(0, 300);

    log_to_csv(0, 2, "update_params");

    TEST_ASSERT_EQUAL(2000, s.get_task_running_period(0));
    TEST_ASSERT_EQUAL(2, s.get_task_priority(0));
    TEST_ASSERT_EQUAL(300, s.get_max_execution_time(0));
}

void test_task_parameters_update_correctly(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    log_to_csv(0, 1, "add_task");

    s.set_task_function(0, dummyTaskFunction);
    s.set_priority(0, 7);
    log_to_csv(0, 7, "priority_update");

    TEST_ASSERT_EQUAL(7, s.get_task_priority(0));
}

void test_invalid_task_access_is_safe(void) {
    scheduler s(3);

    TEST_ASSERT_FALSE(s.is_task_valid(-1));
    TEST_ASSERT_FALSE(s.is_task_valid(100));
    TEST_ASSERT_EQUAL(0, s.get_task_priority(999));
}

void test_max_task_limit(void) {
    scheduler s(3);
    
    int max = s.get_max_number_of_tasks();
    
    for (int i = 0; i < max; ++i) 
    {
        TEST_ASSERT_TRUE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
        log_to_csv(i, 1, "add_task");
    }

    TEST_ASSERT_FALSE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
}

void test_mixed_ready_blocked_tasks(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    log_to_csv(0, 3, "add_blocked_task");
    log_to_csv(1, 1, "add_ready_task");

    unsigned long now = s.get_current_time();
    s.set_delay_until_unblock(0, now + 99999);
    s.set_task_state(0, BLOCKED);

    s.set_task_state(1, READY);
    s.set_last_run_time(0, 0);
    s.set_last_run_time(1, 0);

    while (s.get_current_time() < 2000) 
    {

    }

    s.run();
    log_to_csv(1, s.get_task_priority(1), "run");

    unsigned long run_time_0 = s.get_task_last_run_time(0);
    unsigned long run_time_1 = s.get_task_last_run_time(1);

    TEST_ASSERT_EQUAL(0, run_time_0);
    TEST_ASSERT_NOT_EQUAL(0, run_time_1);
}

void test_run_with_no_tasks(void) {
    scheduler s(3);

    s.run();
    
    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
}

void test_max_priority_task_runs_first(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, INT_MAX, 500);
    log_to_csv(0, 1, "add_low_priority");
    log_to_csv(1, INT_MAX, "add_high_priority");

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);

    while (s.get_current_time() < 1000) 
    {

    }

    s.run();
    log_to_csv(1, INT_MAX, "run");

    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(0));
    TEST_ASSERT_NOT_EQUAL(0, s.get_task_last_run_time(1));
}

void test_scheduler_reset_clears_tasks(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    log_to_csv(0, 1, "add_task");

    TEST_ASSERT_EQUAL(1, s.get_current_number_of_tasks());

    s.reset();
    log_to_csv(-1, -1, "reset");

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
}

void test_rescheduling_after_delay(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 500, 2, 500);
    log_to_csv(0, 2, "add_task");

    s.set_task_state(0, READY);
    s.delay_task(0, 200);
    log_to_csv(0, 2, "delay_200");

    unsigned long unblock_time = s.get_delay_until_unblock(0);
    while (s.get_current_time() < unblock_time) 
    {

    }

    s.run();
    log_to_csv(0, 2, "run");

    s.delay_task(0, 300);
    log_to_csv(0, 2, "delay_300");

    unblock_time = s.get_delay_until_unblock(0);
    while (s.get_current_time() < unblock_time) 
    {

    }

    s.run();
    log_to_csv(0, 2, "run");

    TEST_ASSERT_TRUE(s.get_task_last_run_time(0) > 0);
}

void run_core_tests(void) {
    RUN_TEST(test_add_task);
    RUN_TEST(test_task_parameters);
    RUN_TEST(test_task_parameters_update_correctly);
    RUN_TEST(test_invalid_task_access_is_safe);
    RUN_TEST(test_max_task_limit);
    RUN_TEST(test_mixed_ready_blocked_tasks);
    RUN_TEST(test_run_with_no_tasks);
    RUN_TEST(test_max_priority_task_runs_first);
    RUN_TEST(test_scheduler_reset_clears_tasks);
    RUN_TEST(test_rescheduling_after_delay);
}
