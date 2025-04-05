#include <scheduler.h>

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#include <chrono>
#include <thread>

// Forward declarations
void setup();
void loop();

// Mock Serial object for native builds
class DummySerial {
public:
    static void begin(int) {}

    static void println(const char* msg) {
        printf("%s\n", msg);
    }

    static void println(int value) {
        printf("%d\n", value);
    }

    static void println(double value) {
        printf("%f\n", value);
    }
};

static DummySerial Serial;
#endif

// Create Scheduler
static scheduler scheduler_main(2);

// Failure procedure
static void task_failure_procedure() {
    // For cppcheck: safely defined
}

// Task functions
static void task_1() {
    Serial.println("Task 1 is running");
}

static void task_2() {
    Serial.println("Task 2 is running");
}

static void task_3() {
    Serial.println("Task 3 is running");
}

void setup() {
    Serial.begin(9600);

    scheduler_main.add_task(task_1, task_failure_procedure, 1000, 1, 500);
    scheduler_main.add_task(task_2, task_failure_procedure, 2000, 2, 500);
    scheduler_main.add_task(task_3, task_failure_procedure, 3000, 3, 500);
}

void loop() {
    scheduler_main.run();
}

#ifndef ARDUINO
int main() {
    setup();
    while (true) {
        loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Simulate 100Hz loop
    }
}
#endif
