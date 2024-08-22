#include "ArduinoDriveStation.h"

ArduinoDriveStation::ArduinoDriveStation(int rxPin, int txPin) : bluetooth(rxPin, txPin) {}

void ArduinoDriveStation::begin() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void ArduinoDriveStation::update() {
  // Process received data from Bluetooth
  if (bluetooth.available()) {
    char receivedChar = (char)bluetooth.read();
    static String receivedPacket = "";
    
    // If start of packet
    if (receivedChar == '<') {
      receivedPacket = "";  // Start a new packet
    } else if (receivedChar == '>') {
      // End of packet, process it
      if (receivedPacket == "T") {
        currentMode = TELEOP;
      } else if (receivedPacket == "A") {
        currentMode = AUTONOM;
      } else if (receivedPacket == "D") {
        currentMode = DISABLE;
      }
      receivedPacket = "";  // Reset the packet
    } else {
      // Append received char to the packet
      receivedPacket += receivedChar;
    }
  }

  // Set initRequired flag to true when mode changes
  if (currentMode != previousMode) {
    initRequired = true;
    previousMode = currentMode;
  } else {
    initRequired = false;
  }

  // Call the Init method once when mode changes
  if (initRequired) {
    switch (currentMode) {
      case TELEOP:
        if (teleopInitFunc != nullptr) {
          teleopInitFunc();
        }
        break;
      case AUTONOM:
        if (autonomInitFunc != nullptr) {
          autonomInitFunc();
        }
        break;
      case DISABLE:
        if (disableInitFunc != nullptr) {
          disableInitFunc();
        }
        break;
      default:
        break;
    }
  }

  // Call the Periodic method continuously
  switch (currentMode) {
    case TELEOP:
      if (teleopPeriodicFunc != nullptr) {
        teleopPeriodicFunc();
      }
      break;
    case AUTONOM:
      if (autonomPeriodicFunc != nullptr) {
        autonomPeriodicFunc();
      }
      break;
    case DISABLE:
      if (disablePeriodicFunc != nullptr) {
        disablePeriodicFunc();
      }
      break;
    default:
      break;
  }

  // Other operations
}


// Function to set Teleop Init method
void ArduinoDriveStation::setTeleopInitMethod(void (*initMethod)()) {
  teleopInitFunc = initMethod;
}

// Function to set Teleop Periodic method
void ArduinoDriveStation::setTeleopPeriodicMethod(void (*periodicMethod)()) {
  teleopPeriodicFunc = periodicMethod;
}

// Function to set Autonom Init method
void ArduinoDriveStation::setAutonomInitMethod(void (*initMethod)()) {
  autonomInitFunc = initMethod;
}

// Function to set Autonom Periodic method
void ArduinoDriveStation::setAutonomPeriodicMethod(void (*periodicMethod)()) {
  autonomPeriodicFunc = periodicMethod;
}

// Function to set Disable Init method
void ArduinoDriveStation::setDisableInitMethod(void (*initMethod)()) {
  disableInitFunc = initMethod;
}

// Function to set Disable Periodic method
void ArduinoDriveStation::setDisablePeriodicMethod(void (*periodicMethod)()) {
  disablePeriodicFunc = periodicMethod;
}
