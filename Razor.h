/*
 * IMU.h
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#ifndef RAZOR_H_
#define RAZOR_H_

class Razor
{
	public:
		Razor();
	
		int getGyroXPin() const { return _gyro_x_pin; }
		int getGyroYPin() const { return _gyro_y_pin; }
		int getGyroZPin() const { return _gyro_z_pin; }
		void setGyroXPin(const int pinNum) { _gyro_x_pin = pinNum; }
		void setGyroYPin(const int pinNum) { _gyro_y_pin = pinNum; }
		void setGyroZPin(const int pinNum) { _gyro_z_pin = pinNum; }

		int getAccXPin() const { return _acc_x_pin; }
		int getAccYPin() const { return _acc_y_pin; }
		int getAccZPin() const { return _acc_z_pin; }	
		void setAccXPin(const int pinNum) { _acc_x_pin = pinNum; }
		void setAccYPin(const int pinNum) { _acc_y_pin = pinNum; }
		void setAccZPin(const int pinNum) { _acc_z_pin = pinNum; }

		bool getAccXRev() const { return _acc_x_reverse; }
		bool getAccYRev() const { return _acc_y_reverse; }
		bool getAccZRev() const { return _acc_z_reverse; }
		void setAccXRev(const bool reversed) { _acc_x_reverse = reversed; }
		void setAccYRev(const bool reversed) { _acc_y_reverse = reversed; }
		void setAccZRev(const bool reversed) { _acc_z_reverse = reversed; }

		bool getGyroXRev() const { return _gyro_x_reverse; }
		bool getGyroYRev() const { return _gyro_y_reverse; }
		bool getGyroZRev() const { return _gyro_z_reverse; }
		void setGyroXRev(const bool reversed) { _gyro_x_reverse = reversed; }
		void setGyroYRev(const bool reversed) { _gyro_y_reverse = reversed; }
		void setGyroZRev(const bool reversed) { _gyro_z_reverse = reversed; }
	
		int getAccXTrim() const { return _acc_x_trim; }		
		int getAccYTrim() const { return _acc_y_trim; }
		int getAccZTrim() const { return _acc_z_trim; }
		void setAccXTrim(const int trim) { _acc_x_trim = trim; }	
		void setAccYTrim(const int trim) { _acc_y_trim = trim; }	
		void setAccZTrim(const int trim) { _acc_z_trim = trim; }
	
		int getGyroXTrim() const { return _gyro_x_trim; }
		int getGyroYTrim() const { return _gyro_y_trim; }
		int getGyroZTrim() const { return _gyro_z_trim; }
		
		void calibrateGyro();
		//void calibrateAcc(); If possible to implement in the future.

		/*
		 * GetAcc returns value between -300 and 300, where 0 = 0g, -300 = -3g, 300 = 3g.
		 * This are the values we get from the ACC doing as few calculations as possible, but stil 
		 * using trim and reverse.
		 */ 	
		int getAccX() const;
		int getAccY() const;
		int getAccZ() const;
		/*
		 * GetGyro returns value between -300 and 600, where 0 = 0deg/s, 511 = 0deg/s.
		 */
		//TODO why is gyro 0deg/s 1.25v, and how do you adjust for this to get a better reading?
		int getGyroX() const;
		int getGyroY() const;
		int getGyroZ() const;

	private:
		const int getAverageAnalogRead(const int pinNr) const;
		const int calculateTrim(const bool reverse, const int trim, const int pinNr) const;

		void setGyroXTrim(const int trim) { _gyro_x_trim = trim; }
		void setGyroYTrim(const int trim) { _gyro_y_trim = trim; }
		void setGyroZTrim(const int trim) { _gyro_z_trim = trim; }
	
		static const int _numberOfReadings;
		static const int _defaultAnalogZero;

		bool _gyro_x_reverse;
		bool _gyro_y_reverse;
		bool _gyro_z_reverse;
		bool _acc_x_reverse;
		bool _acc_y_reverse;
		bool _acc_z_reverse;

		int _gyro_x_trim;
		int _gyro_y_trim;
		int _gyro_z_trim;
		int _acc_x_trim;
		int _acc_y_trim;
		int _acc_z_trim;

		int _gyro_x_pin;
		int _gyro_y_pin;
		int _gyro_z_pin;
		int _acc_x_pin;
		int _acc_y_pin;
		int _acc_z_pin;
};

#endif
