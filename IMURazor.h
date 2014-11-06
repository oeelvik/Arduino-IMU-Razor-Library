/**
 * IMU class representing the IMU razor 6DOF board from sparkfun
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#ifndef IMURazor_H_
#define IMURazor_H_

#define _ACCEL_ZERO 511
#define _ACCEL_WEIGHT 0.01
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
    IMURazor() : IMU(), _accel_x_zero(_ACCEL_ZERO), _accel_y_zero(_ACCEL_ZERO), _accel_z_zero(_ACCEL_ZERO), _accel_weight(_ACCEL_WEIGHT), _mag_weight(_MAG_WEIGHT);

    void update();

    void setPins(int acc_x, int acc_y, int acc_z, int gyro_x, int gyro_y, int gyro_z);
    void setReversing(bool acc_x, bool acc_y, bool acc_z, bool gyro_x, bool gyro_y, bool gyro_z);
    void setAccelTrim(int x, int y, int z);

    void setAccelWeight(float weight);
    void setMagWeight(float weight);

private:
    void calibrateGyro();

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

    int _accel_x_zero;
    int _accel_y_zero;
    int _accel_z_zero;
    int _gyro_x_zero;
    int _gyro_y_zero;
    int _gyro_z_zero;

    float _accel_weight;
    float _mag_weight;

    unsigned long int _lastTime;
};

#endif /* IMURazor_H_ */
