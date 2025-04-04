#include "test_common.hpp"

void test_preempt_running_task(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, RUNNING);
    s.set_task_state(1, READY);
    log_to_csv(0, s.get_task_priority(0), "running");
    log_to_csv(1, s.get_task_priority(1), "ready");

    s.preempt_running_task(1);
    log_to_csv(0, s.get_task_priority(0), "preempted");
    log_to_csv(1, s.get_task_priority(1), "now_running");

    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(1));
}

void test_reset_clears_all_state(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);
    log_to_csv(0, 2, "added");

    s.set_task_state(0, RUNNING);
    log_to_csv(0, 2, "running");

    s.reset();
    log_to_csv(-1, -1, "reset");

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
    TEST_ASSERT_FALSE(s.is_task_valid(0));
}

void test_run_interrupt_safe_multiple_calls(void) {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1, 2, 10);

    s.set_task_state(0, READY);
    log_to_csv(0, s.get_task_priority(0), "ready");

    for (int i = 0; i < 10; ++i) 
    {
        s.set_task_state(0, READY);
        while (s.get_current_time() < s.get_task_last_run_time(0) + 2) {}

        bool result = s.run_interrupt_safe();
        log_to_csv(0, s.get_task_priority(0), result ? "run_interrupt_safe_success" : "run_interrupt_safe_fail");

        TEST_ASSERT_TRUE(result);
    }
}

void test_chain_preemptions(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 3, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, RUNNING);
    s.set_task_state(1, READY);
    s.set_task_state(2, READY);

    log_to_csv(0, s.get_task_priority(0), "running");
    log_to_csv(1, s.get_task_priority(1), "ready");
    log_to_csv(2, s.get_task_priority(2), "ready");

    s.preempt_running_task(1);
    log_to_csv(0, s.get_task_priority(0), "preempted_by_1");
    log_to_csv(1, s.get_task_priority(1), "now_running");

    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(1));

    s.preempt_running_task(2);
    log_to_csv(1, s.get_task_priority(1), "preempted_by_2");
    log_to_csv(2, s.get_task_priority(2), "now_running");

    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(2));
}

void run_preempt_tests(void) {
    RUN_TEST(test_preempt_running_task);
    RUN_TEST(test_reset_clears_all_state);
    RUN_TEST(test_run_interrupt_safe_multiple_calls);
    RUN_TEST(test_chain_preemptions);
}
