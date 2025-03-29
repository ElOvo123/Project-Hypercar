#include <scheduler.h>

#include <scheduler.h>

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>

// Forward declarations for native
void setup();
void loop();

// Mock Serial object for native
class DummySerial {
public:
    void begin(int) {}

    void println(const char* msg) {
        printf("%s\n", msg);
    }

    void println(int value) {
        printf("%d\n", value);
    }

    void println(double value) {
        printf("%f\n", value);
    }
};

DummySerial Serial;
#endif

// Create a Scheduler object
scheduler scheduler_main(2);

void task_failure_procedure(){
  
}

// Define task functions
void task_1() {
  Serial.println("Task 1 is running");
}

void task_2() {
  Serial.println("Task 2 is running");
}

void task_3() {
  Serial.println("Task 3 is running");
}

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Add tasks to the scheduler
  scheduler_main.add_task(task_1, task_failure_procedure, 1000, 1, 500); // Task 1, 1-second interval, priority 1
  scheduler_main.add_task(task_2, task_failure_procedure, 2000, 2, 500); // Task 2, 2-second interval, priority 2
  scheduler_main.add_task(task_3, task_failure_procedure, 3000, 3, 500); // Task 3, 3-second interval, priority 3
}

void loop() {
  // Run the scheduler to execute tasks as needed
  scheduler_main.run();
}

#ifndef ARDUINO
#include <chrono>
#include <thread>

int main() {
    setup();
    while (true) {
        loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate a ~100Hz loop
    }
}
#endif
