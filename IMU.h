/*
 * IMU.h
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#ifndef IMU_H_
#define IMU_H_

#include "WProgram.h"

class IMU
{
	public:
		IMU();
		void calibrateGyro();
		void setAccTrim(int acc_roll, int acc_nick, int acc_vert);
		void setAccGain(float acc_gain);
		void setGyroScale(float scale);
		void setAccScale(float scale);
		void setPins(int gyro_roll, int gyro_nick, int gyro_yaw, int acc_roll, int acc_nick, int acc_vert);
		void setReversing(bool gyro_roll, bool gyro_nick, bool gyro_yaw, bool acc_roll, bool acc_nick, bool acc_vert);
		void update();
		int getRollDegree();
		int getNickDegree();
		int getYawDegree();
		int getRoll();
		int getNick();
		int getYaw();
		int getGyroRoll();
		int getGyroNick();
		int getGyroYaw();
		int getAccRoll();
		int getAccNick();

		int getGyroRollPin();
		int getGyroNickPin();
		int getGyroYawPin();
		int getAccRollPin();
		int getAccNickPin();
		int getAccVertPin();

		bool getGyroRollRev();
		bool getGyroNickRev();
		bool getGyroYawRev();
		bool getAccRollRev();
		bool getAccNickRev();
		bool getAccVertRev();

		int getAccRollTrim();
		int getAccNickTrim();
		int getAccVertTrim();
	private:
		int arctan2(int y, int x);

		float _gyro_gain;
		float _acc_gain;

		float _gyro_scale;
		float _acc_scale;

		int _last_update;

		bool _gyro_roll_reverse;
		bool _gyro_nick_reverse;
		bool _gyro_yaw_reverse;
		bool _acc_roll_reverse;
		bool _acc_nick_reverse;
		bool _acc_vert_reverse;

		int _gyro_roll_offset;
		int _gyro_nick_offset;
		int _gyro_yaw_offset;
		int _acc_roll_offset;
		int _acc_nick_offset;
		int _acc_vert_offset;

		int _gyro_roll_pin;
		int _gyro_nick_pin;
		int _gyro_yaw_pin;
		int _acc_roll_pin;
		int _acc_nick_pin;
		int _acc_vert_pin;

		float _roll;
		float _nick;
		float _yaw;
};

#endif /* IMU_H_ */
