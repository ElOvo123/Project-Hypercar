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

void test_reset_clears_all_state(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 2, 500);
    
    s.set_task_state(0, RUNNING);
    
    s.reset();

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
    TEST_ASSERT_FALSE(s.is_task_valid(0));
}

void test_run_interrupt_safe_multiple_calls(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1, 2, 10);
    
    s.set_task_state(0, READY);

    for (int i = 0; i < 10; ++i) {
        s.set_task_state(0, READY);
        
        while (s.get_current_time() < s.get_task_last_run_time(0) + 2) 
        {

        }

        TEST_ASSERT_TRUE(s.run_interrupt_safe());
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

    s.preempt_running_task(1);

    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(1));

    s.preempt_running_task(2);

    TEST_ASSERT_EQUAL(RUNNING, s.get_task_state(2));
}

void run_preempt_tests(void){
    RUN_TEST(test_preempt_running_task);
    RUN_TEST(test_reset_clears_all_state);
    RUN_TEST(test_run_interrupt_safe_multiple_calls);
    RUN_TEST(test_chain_preemptions);
}