#ifndef PID_h
#define PID_h

#include <stdint.h>
#include <BluetoothSerial.h>

class PIDController {

  public:
    PIDController();

    void updateConstants(float Kp, float Ki, float Kd);
    void updateSetpoint(float setpoint);
    void getStartTime(int64_t time);
    float calculateCorrection(float linePosition);
  
  private:
    float error, lastError = 0, sumError = 0;
    float Kp, Ki, Kd;
    float pid, setpoint;
    int64_t lastTime;

};

#endif