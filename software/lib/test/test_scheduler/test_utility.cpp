#include "test_common.hpp"

void test_remove_invalid_task(void) {
    scheduler s(3);
    
    TEST_ASSERT_FALSE(s.remove_task(-1));
    TEST_ASSERT_FALSE(s.remove_task(999));
}

void test_reset_functionality(void) {
    scheduler s(3);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    s.set_task_state(0, RUNNING);
    s.reset();

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());
    TEST_ASSERT_FALSE(s.is_task_valid(0));
}

void run_utility_tests(void){
    RUN_TEST(test_remove_invalid_task);
    RUN_TEST(test_reset_functionality);
}