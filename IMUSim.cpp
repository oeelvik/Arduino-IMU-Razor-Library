#include "IMUSim.h"

void IMUSim::update()
{
	static Vector3D w(1,1,0);
	dcm.rotate(&w);

	IMU::update();
}