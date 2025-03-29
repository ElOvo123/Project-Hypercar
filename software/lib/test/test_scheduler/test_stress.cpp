#include "test_common.hpp"

void test_stress_rapid_execution() {
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

void test_stress_starvation_check() {
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

void test_stress_mass_block_unblock() {
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

void run_stress_tests(){
    RUN_TEST(test_stress_rapid_execution);
    RUN_TEST(test_stress_starvation_check);
    RUN_TEST(test_stress_mass_block_unblock);
}