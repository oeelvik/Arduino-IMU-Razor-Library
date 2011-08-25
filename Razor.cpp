/*
 * IMU.cpp
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#include "WProgram.h"
#include "Razor.h"

const int Razor::_numberOfReadings = 3;
const int Razor::_defaultAnalogZero = 511;

Razor::Razor(){

	_gyro_x_reverse = false;
	_gyro_y_reverse = false;
	_gyro_z_reverse = false;
	_acc_x_reverse = false;
	_acc_y_reverse = false;
	_acc_z_reverse = false;

	_acc_x_offset = _defaultAnalogZero;
	_acc_y_offset = _defaultAnalogZero;
	_acc_z_offset = _defaultAnalogZero;

	_gyro_x_pin = 0;
	_gyro_y_pin = 1;
	_gyro_z_pin = 2;
	_acc_x_pin = 3;
	_acc_y_pin = 4;
	_acc_z_pin = 5;
}

void Razor::calibrateGyro(){
	//TODO: check if Razor was moved during mesurements (All mesurements ar within aceptable range)
	int numberReadings = 50;
	long x_sum = 0;
	long y_sum = 0;
	long z_sum = 0;
	for(int i = 0; i < numberReadings; i++){
		x_sum += analogRead(_gyro_x_pin);
		y_sum += analogRead(_gyro_y_pin);
		z_sum += analogRead(_gyro_z_pin);
	}

	setGyroXTrim(x_sum/numberReadings);
	setGyroYTrim(y_sum/numberReadings);
	setGyroZTrim(z_sum/numberReadings);
}

const int Razor::getAverageAnalogRead(const int pinNr) const{
	int sum = 0;
	for(int i = 0; i < _numberOfReadings; i++){
		sum += analogRead(pinNr);
 	}
	return sum/_numberOfReadings;
}

const int Razor::calculateTrim(const bool reverse, const int trim, const int pinNr) const {
	if (reverse){
		return trim - getAverageAnalogRead(pinNr);
	}else{
		return getAverageAnalogRead(pinNr) - trim;
	}
}

int Razor::getAccX() const{
	return calculateTrim(getAccXRev(), getAccXTrim(), getAccXPin());
}
int Razor::getAccY() const{
	return calculateTrim(getAccYRev(), getAccYTrim(), getAccYPin());
}
int Razor::getAccZ() const{
	return calculateTrim(getAccZRev(), getAccZTrim(), getAccZPin());
}
int Razor::getGyroX() const{
	return calculateTrim(getGyroXRev(), getGyroXTrim(), getGyroXPin());
}
int Razor::getGyroY() const{
	return calculateTrim(getGyroYRev(), getGyroYTrim(), getGyroYPin());
}
int Razor::getGyroZ() const{
	return calculateTrim(getGyroZRev(), getGyroZTrim(), getGyroZPin());
}
