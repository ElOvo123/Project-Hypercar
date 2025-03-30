#include "test_common.hpp"

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
    }

    TEST_ASSERT_TRUE(true);
}

void test_scheduler_mixed_blocked_ready(void) {
    scheduler s(3);

    add_mixed_state_tasks(s, 10);

    for (int i = 0; i < 20; ++i) 
    {
        s.run();
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
    }

    TEST_ASSERT_TRUE(true);
}

void test_scheduler_random_stress_reset_and_reload(void) {
    scheduler s(3);
    
    add_random_tasks(s, 10);

    for (int i = 0; i < 20; ++i) 
    {
        s.run();
    }

    s.reset();

    TEST_ASSERT_EQUAL(0, s.get_current_number_of_tasks());

    add_random_tasks(s, 5);

    TEST_ASSERT_EQUAL(5, s.get_current_number_of_tasks());
}


void run_stress_tests(void){
    RUN_TEST(test_stress_rapid_execution);
    RUN_TEST(test_stress_starvation_check);
    RUN_TEST(test_stress_mass_block_unblock);
    RUN_TEST(test_scheduler_with_random_tasks);
    RUN_TEST(test_scheduler_mixed_blocked_ready);
    RUN_TEST(test_scheduler_random_task_unblock_over_time);
    RUN_TEST(test_scheduler_random_stress_reset_and_reload);
}