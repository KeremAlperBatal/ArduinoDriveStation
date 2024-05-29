#ifndef ArduinoDriveStation_h
#define ArduinoDriveStation_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class ArduinoDriveStation {
  public:
    ArduinoDriveStation(int rxPin, int txPin);
    void begin();
    void update();

    // Functions to set Init and Periodic methods
    void setTeleopInitMethod(void (*initMethod)());
    void setTeleopPeriodicMethod(void (*periodicMethod)());
    void setAutonomInitMethod(void (*initMethod)());
    void setAutonomPeriodicMethod(void (*periodicMethod)());
    void setDisableInitMethod(void (*initMethod)());
    void setDisablePeriodicMethod(void (*periodicMethod)());

  private:
    SoftwareSerial bluetooth;
    enum Mode {
      TELEOP,
      AUTONOM,
      DISABLE
    };
    Mode currentMode = DISABLE;
    Mode previousMode = DISABLE;
    bool initRequired = false;

    // Function pointers to store Init and Periodic methods
    void (*teleopInitFunc)();
    void (*teleopPeriodicFunc)();
    void (*autonomInitFunc)();
    void (*autonomPeriodicFunc)();
    void (*disableInitFunc)();
    void (*disablePeriodicFunc)();
};

#endif
