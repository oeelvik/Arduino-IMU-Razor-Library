/*
 * IMU.h
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#ifndef IMU_H_
#define IMU_H_

class Razor
{
	public:
		Razor();
	
		int getGyroXPinn() const { return _gyro_x_pin; }
		int getGyroYPinn() const { return _gyro_y_pin; }
		int getGyroZPinn() const { return _gyro_z_pin; }
		void setGyroXPin(const int pinNum) { _gyro_x_pin = pinNum; }
		void setGyroYPin(const int pinNum) { _gyro_y_pin = pinNum; }
		void setGyroZPin(const int pinNum) { _gyro_z_pin = pinNum; }

		int getAccXPinn() const { return _acc_x_pin; }
		int getAccYPinn() const { return _acc_y_pin; }
		int getAccZPinn() const { return _acc_z_pin; }	
		void setAccXPin(const int pinNum) { _acc_x_pin = pinNum; }
		void setAccXPin(const int pinNum) { _acc_x_pin = pinNum; }
		void setAccXPin(const int pinNum) { _acc_x_pin = pinNum; }

		bool getAccXRev() const { return _acc_x_reverse; }
		bool getAccYRev() const { return _acc_y_reverse; }
		bool getAccZRev() const { return _acc_z_reverse; }
		void setAccXRev(const bool reversed) { _acc_x_reverse = reversed; }
		void setAccYRev(const bool reversed) { _acc_y_reverse = reversed; }
		void setAccZRev(const bool reversed) { _acc_z_reverse = reversed; }

		bool getGyroXRev() const { return _gyro_x_reverse; }
		bool getGyroYRev() const { return _gyro_y_reverse; }
		bool getGyroZRev() const { return _gyro_Z_reverse; }
		void setGyroXRev(const bool reversed) { _gyro_x_reverse = reversed; }
		void setGyroZRev(const bool reversed) { _gyro_Y_reverse = reversed; }
		void setGyroZRev(const bool reversed) { _gyro_Z_reverse = reversed; }
	
		bool getAccXTrim() const { return _acc_x_offset; }		
		bool getAccYTrim() const { return _acc_y_offset; }
		bool getAccZTrim() const { return _acc_z_offset; }
		void setAccXTrim(const int trim) { _acc_x_offset = trim; }	
		void setAccYTrim(const int trim) { _acc_y_offset = trim; }	
		void setAccZTrim(const int trim) { _acc_z_offset = trim; }
	
		bool getGyroXTrim() const { return _gyro_x_offset; }
		bool getGyroYTrim() const { return _gyro_y_offset; }
		bool getGyroZTrim() const { return _gyro_z_offset; }
/*		void setGyroXTrim(const int trim) { _gyro_x_offset = trim; }
		void setGyroYTrim(const int trim) { _gyro_y_offset = trim; }
		void setGyroZTrim(const int trim) { _gyro_z_offset = trim; }
*/
		void calibrateGyro();
		//void calibrateAcc(); Dersom denne er mulig å implementere på noe fornuftig vis.
	
		int getAccX() const;
		int getAccY() const;
		int getAccZ() const;
		int getGyroX() const;
		int getGyroY() const;
		int getGyroZ() const;

	private:
		bool _gyro_x_reverse;
		bool _gyro_y_reverse;
		bool _gyro_z_reverse;
		bool _acc_x_reverse;
		bool _acc_y_reverse;
		bool _acc_z_reverse;

		int _gyro_x_offset;
		int _gyro_y_offset;
		int _gyro_z_offset;
		int _acc_x_offset;
		int _acc_y_offset;
		int _acc_z_offset;

		int _gyro_x_pin;
		int _gyro_y_pin;
		int _gyro_z_pin;
		int _acc_x_pin;
		int _acc_y_pin;
		int _acc_z_pin;
};

#endif /* IMU_H_ */
