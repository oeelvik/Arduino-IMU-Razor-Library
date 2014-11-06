/**
 * DCM holds a Direction Cosine Matrix along with common matematical operations.
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#ifndef DCM_h
#define DCM_h

#include "Vector3D.h"

class DCM {
public:
	DCM();

	DCM& orthoNorm();

	DCM& rotate(Vector3D* w);

	Vector3D i;
	Vector3D j;
	Vector3D k;
};

#endif