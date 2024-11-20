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

void movement_control() {
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
        if (movement_command == "F") {
            
        } else if (movement_command == "") 
    }
}
