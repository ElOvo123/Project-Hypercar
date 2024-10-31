#include <Arduino.h>
#include <Scheduler.h>

// Create a Scheduler object
scheduler scheduler_main;

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
  scheduler_main.add_task(task_1, 1000, 1); // Task 1, 1-second interval, priority 1
  scheduler_main.add_task(task_2, 2000, 2); // Task 2, 2-second interval, priority 2
  scheduler_main.add_task(task_3, 3000, 3); // Task 3, 3-second interval, priority 3
}

void loop() {
  // Run the scheduler to execute tasks as needed
  scheduler_main.run();
}