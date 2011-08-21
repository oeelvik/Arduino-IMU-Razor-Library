/*
 * IMU.cpp
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#include "WProgram.h"
#include "IMU.h"

IMU::IMU(){
	_gyro_gain = 0.99;
	_acc_gain = 0.01;

	_gyro_scale = 1.f;

	_last_update = 0;

	__gyro_roll_reversgyro_roll_reverse = false;
	_gyro_nick_reverse = false;
	_gyro_yaw_reverse = false;
	_acc_roll_reverse = false;
	_acc_nick_reverse = false;
	_acc_vert_reverse = false;

	_acc_roll_offset = 511;
	_acc_nick_offset = 511;
	_acc_vert_offset = 511;

	_gyro_roll_pin = 0;
	_gyro_nick_pin = 1;
	_gyro_yaw_pin = 2;
	_acc_roll_pin = 3;
	_acc_nick_pin = 4;
	_acc_vert_pin = 5;

	_roll = 511;
	_nick = 511;
	_yaw = 511;
}

void IMU::calibrateGyro(){
	//TODO: check if copter was moved during mesurements (All mesurements ar within aceptable range)
	long roll_sum = 0;
	long nick_sum = 0;
	long yaw_sum = 0;
	for(int i = 0; i < 50; i++){
		roll_sum += analogRead(_gyro_roll_pin);
		nick_sum += analogRead(_gyro_nick_pin);
		yaw_sum += analogRead(_gyro_yaw_pin);
	}

	_gyro_roll_offset = roll_sum/50;
	_gyro_nick_offset = nick_sum/50;
	_gyro_yaw_offset = yaw_sum/50;
}

void IMU::setAccTrim(int acc_roll, int acc_nick, int acc_vert){
	_acc_roll_offset = 511 + acc_roll;
	_acc_nick_offset = 511 + acc_nick;
	_acc_vert_offset = 511 + acc_vert;
}

void IMU::setAccGain(float acc_gain){
	//TODO: Why does changing Acc gain affect gyro gain?
	_acc_gain = acc_gain;
	_gyro_gain = 1 - _acc_gain;
}

void IMU::setGyroScale(float scale){
	_gyro_scale = scale;
}

void IMU::setAccScale(float scale){
	_acc_scale = scale;
}

void IMU::setPins(int gyro_roll, int gyro_nick, int gyro_yaw, int acc_roll, int acc_nick, int acc_vert){
	_gyro_roll_pin = gyro_roll;
	_gyro_nick_pin = gyro_nick;
	_gyro_yaw_pin = gyro_yaw;
	_acc_roll_pin = acc_roll;
	_acc_nick_pin = acc_nick;
	_acc_vert_pin = acc_vert;
}

void IMU::setReversing(bool gyro_roll, bool gyro_nick, bool gyro_yaw, bool acc_roll, bool acc_nick, bool acc_vert){
	_gyro_roll_reverse = gyro_roll;
	_gyro_nick_reverse = gyro_nick;
	_gyro_yaw_reverse = gyro_yaw;
	_acc_roll_reverse = acc_roll;
	_acc_nick_reverse = acc_nick;
	_acc_vert_reverse = acc_vert;
}

void IMU::update(){
	int sampleTime = millis() - _last_update;
	_last_update = millis();

	float gyro_dt = (float) sampleTime / 1000.f;

	/* Complementary filter */
	_roll = (_gyro_gain * (_roll + (getGyroRoll() * gyro_dt))) + (_acc_gain * getAccRoll());
	_nick = (_gyro_gain * (_nick + (getGyroNick() * gyro_dt))) + (_acc_gain * getAccNick());
	_yaw = _yaw + (getGyroYaw() * gyro_dt);
}

int IMU::getRoll(){
	return _roll;
}

int IMU::getNick(){
	return _nick;
}

int IMU::getYaw(){
	return _yaw;
}

int IMU::getRollDegree(){
	//TODO: Remove magic constants
	return (float)(getRoll() - 511) / 1024 * 360;
}

int IMU::getNickDegree(){
	//TODO: Remove magic constants
	return (float)(getNick() - 511) / 1024 * 360;
}

int IMU::getYawDegree(){
	//TODO: Remove magic constants
	return (float)(getYaw() - 511) / 1024 * 360;
}

