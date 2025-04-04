#include "test_common.hpp"

int task_executed_id = -1;

void traceableTask0(void) { task_executed_id = 0; }
void traceableTask1(void) { task_executed_id = 1; }

void test_locking_unlocking(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    
    s.set_task_is_running(0, true);
    s.lock_resource(0);
    log_to_csv(0, s.get_task_priority(0), "lock_resource");

    TEST_ASSERT_EQUAL(3, s.get_task_priority(0));
    
    s.unlock_resource(0);
    log_to_csv(0, s.get_task_priority(0), "unlock_resource");

    TEST_ASSERT_EQUAL(1, s.get_task_priority(0));
}

void test_run_selects_highest_priority_ready(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);
    s.set_last_run_time(0, 0);
    s.set_last_run_time(1, 0);

    while (s.get_current_time() < 5000) 
    {

    }

    s.run();
    log_to_csv(1, s.get_task_priority(1), "run");

    unsigned long task1_last_run = s.get_task_last_run_time(1);
    unsigned long task0_last_run = s.get_task_last_run_time(0);

    TEST_ASSERT_TRUE(task1_last_run > 0);
    TEST_ASSERT_TRUE(task0_last_run == 0);
}

void test_multiple_ready_tasks_same_priority(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);

    while (s.get_current_time() < 1000) 
    {

    }

    s.run();

    unsigned long t0 = s.get_task_last_run_time(0);
    unsigned long t1 = s.get_task_last_run_time(1);

    if (t0 > 0) 
    {
        log_to_csv(0, 3, "run");
    }

    if (t1 > 0)
    {
        log_to_csv(1, 3, "run");
    }
            
    TEST_ASSERT_TRUE((t0 > 0 && t1 == 0) || (t1 > 0 && t0 == 0));
}

void test_all_tasks_ready_highest_priority_runs(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 4, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);

    for (int i = 0; i < 3; i++)
    {
        s.set_task_state(i, READY);
    }

    while (s.get_current_time() < 2000) 
    {

    }

    s.run();

    if (s.get_task_last_run_time(1) > 0)
    {
        log_to_csv(1, s.get_task_priority(1), "run");
    }

    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(0));
    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(2));
    TEST_ASSERT_NOT_EQUAL(0, s.get_task_last_run_time(1));
}

void test_only_one_task_runs_at_a_time(void) {
    scheduler s(3);

    task_executed_id = -1;

    s.add_task(traceableTask0, dummyFailureProcedure, 1000, 2, 500);
    s.add_task(traceableTask1, dummyFailureProcedure, 1000, 3, 500);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);

    while (s.get_current_time() < 1000) 
    {

    }

    s.run();

    if (task_executed_id >= 0)
    {
        log_to_csv(task_executed_id, s.get_task_priority(task_executed_id), "run");
    }
    
    TEST_ASSERT_TRUE(task_executed_id == 0 || task_executed_id == 1);
}

void test_priority_inheritance_only_when_running(void) {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_is_running(0, false);
    s.lock_resource(0);

    log_to_csv(0, s.get_task_priority(0), "lock_resource_no_effect");

    TEST_ASSERT_EQUAL(1, s.get_task_priority(0));
}

void run_priority_tests(void) {
    RUN_TEST(test_locking_unlocking);
    RUN_TEST(test_run_selects_highest_priority_ready);
    RUN_TEST(test_multiple_ready_tasks_same_priority);
    RUN_TEST(test_all_tasks_ready_highest_priority_runs);
    RUN_TEST(test_only_one_task_runs_at_a_time);
    RUN_TEST(test_priority_inheritance_only_when_running);
}
