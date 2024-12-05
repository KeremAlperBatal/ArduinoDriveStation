#ifndef ArduinoDriveStation_h
#define ArduinoDriveStation_h

#include <Arduino.h>
#include <SoftwareSerial.h>


class ArduinoDriveStation {
  public:
    ArduinoDriveStation(int rxPin, int txPin, int maxAxes, int maxButtons);
    void begin(long baudRate);
    void update();

    String getMode();
    float getAxis(int axisID);
    bool getButton(int buttonID);

    // Functions to set Init and Periodic methods
    void setTeleopInitMethod(void (*initMethod)());
    void setTeleopPeriodicMethod(void (*periodicMethod)());
    void setAutonomInitMethod(void (*initMethod)());
    void setAutonomPeriodicMethod(void (*periodicMethod)());
    void setDisableInitMethod(void (*initMethod)());
    void setDisablePeriodicMethod(void (*periodicMethod)());
    void setPracticeInitMethod(void (*initMethod)());
    void setPracticePeriodicMethod(void (*periodicMethod)());

  private:
    SoftwareSerial bluetooth;
    

    int maxAxes;
    int maxButtons;
    enum Mode {
      TELEOP,
      AUTONOM,
      DISABLE,
      PRACTICE
    };
    
    Mode currentMode = DISABLE;
    Mode previousMode = DISABLE;
    bool initRequired = false;
    
    String mode = "Disable";
    float* axes;
    int* buttons;

    void parseData(String data);

    // Function pointers to store Init and Periodic methods
    void (*teleopInitFunc)();
    void (*teleopPeriodicFunc)();
    void (*autonomInitFunc)();
    void (*autonomPeriodicFunc)();
    void (*disableInitFunc)();
    void (*disablePeriodicFunc)();
    void (*practiceInitFunc)();
    void (*practicePeriodicFunc)();
};

#endif
