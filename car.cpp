#include "mbed.h"

// Define Pins for Hardware.
DigitalIn ultrasonic_sensor_trigger();
DigitalIn ultrasonic_sensor_echo();
DigitalOut motor_front_left();
DigitalOut motor_front_right();
DigitalOut motor_back_left();
DigitalOut motor_back_right();
Serial bluetooth();

// Constraints.
const int OBSTACLE_THRESHOLD = 10;

// Global Varaibles.
bool obstacle_detected = false;
string movement_command = "Stop";

// Function Prototypes.
void bluetooth_communication();
void detect_obstacle();
void movement_control();
void send_alert();
void power_management();

int main() {
    while (1) {

    }
}
