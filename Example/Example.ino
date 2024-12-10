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
void practiceInit() {
  Serial.println("Practice Init");
  // Practic mode initialization settings
}

// Practic Periodic method
void practicePeriodic() {
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
