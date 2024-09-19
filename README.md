# Kinetic Jewel Automation

This repository contains the code and instructions for the **Kinetic Jewelry** project, which creates controlled movements in a small aesthetic gold pendant using BLE (Bluetooth Low Energy). The pendant is equipped with a small coreless micro DC motor, controlled by an ESP32C3 microcontroller, and utilizes a DRV8833 motor driver. The entire system is controlled via a mobile app through BLE.

## Features

- BLE connectivity using ESP32C3 to control movements in the jewelry.
- Actuation of the coreless micro DC motor via the DRV8833 motor driver.
- Custom PCB design to fit within the pendant and optimize space.
- Various motor actions such as "Arch Up", "Arch Down", "Lotus Open", and more, triggered by specific BLE commands.
- Smooth motion control using PWM signals.

## Hardware

- **ESP32C3**: For BLE control and motor control.
- **Coreless Micro DC Motor**: For creating the movements in the pendant.
- **DRV8833 Motor Driver**: To drive the DC motor efficiently.
- **Custom PCB**: Designed to fit into the pendant and connect all components seamlessly.

## Software Requirements

- Arduino IDE with ESP32 core installed.
- BLE libraries for Arduino.

## Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/Abimacaw/Kinetic_Jewel.git

1. Open the `.ino` file in the Arduino IDE.

2. Install the required libraries:
   - `BLEDevice.h`
   - `BLEUtils.h`
   - `BLEServer.h`

3. Upload the code to your ESP32C3 microcontroller.

## BLE Commands

Once connected via BLE, the pendant accepts the following commands:

- **T**: Moves the "Arch" up.
- **B**: Moves the "Arch" down.
- **O**: Opens the "Lotus".
- **C**: Closes the "Lotus".
- **V**: Activates the vibration motor.

## Usage

- Pair your mobile app with the pendant via BLE.
- Send the appropriate BLE commands to control the various movements of the pendant.
