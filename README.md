# ArduinoDriveStation Library

ArduinoDriveStation is a library for Arduino projects that enables communication over Bluetooth and provides functionality to control the behavior of the project based on the received data.With this library, you can set your robot to teleop mode, autonom mode, disabled mode and practice mode via Bluetooth.You can also get the data from the joystick and control your robot with it on V2.0

## Installation

You can download the library as a zip file and manually install it in your Arduino IDE:

1. Click on the **Code** button at the top of the GitHub repository.
2. Select **Download ZIP** from the dropdown menu to download the library as a zip file.
3. Open Arduino IDE.
4. Go to **Sketch > Include Library > Add .ZIP Library...** from the menu bar.
5. Navigate to the downloaded zip file and select it.
6. Click **Open** to complete the installation.
7. To use the library, add `#include <ArduinoDriveStation.h>` at the beginning of your Arduino sketch.

## Usage

[Link to Arduino Drive Station App](https://github.com/KeremAlperBatal/ArduinoDriveStationApp)

The Arduino Drive Station App provides a user interface to switch between different modes and sending the data of joystick using Bluetooth.

### Initialization

1. Create an ArduinoDriveStation object by specifying the RX and TX pins connected to the Bluetooth module and the total axes and total buttons on your joystick:
    ```cpp
    ArduinoDriveStation driveStation(rxPin, txPin, totalAxes, totalButtons);
    ```
2. Initialize the library in the `setup()` function with a baudRate value (e.g., 9600, 57600):
    ```cpp
    void setup() {
      driveStation.begin(9600);
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
    
    // Set Practice mode initialization method
    driveStation.setPracticeInitMethod(practiceInit);

    // Set Practice mode periodic method
    driveStation.setPracticePeriodicMethod(practicePeriodic);
    ```

### Getting Joystick Data

1. You can get the joystick data using the `getAxis(int axisId)` and `getButton(int buttonId)` methods, they will return the desired values:
    ```cpp
    // This code will return the value of the axis3 as float (you can check the axis number on python app)
    driveStation.getAxis(3);

    // This code will return the value of the button as bool (you can check the button number on python app)
    driveStation.getButton(1);
    ```

## Example Code

```cpp
#include <ArduinoDriveStation.h>

// RX and TX pins of the Bluetooth module
#define RX_PIN 0
#define TX_PIN 1

//max axis number on joystick, max button number on joystick (you can check the max number on python script)
#define totalAxes 6
#define totalButtons 16

ArduinoDriveStation driveStation(RX_PIN, TX_PIN, totalAxes, totalButtons); // RX pin, TX pin for bluetooth connection, max axis number on joystick, max button number on joystick (you can check the max number on python script)

// Teleop Init method
void teleopInit() {
  Serial.println("Teleop Init");
  // Teleop mode initialization settings
}

// Teleop Periodic method
void teleopPeriodic() {
  Serial.println("Teleop Periodic");
  // Teleop mode continuous operations
  Serial.println(driveStation.getAxis(2)); // Get axis 2 value and print it
  Serial.println(driveStation.getButton(1)); // Get button 1 value and print it
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

// Practice Init method
void practicInit() {
  Serial.println("Practice Init");
  // Practic mode initialization settings
}

// Practic Periodic method
void practicPeriodic() {
  Serial.println("Practic Periodic");
  // Practic mode continuous operations
}


void setup() {
  
  driveStation.begin(9600);

  // Setting Init and Periodic methods for different modes
  driveStation.setTeleopInitMethod(teleopInit);
  driveStation.setTeleopPeriodicMethod(teleopPeriodic);
  driveStation.setAutonomInitMethod(autonomInit);
  driveStation.setAutonomPeriodicMethod(autonomPeriodic);
  driveStation.setDisableInitMethod(disableInit);
  driveStation.setDisablePeriodicMethod(disablePeriodic);
  driveStation.setPracticeInitMethod(practiceInit);
  driveStation.setPracticePeriodicMethod(practicePeriodic);
}

void loop() {
  driveStation.update();// DriveStation Library update function must be called every loop
  
  
  Serial.println(driveStation.getMode()); //Printing currentMode
  

}