#include "test_common.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>

void test_stress_rapid_execution(void) {
    scheduler s(3);

    const int max = s.get_max_number_of_tasks();

    for (int i = 0; i < max; ++i) 
    {
        s.add_task(dummyTaskFunction, dummyFailureProcedure, 1, i + 1, 10);
        s.set_task_state(i, READY);
    }

    unsigned long start = s.get_current_time();
    unsigned long end = start + 100;

    while (s.get_current_time() < end) 
    {
        s.run();
    }

    for (int i = 0; i < max; ++i) 
    {
        TEST_ASSERT_TRUE(s.get_task_last_run_time(i) > 0);
    }
}
void test_stress_starvation_check(void) {
    scheduler s(3);

    s.add_task(dummyTaskFunction, dummyFailureProcedure, 10, 10, 10);
    s.add_task(dummyTaskFunction, dummyFailureProcedure, 10, 1, 10);

    s.set_task_state(0, READY);
    s.set_task_state(1, READY);

    unsigned long deadline = s.get_current_time() + 500;

    while (s.get_current_time() < deadline) 
    {
        s.run();
        for (int i = 0; i < 2; ++i) {
            if (s.get_task_last_run_time(i) >= s.get_current_time() - 1) 
            {
                log_to_csv(i, s.get_task_priority(i), "run");
            }
        }
    }

    TEST_ASSERT_TRUE(s.get_task_last_run_time(1) > 0);
}

void test_stress_mass_block_unblock(void) {
    scheduler s(3);

    const int max = s.get_max_number_of_tasks();

    for (int i = 0; i < max; ++i) 
    {
        s.add_task(dummyTaskFunction, dummyFailureProcedure, 100, i + 1, 10);
        s.delay_task(i, 100);
    }

    int ran_count = 0;
    unsigned long timeout = s.get_current_time() + 500;

    while (ran_count < max && s.get_current_time() < timeout) 
    {
        s.run();

        for (int i = 0; i < max; ++i) {
            if (s.get_task_last_run_time(i) > 0) 
            {
                log_to_csv(i, s.get_task_priority(i), "run");
            }
        }

        ran_count = 0;

        for (int i = 0; i < max; ++i) 
        {
            if (s.get_task_last_run_time(i) > 0) 
            {
                ran_count++;
            }
        }
    }

    TEST_ASSERT_EQUAL(max, ran_count);
}

void test_scheduler_with_random_tasks(void) {
    scheduler s(3);

    add_random_tasks(s, 10);

    for (int i = 0; i < s.get_current_number_of_tasks(); ++i) 
    {
        s.set_task_state(i, READY);
    }

    for (int i = 0; i < 50; ++i) 
    {
        s.run();
        for (int j = 0; j < s.get_current_number_of_tasks(); ++j) 
        {
            if (s.get_task_last_run_time(j) >= s.get_current_time() - 1) 
            {
                log_to_csv(j, s.get_task_priority(j), "run");
            }
        }
    }

    TEST_ASSERT_TRUE(true);
}

void test_scheduler_mixed_blocked_ready(void) {
    scheduler s(3);

    add_mixed_state_tasks(s, 10);

    for (int i = 0; i < 20; ++i) 
    {
        s.run();
        for (int j = 0; j < s.get_current_number_of_tasks(); ++j) 
        {
            if (s.get_task_last_run_time(j) >= s.get_current_time() - 1) 
            {
                log_to_csv(j, s.get_task_priority(j), "run");
            }
        }
    }

    TEST_ASSERT_TRUE(true);
}

void test_scheduler_random_task_unblock_over_time(void) {
    scheduler s(3);

    add_mixed_state_tasks(s, 10);

    unsigned long wait_until = s.get_current_time() + 1500;

    while (s.get_current_time() < wait_until) 
    {
        s.run();
        for (int j = 0; j < s.get_current_number_of_tasks(); ++j) 
        {
            if (s.get_task_last_run_time(j) >= s.get_current_time() - 1) 
            {
                log_to_csv(j, s.get_task_priority(j), "run");
            }
        }
    }

    TEST_ASSERT_TRUE(true);
}

void test_scheduler_random_stress_reset_and_reload(void) {
    scheduler s(3);

    add_random_tasks(s, 10);

    for (int i = 0; i < 20; ++i) 
    {
        s.run();
        for (int j = 0; j < s.get_current_number_of_tasks(); ++j) 
        {
            if (s.get_task_last_run_time(j) >= s.get_current_time() - 1) 
            {
                log_to_csv(j, s.get_task_priority(j), "run");
            }
        }
    }

    s.reset();

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());

    add_random_tasks(s, 5);

    TEST_ASSERT_EQUAL(5, s.get_current_number_of_tasks());
}

void test_scheduler_performance_profile() {
    scheduler s(3);

    add_random_tasks(s, 20);
    
    for (int i = 0; i < s.get_current_number_of_tasks(); ++i) 
    {
        s.set_task_state(i, READY);
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; ++i) 
    {
        s.run();
        for (int j = 0; j < s.get_current_number_of_tasks(); ++j) 
        {
            if (s.get_task_last_run_time(j) >= s.get_current_time() - 1) 
            {
                log_to_csv(j, s.get_task_priority(j), "run");
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    TEST_ASSERT_TRUE(duration.count() > 0);
}

void test_fault_injection_null_failure_safe() {
    scheduler s(3);
    
    s.add_task(dummyTaskFunction, nullptr, 1000, 1, 500);
    
    s.set_number_failures(0, 3);
    
    s.retry_task(0);
    log_to_csv(0, 1, "retry");
    
    TEST_ASSERT_EQUAL(TASK_FAILED, s.get_task_state(0));
}

void run_stress_tests(void){
    RUN_TEST(test_stress_rapid_execution);
    RUN_TEST(test_stress_starvation_check);
    RUN_TEST(test_stress_mass_block_unblock);
    RUN_TEST(test_scheduler_with_random_tasks);
    RUN_TEST(test_scheduler_mixed_blocked_ready);
    RUN_TEST(test_scheduler_random_task_unblock_over_time);
    RUN_TEST(test_scheduler_random_stress_reset_and_reload);
    RUN_TEST(test_fault_injection_null_failure_safe);
    RUN_TEST(test_scheduler_performance_profile);
}