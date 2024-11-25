#include "mbed.h"

// Define Pins on Nucleo Board.
DigitalOut ultrasonic_sensor_trigger(D9);  
DigitalIn ultrasonic_sensor_echo(D10);     
Serial bluetooth(D8, D2);                 
DigitalOut driver1_in1(D3);               
DigitalOut driver1_in2(D4);               
DigitalOut driver1_in3(D5);                
DigitalOut driver1_in4(D6);               
DigitalOut driver2_in1(D7);                
DigitalOut driver2_in2(D11);               
DigitalOut driver2_in3(D12);               
DigitalOut driver2_in4(D13);    

// Constraints.
const int OBSTACLE_THRESHOLD = 10;

// Global Varaibles.
bool obstacle_detected = false;
char movement_command = 'S';

// Function Prototypes.
void bluetooth_communication();
void detect_obstacle();
void movement_control();
void send_alert();
void power_management();

int main() {
    while (1) {
        bluetooth_communication();
        detect_obstacle();
        movement_control();
        send_alert();
        wait_us(100000);
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
        movement_command = 'S';
        driver1_in1 = 1;
        driver1_in2 = 1; 
        driver1_in3 = 1;
        driver1_in4 = 1;
        driver2_in1 = 1;
        driver2_in2 = 1; 
        driver2_in3 = 1;
        driver2_in4 = 1;
    } else {
        // Move Car Forwards.
        if (movement_command == 'F') {
            driver1_in1 = 1;
            driver1_in2 = 0;
            driver1_in3 = 0;
            driver1_in4 = 1;
            driver2_in1 = 0;
            driver2_in2 = 1;
            driver2_in3 = 0;
            driver2_in4 = 1;
        // Move Car Backwards.
        } else if (movement_command == 'B') {
            driver1_in1 = 0;
            driver1_in2 = 1;
            driver1_in3 = 1;
            driver1_in4 = 0;
            driver2_in1 = 1;
            driver2_in2 = 0;
            driver2_in3 = 1;
            driver2_in4 = 0;
        // Move Car Left.
        } else if (movement_command == 'R') {
            driver1_in1 = 1;
            driver1_in2 = 0;
            driver1_in3 = 0;
            driver1_in4 = 1;
            driver2_in1 = 1;
            driver2_in2 = 0;
            driver2_in3 = 1;
            driver2_in4 = 0;
        // Move Car Right.
        } else if (movement_command == 'L') {
            driver1_in1 = 0;
            driver1_in2 = 1;
            driver1_in3 = 1;
            driver1_in4 = 0;
            driver2_in1 = 0;
            driver2_in2 = 1;
            driver2_in3 = 0;
            driver2_in4 = 1;
        // Stop Car.
        } else if (movement_command == 'S') {
            driver1_in1 = 1;
            driver1_in2 = 1;
            driver1_in3 = 1;
            driver1_in4 = 1;
            driver2_in1 = 1;
            driver2_in2 = 1; 
            driver2_in3 = 1;
            driver2_in4 = 1;
        }
    }
}

void send_alert() {
    // Send Alert Message for Movement Command.

    // Send Alert Message for Obstacle Detected.
}
