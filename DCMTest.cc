/**
 * DCMTest unit tests for the class DCM
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#include <iostream>
#include <cassert>

#include "Vector3D.cpp"
#include "DCM.cpp"

int main()
{
	
	std::cout  << "DCMTest" << std::endl; // 5

	// DCM()
	DCM dcm;
	assert(dcm.i.x == 1);
	assert(dcm.i.y == 0);
	assert(dcm.i.z == 0);
	assert(dcm.j.x == 0);
	assert(dcm.j.y == 1);
	assert(dcm.j.z == 0);
	assert(dcm.k.x == 0);
	assert(dcm.k.y == 0);
	assert(dcm.k.z == 1);

	// DCM& orthoNorm();
	dcm.i.x += 0.1;
	dcm.j.y -= 0.1;

	dcm.orthoNorm();
	assert(dcm.i.x == 1);
	assert(dcm.i.y == 0);
	assert(dcm.i.z == 0);
	assert(dcm.j.x == 0);
	assert(dcm.j.y == 1);
	assert(dcm.j.z == 0);
	assert(dcm.k.x == 0);
	assert(dcm.k.y == 0);
	assert(dcm.k.z == 1);

	dcm.i.x += 0.3;
	dcm.j.y -= 0.3;

	dcm.orthoNorm();
	assert(dcm.i.x == 1);
	assert(dcm.i.y == 0);
	assert(dcm.i.z == 0);
	assert(dcm.j.x == 0);
	assert(dcm.j.y == 1);
	assert(dcm.j.z == 0);
	assert(dcm.k.x == 0);
	assert(dcm.k.y == 0);
	assert(dcm.k.z == 1);

	Vector3D w (0.1,0,0);
	dcm.rotate(&w);
	assert(dcm.i.x == 1);
	assert(dcm.i.y == 0);
	assert(dcm.i.z == 0);
	assert(dcm.j.x == 0);
	assert(dcm.j.y < 1);
	assert(dcm.j.y > 0.99);
	assert(dcm.j.z > 0);
	assert(dcm.j.z < 0.1);
	assert(dcm.j.mag()-1 < 0.000001);
	assert(dcm.k.x == 0);
	assert(dcm.k.y < 0);
	assert(dcm.k.y > -0.1);
	assert(dcm.k.z < 1);
	assert(dcm.k.z > 0.99);
	assert(dcm.k.mag()-1 < 0.000001);

	// cout.setf(ios::fixed);
	// std::cout  << dcm.k.z << std::endl;

	std::cout  << "DCMTest: All tests passed" << std::endl;

	
	return 0;
}
