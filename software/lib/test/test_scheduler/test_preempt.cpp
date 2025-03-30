#include "test_common.hpp"

void test_preempt_running_task(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 5, 500);

    s.set_task_state(0, RUNNING);
    s.set_task_state(1, READY);

    s.preempt_running_task(1);

    TEST_ASSERT_EQUAL(READY, s.get_task_state(0));
    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(1));
}

void run_preempt_tests(void){
    RUN_TEST(test_preempt_running_task);
}