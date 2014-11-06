/**
 * IMUSimTest unit tests for the class DCM
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#include <iostream>
#include <cassert>
#include <math.h>

#include "Vector3D.cpp"
#include "DCM.cpp"
#include "IMU.cpp"
#include "IMUSim.cpp"

int main()
{
	
	std::cout  << "IMUSimTest" << std::endl; // 5

	// DCM()
	IMUSim imu;
	assert(imu.dcm.i.x == 1);
	assert(imu.dcm.i.y == 0);
	assert(imu.dcm.i.z == 0);
	assert(imu.dcm.j.x == 0);
	assert(imu.dcm.j.y == 1);
	assert(imu.dcm.j.z == 0);
	assert(imu.dcm.k.x == 0);
	assert(imu.dcm.k.y == 0);
	assert(imu.dcm.k.z == 1);

	cout.setf(ios::fixed);

		imu.update();

		// float total = acos(imu.dcm.k.z);
		// float Kxy = sqrt(imu.dcm.k.x * imu.dcm.k.x + imu.dcm.k.y * imu.dcm.k.y);

		// float x = -total * asin(imu.dcm.k.x / Kxy) / (3.14/2);
		// float y = total * asin(imu.dcm.k.y / Kxy) / (3.14/2);
		std::cout  << "rollRad: ";
		std::cout  << imu.getRollRadians();
		std::cout  << " nickRad: ";
		std::cout  << imu.getNickRadians();
		std::cout  << " rollDeg: ";
		std::cout  << imu.getRollDegree();
		std::cout  << " nickDeg: ";
		std::cout  << imu.getNickDegree() << std::endl;



	for (int i = 0; i < 100; ++i)
	{
		imu.update();

		// float total = acos(imu.dcm.k.z);
		// float Kxy = sqrt(imu.dcm.k.x * imu.dcm.k.x + imu.dcm.k.y * imu.dcm.k.y);

		// float x = -total * asin(imu.dcm.k.x / Kxy) / (3.14/2);
		// float y = total * asin(imu.dcm.k.y / Kxy) / (3.14/2);
		

		float n = -asin(imu.dcm.k.x);
		float r = atan2(imu.dcm.k.y, imu.dcm.k.z);
		float y = atan2(imu.dcm.j.x, imu.dcm.i.x);

		std::cout  << " roll: ";
		std::cout  << r;
		std::cout  << " nick: ";
		std::cout  << n;
		std::cout  << " yaw: ";
		std::cout  << y;

		std::cout  << " rollRad: ";
		std::cout  << imu.getRollRadians();
		std::cout  << " nickRad: ";
		std::cout  << imu.getNickRadians();
		std::cout  << " rollDeg: ";
		std::cout  << imu.getRollDegree();
		std::cout  << " nickDeg: ";
		std::cout  << imu.getNickDegree() << std::endl;

	}

	// Vector3D w(1,1,0);
	// imu.dcm.rotate(&w);
	// assert(imu.dcm.i.x == 1);
	// assert(imu.dcm.i.y == 0);
	// assert(imu.dcm.i.z == 0);
	// assert(imu.dcm.j.x == 0);
	// assert(imu.dcm.j.y == 1);
	// assert(imu.dcm.j.z == 0);
	// assert(imu.dcm.k.x == 0);
	// assert(imu.dcm.k.y == 0);
	// assert(imu.dcm.k.z == 1);

	
	// assert(imu.dcm.i.x == 1);
	// assert(imu.dcm.i.y == 0);
	// assert(imu.dcm.i.z == 0);
	// assert(imu.dcm.j.x == 0);
	// assert(imu.dcm.j.y < 1);
	// assert(imu.dcm.j.y > 0.99);
	// assert(imu.dcm.j.z > 0);
	// assert(imu.dcm.j.z < 0.1);
	// assert(imu.dcm.j.mag()-1 < 0.000001);
	// assert(imu.dcm.k.x == 0);
	// assert(imu.dcm.k.y < 0);
	// assert(imu.dcm.k.y > -0.1);
	// assert(imu.dcm.k.z < 1);
	// assert(imu.dcm.k.z > 0.99);
	// assert(imu.dcm.k.mag()-1 < 0.000001);

	std::cout  << "IMUSimTest: All tests passed" << std::endl;

	return 0;
}
