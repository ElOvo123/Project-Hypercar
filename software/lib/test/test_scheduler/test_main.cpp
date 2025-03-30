#include "test_common.hpp"

bool failure_called = false;

void dummyTaskFunction(void) {

}

void dummyFailureProcedure(void) {
    printf("[dummyFailureProcedure] Called!\n");
    fflush(stdout);
}

void mockFailure(void) {
    failure_called = true;
}

int main() {
    UNITY_BEGIN();
    run_core_tests();
    run_timing_tests();
    run_priority_tests();
    run_failure_tests();
    run_edge_case_tests();
    run_stress_tests();
    run_utility_tests();
    return UNITY_END();
}
