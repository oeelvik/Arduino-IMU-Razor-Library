/**
 * IMU class representing the IMU razor 6DOF board from sparkfun
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#ifndef IMURazor_H_
#define IMURazor_H_

// ( (1 / 1024) * 3300 ) / 0,83 (0,83mv/deg/sec) ) = 3.882718 (analogRead -> deg/sec scaling factor)
// ( (1 / 180) * M_PI) / 1000 ) = 0,00001744444 (deg/s -> rad/ms scaling factor)
// (analogRead -> deg/sec scaling factor) * (deg/s -> rad/ms scaling factor) = 6,7766219545148809344975756965508e-5 (analog read ->  rad/ms scaling factor)
// 4x ports = 6,7766219545148809344975756965508e-5 (analog read ->  rad/ms scaling factor) / 4 = 1,6941554886287202336243939241377e-5
#define _GYRO_SCALE 0.000068
#define _GYRO_CALIBRATION_TRESHOLD 2

#define _ACCEL_ZERO 511
#define _ACCEL_WEIGHT 0.01
#define _ACCEL_SCALE 0.010742  // 0.0107421875 // ( (1 / 1024 ) * 3300) / 300 //300[mV pr g] / 3300[Aref] * 1024 = 93 [val at 1g] //Mesured to 102 after trail and error

#define _MAG_WEIGHT 0.0


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "IMU.h"

class IMURazor : public IMU
{
public:
    IMURazor() : IMU(), _accel_x_zero(_ACCEL_ZERO), _accel_y_zero(_ACCEL_ZERO), _accel_z_zero(_ACCEL_ZERO), _accel_weight(_ACCEL_WEIGHT), _mag_weight(_MAG_WEIGHT){};

    void init();

    void update();

    void setPins(int acc_x, int acc_y, int acc_z, int gyro_x, int gyro_y, int gyro_z);
    void setReversing(bool acc_x, bool acc_y, bool acc_z, bool gyro_x, bool gyro_y, bool gyro_z);
    void setAccelTrim(float x, float y, float z);

    void setAccelWeight(float weight);
    void setMagWeight(float weight);

private:
    bool calibrateGyro();

    int _accel_x_pin;
    int _accel_y_pin;
    int _accel_z_pin;
    int _gyro_x_pin;
    int _gyro_y_pin;
    int _gyro_z_pin;

    int _accel_x_reverse;
    int _accel_y_reverse;
    int _accel_z_reverse;
    int _gyro_x_reverse;
    int _gyro_y_reverse;
    int _gyro_z_reverse;

    float _accel_x_zero;
    float _accel_y_zero;
    float _accel_z_zero;
    float _gyro_x_zero;
    float _gyro_y_zero;
    float _gyro_z_zero;

    float _accel_weight;
    float _mag_weight;

    unsigned long int _lastTime;
};

#endif /* IMURazor_H_ */
