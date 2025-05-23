#include "test_common.hpp"

#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <mutex>
#include <scheduler.h>

std::mutex log_mutex;

void seed_random(void) {
    static bool seeded = false;
    
    if (!seeded) 
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

void add_random_tasks(scheduler& s, int count) {
    seed_random();

    for (int i = 0; i < count; ++i) 
    {
        unsigned long period = 100 + (std::rand() % 1000);
        int priority = 1 + (std::rand() % 10);
        unsigned long max_time = 100 + (std::rand() % 500);

        s.add_task(dummyTaskFunction, dummyFailureProcedure, period, priority, max_time);
    }
}

void add_mixed_state_tasks(scheduler& s, int count) {
    seed_random();

    for (int i = 0; i < count; ++i) 
    {
        unsigned long period = 100 + (std::rand() % 1000);
        int priority = 1 + (std::rand() % 10);
        unsigned long max_time = 100 + (std::rand() % 500);

        s.add_task(dummyTaskFunction, dummyFailureProcedure, period, priority, max_time);

        if (i % 2 == 0) 
        {
            s.set_task_state(i, READY);
        } else {
            s.set_task_state(i, BLOCKED);
            s.set_delay_until_unblock(i, s.get_current_time() + (std::rand() % 1000));
        }
    }
}

unsigned long get_timestamp_ms() {
    
    auto now = std::chrono::steady_clock::now();
    
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    return static_cast<unsigned long>(ms);
}

void log_to_csv(int task_id, int priority, const char* event) {
    std::ofstream file("logs/scheduler_log.csv", std::ios::app);

    if (file.is_open()) 
    {
        file << get_timestamp_ms() << "," << task_id << "," << priority << "," << event << "\n";
        file.close();
    }
}


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