/**
 * Abstract IMU class
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#ifndef IMU_h
#define IMU_h

#include "DCM.h"

class IMU
{
public:
    IMU();

    void update();

    float getRollRadians();
    float getNickRadians();
    float getYawRadians();

    float getRollDegree();
    float getNickDegree();
    float getYawDegree();

	DCM dcm;

private:
	float _rollRad;
	float _nickRad;
	float _yawRad;
};

#endif /* IMU_h */