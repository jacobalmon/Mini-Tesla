#include "mbed.h"

// Define Pins for Hardware.
DigitalOut ultrasonic_sensor_trigger(D9);
DigitalIn ultrasonic_sensor_echo(D10);
Serial bluetooth(D12, D13);
PwmOut driver1_act1(D6);
PwmOut driver1_act2(D11);
DigitalOut driver1_in1(D2);
DigitalOut driver1_in2(D3);
DigitalOut driver1_in3(D4);
DigitalOut driver1_in4(D5);
PwmOut driver2_act1(D8);
PwmOut driver2_act2(D7);
DigitalOut driver2_in1(D12);
DigitalOut driver2_in2(D13);
DigitalOut driver2_in3(D9);
DigitalOut driver2_in4(A0);

// Constraints.
const int OBSTACLE_THRESHOLD = 10;

// Global Varaibles.
bool obstacle_detected = false;
string movement_command = "S";

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

void bluetooth_communication() {
    // Check if any data has been received over Bluetooth.

    // Get the Character from the Bluetooth.
}

void detect_obstacle() {
    // Send pulse to ultrasonic sensor to trigger measurement.

    // Measure echo pulse duration.

    // Calculate distance in cm.

    // Set Obstacle Detected Flag.
}

void movement_control() {
    // Stop the car if object detected.
    if (obstacle_detected) {
        movement_command == "S";
        driver1_in1 = 0;
        driver1_in2 = 0;
        driver1_in3 = 0;
        driver1_in4 = 0;
        driver2_in1 = 0;
        driver2_in2 = 0;
        driver2_in3 = 0;
        driver2_in4 = 0;
    } else {
        // Move Car Forwards.
        if (movement_command == "F") {
            
        // Move Car Backwards.
        } else if (movement_command == "B") {
            
        // Move Car Left.
        } else if (movement_command == "L") {
            
        // Move Car Right.
        } else if (movement_command == "R") {
            
        // Stop Car.
        } else if (movement_command == "S") {
            
        }
    }
}

void send_alert() {
    // Send Alert Message for Movement Command.

    // Send Alert Message for Obstacle Detected.
}
