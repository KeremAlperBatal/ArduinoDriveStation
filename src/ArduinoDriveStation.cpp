#include "ArduinoDriveStation.h"

ArduinoDriveStation::ArduinoDriveStation(int rxPin, int txPin, int maxAxes, int maxButtons) : bluetooth(rxPin, txPin), maxAxes(maxAxes), maxButtons(maxButtons) {
  axes = new float[maxAxes];
  buttons = new int[maxButtons];
 }

void ArduinoDriveStation::begin(long baudRate) {
  Serial.begin(baudRate);
  bluetooth.begin(baudRate);
}

void ArduinoDriveStation::update() {
  if (bluetooth.available()) {
    String data = bluetooth.readStringUntil('\n');
    parseData(data);
  }
  
  if (mode == "Teleop") {
    currentMode = TELEOP;
} else if (mode == "Autonom") {
    currentMode = AUTONOM;
} else if (mode == "Disable") {
    currentMode = DISABLE;
} else if (mode == "Practice") {
    currentMode = PRACTICE;
} else{
  currentMode = DISABLE;
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
      case PRACTICE:
        if (practiceInitFunc != nullptr) {
          practiceInitFunc();
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
    case PRACTICE:
      if (practicePeriodicFunc != nullptr) {
        practicePeriodicFunc();
      }
      break;
    default:
      break;
  }

  // Other operations
}
float ArduinoDriveStation::getAxis(int axisID) {
  if (axisID >= 0 && axisID < maxAxes) {
    return axes[axisID-1];
  } else {
    return 0.0; // Geçersiz eksen ID'si için varsayılan değer
  }
}

bool ArduinoDriveStation::getButton(int buttonID) {
  if (buttonID >= 0 && buttonID < maxButtons) {
    return buttons[buttonID-1] == 1; // Buton değeri 1 ise true, aksi halde false
  } else {
    return false; // Geçersiz buton ID'si için varsayılan değer
  }
}

String ArduinoDriveStation::getMode() {
  return mode;
}

void ArduinoDriveStation::parseData(String data) {
  if (data.startsWith("{\"mode\":")) {
    mode = data.substring(data.indexOf(":") + 1, data.indexOf("}"));
  } else if (data.startsWith("{\"axes\":")) {
    String axesData = data.substring(data.indexOf(":") + 1, data.indexOf("}"));
    axesData.replace("[", "");
    axesData.replace("]", "");

    int index = 0;
    char* token = strtok((char*)axesData.c_str(), ",");
    while (token != NULL && index < maxAxes) {
      axes[index] = atof(token);
      token = strtok(NULL, ",");
      index++;
    }
  } else if (data.startsWith("{\"buttons\":")) {
    String buttonsData = data.substring(data.indexOf(":") + 1, data.indexOf("}"));
    buttonsData.replace("[", "");
    buttonsData.replace("]", "");

    int index = 0;
    char* token = strtok((char*)buttonsData.c_str(), ",");
    while (token != NULL && index < maxButtons) {
      buttons[index] = atoi(token);
      token = strtok(NULL, ",");
      index++;
    }
  }
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

// Function to set Practice Init method
void ArduinoDriveStation::setPracticeInitMethod(void (*initMethod)()) {
  practiceInitFunc = initMethod;
}

// Function to set Practice Periodic method
void ArduinoDriveStation::setPracticePeriodicMethod(void (*periodicMethod)()) {
  practicePeriodicFunc = periodicMethod;
}
