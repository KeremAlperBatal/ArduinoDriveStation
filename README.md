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
#include <ArduinoDriveStation.h>

ArduinoDriveStation driveStation(2, 3); // Define RX and TX pins here

void setup() {
  driveStation.begin();
}

void loop() {
  driveStation.update();
  // Other operations...
}

void teleopInit() {
  // Teleop mode initialization operations
}

void teleopPeriodic() {
  // Teleop mode periodic operations
}

void autonomInit() {
  // Autonom mode initialization operations
}

void autonomPeriodic() {
  // Autonom mode periodic operations
}

void disableInit() {
  // Disable mode initialization operations
}

void disablePeriodic() {
  // Disable mode periodic operations
}
