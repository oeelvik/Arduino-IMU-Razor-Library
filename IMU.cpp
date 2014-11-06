#include "IMU.h"
#include <math.h>

IMU::IMU(){
}

void IMU::update(){
	// ALT 1
	float total = acos(dcm.k.z);
	float Kxy = sqrt(dcm.k.x * dcm.k.x + dcm.k.y * dcm.k.y);

	if(fabs(Kxy) < 0.01) { //Default to roll when close to uppside down
		_nickRad = 0;
		_rollRad = total;
	} else {
		_nickRad = -total * asin(dcm.k.x / Kxy) / (3.14/2);
		_rollRad = total * asin(dcm.k.y / Kxy) / (3.14/2);
	}

	// ALT 2
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