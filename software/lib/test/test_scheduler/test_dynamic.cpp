#include "test_common.hpp"

void test_promote_priority(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 1000, 1, 500);
    log_to_csv(0, 1, "initial_priority");

    s.promote_task_priority(0, 5);
    log_to_csv(0, 5, "promoted_priority");

    TEST_ASSERT_EQUAL(5, s.get_task_priority(0));
}

void run_dynamic_tests(void){
    RUN_TEST(test_promote_priority);
}
