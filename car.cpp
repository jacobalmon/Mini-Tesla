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
    if (bluetooth.readable()) {
        char received = bluetooth.getc(); // Read a single character from Bluetooth.
        // Update the movement command only if it's a valid command
        if (received == 'F' || received == 'B' || received == 'L' || 
            received == 'R' || received == 'S') {
            movement_command = received; // Update the movement command
        }
    }
}

void detect_obstacle() {
   // Send pulse to ultrasonic sensor to trigger measurement.
    ultrasonic_sensor_trigger = 1;
    wait_us(10);
    ultrasonic_sensor_trigger = 0;

    //Wait for echo to be sent out (HIGH)
    Timer timer;
    //100ms timeout prevents infinite loop.
    timer.start();
    while (!ultrasonic_sensor_echo) {
        if (timer.read_us() > 100000) {
            // Assumes no response = no obstacle
            obstacle_detected = false;  
            return;
        }
    }

    // Measure echo pulse duration.
    timer.reset();
    while (ultrasonic_sensor_echo) {
        //out of range 380ms max echo 
        //NOTE: Can be adjusted to change the max detection distance
        //380ms is jus what the documentation used
        if (timer.read_us() > 380000) {
            obstacle_detected = false;
            return;
        }
    }
    float pulse_duration = timer.read_us(); // Duration in microseconds

    // Calculate distance in cm.
    float distance = pulse_duration * 0.034 / 2;

    // Clear the screen and move the cursor to the home position
    printf("\033[2J\033[H");    
    printf("dist: %fcm\n", distance);

    // Set Obstacle Detected Flag. 
    obstacle_detected = (distance < OBSTACLE_THRESHOLD);

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
