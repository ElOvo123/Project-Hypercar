#include <stdio.h>
#include <unity.h>
#include <scheduler.h>

void dummyFailureProcedure() {
    printf("[dummyFailureProcedure] Called!\n");
    fflush(stdout);
}

void dummyTaskFunction() {}

bool failure_called = false;

void mockFailure() {
    failure_called = true;
}

void test_add_task() {
    scheduler s(3);

    bool result = s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(1, s.get_current_number_of_tasks());
}

void test_task_parameters() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    int task_id = 0;
    s.set_running_period(task_id, 2000);
    s.set_priority(task_id, 2);
    s.set_max_execution_time(task_id, 300);

    TEST_ASSERT_EQUAL(2000, s.get_task_running_period(task_id));
    TEST_ASSERT_EQUAL(2, s.get_task_priority(task_id));
    TEST_ASSERT_EQUAL(300, s.get_max_execution_time(task_id));
}

void test_task_retry() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    s.set_number_failures(0, 3);
    s.retry_task(0);

    TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
}

void test_locking_unlocking() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);

    s.set_task_is_running(0, true);
    s.lock_resource(0);

    TEST_ASSERT_EQUAL(3, s.get_task_priority(0));

    s.unlock_resource(0);

    TEST_ASSERT_EQUAL(1, s.get_task_priority(0));
}

void test_delay_and_unblock() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    int task_id = 0;
    s.delay_task(task_id, 5000);

    TEST_ASSERT_EQUAL(BLOCKED, s.get_task_state(task_id));

    unsigned long unblock_time = s.get_delay_until_unblock(task_id);
    while (s.get_current_time() < unblock_time) {}

    s.run();

    TEST_ASSERT_EQUAL(READY, s.get_task_state(task_id));
}

void test_task_execution_timing() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    int task_id = 0;
    s.run();

    unsigned long last_run = s.get_task_last_run_time(task_id);

    s.run();
    TEST_ASSERT_EQUAL(last_run, s.get_task_last_run_time(task_id));
}

void test_max_task_limit() {
    scheduler s(3);
    int max = s.get_max_number_of_tasks();

    for (int i = 0; i < max; ++i) {
        TEST_ASSERT_TRUE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
    }

    TEST_ASSERT_FALSE(s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500));
}

void test_run_skips_blocked_task() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    int task_id = 0;
    unsigned long now = s.get_current_time();
    s.set_delay_until_unblock(task_id, now + 5000);
    s.set_task_state(task_id, BLOCKED);

    s.run();

    TEST_ASSERT_EQUAL(BLOCKED, s.get_task_state(task_id));
}


void test_run_selects_highest_priority_ready() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);
    s.set_last_run_time(0, 0);
    s.set_last_run_time(1, 0);

    while (s.get_current_time() < 5000) {}

    s.run();

    unsigned long task1_last_run = s.get_task_last_run_time(1);
    unsigned long task0_last_run = s.get_task_last_run_time(0);

    TEST_ASSERT_TRUE(task1_last_run > 0);
    TEST_ASSERT_TRUE(task0_last_run == 0);
}

void test_invalid_task_access_is_safe() {
    scheduler s(3);

    TEST_ASSERT_FALSE(s.is_task_valid(-1));
    TEST_ASSERT_FALSE(s.is_task_valid(100));
    TEST_ASSERT_EQUAL(0, s.get_task_priority(999));
}

void test_task_unblocks_exactly_on_time() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    s.delay_task(0, 200);

    unsigned long unblock_time = s.get_delay_until_unblock(0);
    while (s.get_current_time() < unblock_time) {}

    s.run();
    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
}


void test_task_parameters_update_correctly() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    s.set_task_function(0, dummyTaskFunction);
    s.set_priority(0, 7);
    TEST_ASSERT_EQUAL(7, s.get_task_priority(0));
}

void test_retry_until_limit_then_fail() {
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


void test_multiple_ready_tasks_same_priority() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);

    while (s.get_current_time() < 1000) {}

    s.run();

    unsigned long t0 = s.get_task_last_run_time(0);
    unsigned long t1 = s.get_task_last_run_time(1);

    TEST_ASSERT_TRUE((t0 > 0 && t1 == 0) || (t1 > 0 && t0 == 0));
}

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

void test_invalid_task_rejection() {
    scheduler s(3);
    s.set_task_state(-1, RUNNING);
    s.set_task_function(999, dummyTaskFunction);
    s.set_priority(999, 10);

    TEST_ASSERT_FALSE(s.is_task_valid(-1));
    TEST_ASSERT_FALSE(s.is_task_valid(999));
}

void test_run_respects_running_period() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);

    s.set_task_state(0, READY);
    s.run();

    unsigned long t0 = s.get_task_last_run_time(0);

    s.run();

    TEST_ASSERT_EQUAL(t0, s.get_task_last_run_time(0));
}

void test_all_tasks_ready_highest_priority_runs() {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 4, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);

    for (int i = 0; i < 3; i++) {
        s.set_task_state(i, READY);
    }

    while (s.get_current_time() < 2000) {}

    s.run();
    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(0));
    TEST_ASSERT_EQUAL(0, s.get_task_last_run_time(2));
    TEST_ASSERT_NOT_EQUAL(0, s.get_task_last_run_time(1));
}

void test_escalate_failure_only_called_on_failure() {
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
    s.set_last_run_time(0, 0);
    s.set_last_run_time(1, 0);

    while (s.get_current_time() < 10000) {}

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

void test_task_runs_again_after_period() {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 500, 2, 500);
    s.set_task_state(0, READY);
    s.run();

    unsigned long first = s.get_task_last_run_time(0);
    while (s.get_current_time() < first + 500) {}

    s.run();
    TEST_ASSERT_TRUE(s.get_task_last_run_time(0) > first);
}

void test_get_current_time_increases() {
    scheduler s(3);
    unsigned long t1 = s.get_current_time();
    while (s.get_current_time() <= t1) {}
    unsigned long t2 = s.get_current_time();
    TEST_ASSERT_TRUE(t2 > t1);
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

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_add_task);
    RUN_TEST(test_task_parameters);
    RUN_TEST(test_task_retry);
    RUN_TEST(test_locking_unlocking);
    RUN_TEST(test_delay_and_unblock);
    RUN_TEST(test_task_execution_timing);
    RUN_TEST(test_max_task_limit);
    RUN_TEST(test_run_skips_blocked_task);
    RUN_TEST(test_run_selects_highest_priority_ready);
    RUN_TEST(test_invalid_task_access_is_safe);
    RUN_TEST(test_task_unblocks_exactly_on_time);
    RUN_TEST(test_task_parameters_update_correctly);
    RUN_TEST(test_retry_until_limit_then_fail);
    RUN_TEST(test_multiple_ready_tasks_same_priority);
    RUN_TEST(test_delay_prevents_early_run);
    RUN_TEST(test_double_unlock_restores_priority_once);
    RUN_TEST(test_invalid_task_rejection);
    RUN_TEST(test_run_respects_running_period);
    RUN_TEST(test_all_tasks_ready_highest_priority_runs);
    RUN_TEST(test_escalate_failure_only_called_on_failure);
    RUN_TEST(test_task_reset_after_failure);
    RUN_TEST(test_task_starvation_prevention_basic);
    RUN_TEST(test_blocked_task_does_not_run_even_if_high_priority);
    RUN_TEST(test_task_runs_again_after_period);
    RUN_TEST(test_get_current_time_increases);
    RUN_TEST(test_priority_restoration_on_unlock_only_once);
    RUN_TEST(test_run_does_nothing_when_no_tasks_ready);
    return UNITY_END();
}
