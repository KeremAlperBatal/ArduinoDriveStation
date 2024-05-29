# ArduinoDriveStation Library

ArduinoDriveStation is a library for Arduino projects that enables communication over Bluetooth and provides functionality to control the behavior of the project based on the received data.

## Installation

1. Open Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries...** from the menu bar.
3. Search for "ArduinoDriveStation" in the Library Manager.
4. Click on the ArduinoDriveStation library, then click **Install** to complete the installation.
5. To use the library, add `#include <ArduinoDriveStation.h>` at the beginning of your Arduino sketch.

## Usage

### Initialization

1. Create an ArduinoDriveStation object by specifying the RX and TX pins connected to the Bluetooth module:
    ```cpp
    ArduinoDriveStation driveStation(rxPin, txPin);
    ```
2. Initialize the library in the `setup()` function:
    ```cpp
    void setup() {
      driveStation.begin();
    }
    ```

### Data Processing

1. In the `loop()` function, call the `update()` method to process incoming data over Bluetooth:
    ```cpp
    void loop() {
      driveStation.update();
      // Other operations...
    }
    ```

### Mode Configuration

1. Set the initialization and periodic methods for each mode:
    ```cpp
    // Set Teleop mode initialization method
    driveStation.setTeleopInitMethod(teleopInit);

    // Set Teleop mode periodic method
    driveStation.setTeleopPeriodicMethod(teleopPeriodic);

    // Set Autonom mode initialization method
    driveStation.setAutonomInitMethod(autonomInit);

    // Set Autonom mode periodic method
    driveStation.setAutonomPeriodicMethod(autonomPeriodic);

    // Set Disable mode initialization method
    driveStation.setDisableInitMethod(disableInit);

    // Set Disable mode periodic method
    driveStation.setDisablePeriodicMethod(disablePeriodic);
    ```

## Example Code

```cpp
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ArduinoDriveStation.h"

// RX and TX pins of the Bluetooth module
#define RX_PIN 0
#define TX_PIN 1

// Creating an instance of ArduinoDriveStation
ArduinoDriveStation driveStation(RX_PIN, TX_PIN);

// Teleop Init method
void teleopInit() {
  Serial.println("Teleop Init");
  // Teleop mode initialization settings
}

// Teleop Periodic method
void teleopPeriodic() {
  Serial.println("Teleop Periodic");
  // Teleop mode continuous operations
}

// Autonom Init method
void autonomInit() {
  Serial.println("Autonom Init");
  // Autonom mode initialization settings
}

// Autonom Periodic method
void autonomPeriodic() {
  Serial.println("Autonom Periodic");
  // Autonom mode continuous operations
}

// Disable Init method
void disableInit() {
  Serial.println("Disable Init");
  // Disable mode initialization settings
}

// Disable Periodic method
void disablePeriodic() {
  Serial.println("Disable Periodic");
  // Disable mode continuous operations
}

void setup() {
  // Serial communication initialization
  Serial.begin(9600);

  // Initializing the ArduinoDriveStation library
  driveStation.begin();
  
  // Setting Init and Periodic methods for different modes
  driveStation.setTeleopInitMethod(teleopInit);
  driveStation.setTeleopPeriodicMethod(teleopPeriodic);
  driveStation.setAutonomInitMethod(autonomInit);
  driveStation.setAutonomPeriodicMethod(autonomPeriodic);
  driveStation.setDisableInitMethod(disableInit);
  driveStation.setDisablePeriodicMethod(disablePeriodic);
}

void loop() {
  // Calling the update() method of ArduinoDriveStation library
  driveStation.update();

  // Other operations
}