//TODO: maby limit return values [0 <-> 1024]
//Rate quids per second
int IMU::getGyroRoll(){
	if(_gyro_roll_reverse)
		return (_gyro_roll_offset - analogRead(_gyro_roll_pin)) * _gyro_scale;
	else
		return (analogRead(_gyro_roll_pin) - _gyro_roll_offset) * _gyro_scale;
}

//Rate quids per second
int IMU::getGyroNick(){
	if(_gyro_nick_reverse)
		return (_gyro_nick_offset - analogRead(_gyro_nick_pin)) * _gyro_scale;
	else
		return (analogRead(_gyro_nick_pin) - _gyro_nick_offset) * _gyro_scale;
}

//Rate quids per second
int IMU::getGyroYaw(){
	if(_gyro_yaw_reverse)
		return (_gyro_yaw_offset - analogRead(_gyro_yaw_pin)) * _gyro_scale;
	else
		return (analogRead(_gyro_yaw_pin) - _gyro_yaw_offset) * _gyro_scale;
}

//Angle quids
int IMU::getAccRoll(){
	int r = 0;
	if(_acc_roll_reverse){
		r = ((_acc_roll_offset - analogRead(_acc_roll_pin)) * _acc_scale) + 511;
	} else {
		r = ((analogRead(_acc_roll_pin) - _acc_roll_offset) * _acc_scale) + 511;
	}
	//return arctan2( analogRead(_acc_roll_pin) - _acc_roll_offset, analogRead(_acc_vert_pin) - _acc_vert_offset) + 511;

	if(r < 0 ) r = 0;
	if(r > 1023 ) r = 1023;

	return r;
}

//Angle quids
int IMU::getAccNick(){
	int r = 0;
	if(_acc_nick_reverse){
		r = ((_acc_nick_offset - analogRead(_acc_nick_pin)) * _acc_scale) + 511;
	} else {
		r = ((analogRead(_acc_nick_pin) - _acc_nick_offset) * _acc_scale) + 511;
	}
	//return arctan2(analogRead(_acc_nick_pin) - _acc_nick_offset, analogRead(_acc_vert_pin) - _acc_vert_offset) + 511;

	if(r < 0 ) r = 0;
	if(r > 1023 ) r = 1023;

	return r;
}

//TODO: change to use 3 acses trigonometry instead of 2
/* Using 2 acses trigonometry function will make both roll and nick adjust for changes in vertical gravity and therefore invalidate each other
int IMU::arctan2(int y, int x) {                               // http://www.dspguru.com/comp.dsp/tricks/alg/fxdatan2.htm
	int coeff_1 = 128;                                          // angle in Quids (1024 Quids=360°)
	int coeff_2 = 3*coeff_1;
	float abs_y = abs(y)+1e-10;
	float r, angle;

	if (x >= 0) {
		r = (x - abs_y) / (x + abs_y);
		angle = coeff_1 - coeff_1 * r;
	} else {
		r = (x + abs_y) / (abs_y - x);
		angle = coeff_2 - coeff_1 * r;
	}
	if (y < 0) return int(-angle);
	else return int(angle);
}*/


int IMU::getGyroRollPin(){
	return _gyro_roll_pin;
}

int IMU::getGyroNickPin(){
	return _gyro_nick_pin;
}

int IMU::getGyroYawPin(){
	return _gyro_yaw_pin;
}

int IMU::getAccRollPin(){
	return _acc_roll_pin;
}

int IMU::getAccNickPin(){
	return _acc_nick_pin;
}

int IMU::getAccVertPin(){
	return _acc_vert_pin;
}

bool IMU::getGyroRollRev(){
	return _gyro_roll_reverse;
}

bool IMU::getGyroNickRev(){
	return _gyro_nick_reverse;
}

bool IMU::getGyroYawRev(){
	return _gyro_yaw_reverse;
}

bool IMU::getAccRollRev(){
	return _acc_roll_reverse;
}

bool IMU::getAccNickRev(){
	return _acc_nick_reverse;
}

bool IMU::getAccVertRev(){
	return _acc_vert_reverse;
}

int IMU::getAccRollTrim(){
	return _acc_roll_offset - 511;
}

int IMU::getAccNickTrim(){
	return _acc_nick_offset - 511;
}

int IMU::getAccVertTrim(){
	return _acc_vert_offset - 511;
}
