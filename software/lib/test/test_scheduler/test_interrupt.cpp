#include "test_common.hpp"

void test_run_interrupt_safe_executes_ready_task(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1, 3, 10);
    
    s.set_task_state(0, READY);

    bool ran = s.run_interrupt_safe();
    
    TEST_ASSERT_TRUE(ran);
}

void run_interrupt_tests(void){
    RUN_TEST(test_run_interrupt_safe_executes_ready_task);
}