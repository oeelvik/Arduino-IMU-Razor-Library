#include "IMUSim.h"

void IMUSim::update()
{
	static Vector3D w(0.01,0,0);
	dcm.rotate(&w);

	IMU::update();
}