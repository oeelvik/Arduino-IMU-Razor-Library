/*
 * IMU.cpp
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#include "WProgram.h"
#include "Razor.h"

Razor::Razor(){

	_gyro_x_reverse = false;
	_gyro_y_reverse = false;
	_gyro_z_reverse = false;
	_acc_x_reverse = false;
	_acc_y_reverse = false;
	_acc_z_reverse = false;

	_acc_x_offset = 511;
	_acc_y_offset = 511;
	_acc_z_offset = 511;

	_gyro_x_pin = 0;
	_gyro_y_pin = 1;
	_gyro_z_pin = 2;
	_acc_x_pin = 3;
	_acc_y_pin = 4;
	_acc_z_pin = 5;
}

void Razor::calibrateGyro(){
	//TODO: check if Razor was moved during mesurements (All mesurements ar within aceptable range)
	long x_sum = 0;
	long y_sum = 0;
	long z_sum = 0;
	for(int i = 0; i < 50; i++){
		x_sum += analogRead(_gyro_x_pin);
		y_sum += analogRead(_gyro_y_pin);
		z_sum += analogRead(_gyro_z_pin);
	}

	_gyro_x_offset = x_sum/50;
	_gyro_y_offset = y_sum/50;
	_gyro_z_offset = z_sum/50;
}

//Gets a sum of several reading from the ACC
int Razor::getAccX() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_acc_x_pin);
 	}	
	return sum/loops;
}
int Razor::getAccY() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_acc_y_pin);
 	}	
	return sum/loops;
}
int Razor::getAccZ() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_acc_z_pin);
 	}	
	return sum/loops;
}
int Razor::getGyroX() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_gyro_x_pin);
 	}	
	return sum/loops;
}
int Razor::getGyroY() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_gyro_y_pin);
 	}	
	return sum/loops;
}
int Razor::getGyroZ() const{
	int sum = 0;
	int loops = 3;
	for(int i = 0; i < loops; i++){
		sum += analogRead(_gyro_z_pin);
 	}	
	return sum/loops;
}
