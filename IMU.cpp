#include "IMU.h"
#include <math.h>

IMU::IMU(){
}

void IMU::update(){
	_nickRad = -asin(dcm.k.x);
	_rollRad = atan2(dcm.k.y, dcm.k.z);
	_yawRad = atan2(dcm.j.x, dcm.i.x);
};

float IMU::getRollRadians(){
	return _rollRad;
};

float IMU::getNickRadians(){
	return _nickRad;
};

float IMU::getYawRadians(){
	return _yawRad;
};

float IMU::getRollDegree(){
	return _rollRad * 180 / M_PI;
};
float IMU::getNickDegree(){
	return _nickRad * 180 / M_PI;
};
float IMU::getYawDegree(){
	return _yawRad * 180 / M_PI;
};