# Obstacle Avoiding Car - README

## Introduction
This project implements an **Obstacle Avoiding Car** using the **ST32-F401RE** microcontroller and **Ultrasonic Sensor (HC-SR04)** for obstacle detection. The car can be remotely controlled using a **Bluetooth module (DX-BT24-A)** to move forward, backward, left, or right. If an obstacle is detected within a predefined distance, the car will stop to avoid a collision.

### Key Features:
- Remote control via Bluetooth using a mobile phone.
- Obstacle detection using an ultrasonic sensor.
- Movement control with forward, backward, left, and right commands.
- Automatic stop if an obstacle is detected in the path.

## Hardware Requirements
- **ST32-F401RE Nucleo Board** (or any STM32 board with compatible pins).
- **Ultrasonic Sensor** (HC-SR04) for obstacle detection.
- **Bluetooth Module** (DX-BT24-A or similar) for wireless communication (UART).
- **Motor Driver** (e.g., L298N or any suitable driver for controlling the motors).
- **DC Motors** for movement of the car.
- Jumper wires and a power source (battery or external power supply).
- Buck Converter to convert from 12V to 5V for MCU and other components.

## Pin Connections
| **Component**            | **Pin on ST32-F401RE** |
|--------------------------|------------------------|
| Ultrasonic Sensor Trigger | D9                     |
| Ultrasonic Sensor Echo    | D10                    |
| Bluetooth TX              | D8                     |
| Bluetooth RX              | D2                     |
| Motor Driver 1 IN1        | D3                     |
| Motor Driver 1 IN2        | D4                     |
| Motor Driver 1 IN3        | D5                     |
| Motor Driver 1 IN4        | D6                     |
| Motor Driver 2 IN1        | D7                     |
| Motor Driver 2 IN2        | D11                    |
| Motor Driver 2 IN3        | D12                    |
| Motor Driver 2 IN4        | D13                    |

## Software Requirements
- **mbed OS**: The code is written using the mbed OS environment and uses mbed libraries for GPIO, serial communication, and timers.
- **IDE**: You can use the **Mbed Studio** or the **Online Compiler** to compile and upload the code to the STM32-F401RE.

## Project Overview
This project is designed to allow the car to:
1. Receive movement commands (`F`, `B`, `L`, `R`, `S`) via Bluetooth.
2. Detect obstacles in its path using an ultrasonic sensor.
3. Stop the car if an obstacle is detected to prevent a collision.

### Bluetooth Communication:
The car can be controlled using a Bluetooth terminal app on your mobile phone. The available movement commands are:
- **'F'**: Move forward.
- **'B'**: Move backward.
- **'L'**: Turn left.
- **'R'**: Turn right.
- **'S'**: Stop.

### Obstacle Detection:
- The ultrasonic sensor is used to measure the distance to the nearest object in front of the car.
- If the object is within a defined threshold (40 cm), the car will stop moving and print an alert via Bluetooth.
- Note momentum and delays are a factor so it won't stop at 40 cm.
  
### Motor Control:
The motor driver controls the DC motors based on the received Bluetooth commands:
- **Forward (F)**: Both motors rotate forward.
- **Backward (B)**: Both motors rotate backward.
- **Left (L)**: Left motor rotates in reverse while the right motor moves forward.
- **Right (R)**: Right motor rotates in reverse while the left motor moves forward.
- **Stop (S)**: Both motors stop.

## How It Works
1. **Bluetooth Communication**: The car waits for Bluetooth commands to control the movement. The Bluetooth module (HC-05) receives data from a mobile app and sends it to the STM32 board.
2. **Obstacle Detection**: The ultrasonic sensor sends a pulse, and the board measures the time it takes for the echo to return. The distance is calculated and compared to a threshold (40 cm).
3. **Movement Control**: Based on the received command, the car moves accordingly. If an obstacle is detected, the movement is halted, and an alert is sent via Bluetooth.

## Code Flow
1. **bluetooth_communication()**: This function reads Bluetooth commands to control the movement (`F`, `B`, `L`, `R`, `S`).
2. **detect_obstacle()**: This function measures the distance to any obstacle in the path. If the distance is less than 40 cm, the `obstacle_detected` flag is set to true.
3. **movement_control()**: This function controls the motors based on the received command, stopping the car if an obstacle is detected.
4. **send_alert()**: Sends a message to the Bluetooth terminal to inform the user of the car's current state (e.g., moving forward, moving backward, obstacle detected).

## How to Use
1. **Set Up Hardware**:
   - Connect the ultrasonic sensor, Bluetooth module, and motor driver as described in the **Pin Connections** section.
   - Ensure your car’s motors are connected to the motor driver correctly.
   - Power the system using a battery or power supply suitable for the STM32 and motors.
   - Image of setup at the end.

2. **Upload the Code**:
   - Open the code in the **Mbed Studio** or **Mbed Online Compiler**.
   - Select the STM32F401RE board as the target.
   - Compile and upload the code to the STM32 board.

3. **Control the Car**:
   - Pair your mobile phone with the Bluetooth module (HC-05).
   - Open a Bluetooth terminal app and send one of the following commands:
     - `F` to move forward.
     - `B` to move backward.
     - `L` to turn left.
     - `R` to turn right.
     - `S` to stop the car.
   - The car will move accordingly. If an obstacle is detected, it will stop and send an alert message via Bluetooth.

## Troubleshooting
- **Car not responding**: Ensure that the Bluetooth module is correctly paired with your mobile phone and that the mobile app is sending the correct commands.
- **Obstacle detection issues**: Check the wiring of the ultrasonic sensor, ensuring that the trigger and echo pins are correctly connected. Also, ensure that there is nothing blocking the sensor’s line of sight.
- **Motor not working**: Verify the motor driver connections, the motor power supply, and the motor driver logic.

## Conclusion
This obstacle avoiding car project demonstrates the integration of a variety of components including Bluetooth communication, ultrasonic sensors, and motor drivers to create an autonomous vehicle capable of avoiding obstacles.
