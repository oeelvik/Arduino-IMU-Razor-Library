/*
 * IMU.h
 *
 *  Created on: 16. feb. 2011
 *      Author: develop
 */

#ifndef IMU_H_
#define IMU_H_

#include "Razor.h"

class IMU
{
	public:
		IMU();
		
		Razor* getSensor() { return raz; }

		void update();
		int getXDegree();
		int getYDegree();
		int getZDegree();
	
		~IMU();
	private:
		Razor* raz;		

		int _last_update;

		float _roll;
		float _nick;
		float _yaw;
};

#endif /* IMU_H_ */
