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
const int OBSTACLE_THRESHOLD = 40;

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
    // Initialize Baud Rate.
    bluetooth.baud(9600);
    // Wait for Motors to be Initialized.
    wait_us(100000);
    // Run indefinately.
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
    // Ensure the trigger pin is initialized (set to output).
    ultrasonic_sensor_trigger = 0;  // Set trigger to low initially.

    // Send pulse to ultrasonic sensor to trigger measurement.
    ultrasonic_sensor_trigger = 1;  // Send a 10us pulse to trigger the sensor.
    wait_us(10);  // Pulse duration should be 10 microseconds.
    ultrasonic_sensor_trigger = 0;  // Set trigger low again.

    // Wait for the echo pin to go high.
    Timer timer;
    timer.start();  // Start the timer to measure the echo duration.

    // 100ms timeout to prevent infinite loop if no echo.
    while (!ultrasonic_sensor_echo) {
        if (timer.read_us() > 100000) {
            // No response = no obstacle detected within timeout period.
            obstacle_detected = false;  
            printf("No echo detected (timeout).\n");
            return;
        }
    }

    // Measure the duration of the echo pulse.
    timer.reset();  // Reset the timer to start measuring the pulse duration.

    while (ultrasonic_sensor_echo) {
        // Check if the echo pulse exceeds 380ms (maximum range).
        if (timer.read_us() > 380000) {
            obstacle_detected = false;
            printf("Echo pulse too long (out of range).\n");
            return;
        }
    }

    // Calculate the pulse duration (time it took for the echo to return).
    float pulse_duration = timer.read_us();  // Duration in microseconds.
    float distance = pulse_duration * 0.034 / 2;  // Distance in centimeters.

    // Print distance for debugging.
    printf("\033[2J\033[H");  // Clear screen and reset cursor position.
    printf("Distance: %f cm\n", distance);

    // Set obstacle detection flag based on distance threshold.
    obstacle_detected = (distance < OBSTACLE_THRESHOLD);
    
    if (obstacle_detected) {
        printf("Obstacle detected!\n");
    } else {
        printf("No obstacle detected.\n");
    }
}


void movement_control() {
    // Stop the car if object detected.
    if (obstacle_detected && movement_command != 'B') {
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
            driver1_in3 = 1;
            driver1_in4 = 0;
            driver2_in1 = 0;
            driver2_in2 = 1;
            driver2_in3 = 0;
            driver2_in4 = 1;
        // Move Car Backwards.
        } else if (movement_command == 'B') {
            driver1_in1 = 0;
            driver1_in2 = 1;
            driver1_in3 = 0;
            driver1_in4 = 1;
            driver2_in1 = 1;
            driver2_in2 = 0;
            driver2_in3 = 1;
            driver2_in4 = 0;
        // Move Car Left.
        } else if (movement_command == 'R') {
            driver1_in1 = 1;
            driver1_in2 = 0;
            driver1_in3 = 1;
            driver1_in4 = 0;
            driver2_in1 = 1;
            driver2_in2 = 0;
            driver2_in3 = 1;
            driver2_in4 = 0;
        // Move Car Right.
        } else if (movement_command == 'L') {
            driver1_in1 = 0;
            driver1_in2 = 1;
            driver1_in3 = 0;
            driver1_in4 = 1;
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
    switch(movement_command) {
        case 'F':
            bluetooth.printf("Moving Forwards.\n");
            break;
        case 'B':
            bluetooth.printf("Moving Backwards.\n");
            break;
        case 'L':
            bluetooth.printf("Moving Left.\n");
            break;  
        case 'R':
            bluetooth.printf("Moving Right.\n");
            break;
        case 'S':
            bluetooth.printf("Not Moving.\n");
            break;
        default:
            bluetooth.printf("Invalid Input, Try Again.\n");
    }
    // Send Alert Message for Obstacle Detected.
    if (obstacle_detected) {
        bluetooth.printf("Alert: Obstacle detected! Movement halted.\n");
    }
}
