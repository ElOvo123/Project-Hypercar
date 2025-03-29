#include "test_common.hpp"

bool failure_called = false;

void dummyTaskFunction() {

}

void dummyFailureProcedure() {
    printf("[dummyFailureProcedure] Called!\n");
    fflush(stdout);
}

void mockFailure() {
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
    return UNITY_END();
}
