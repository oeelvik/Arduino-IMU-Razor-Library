/**
 * Vector3D holds a 3 dimentional vector along with common matematical operations.
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */
 
#ifndef Vector3D_h
#define Vector3D_h

class Vector3D
{
public:
	Vector3D(float x, float y, float z);

	Vector3D copy();

	Vector3D& set(float x, float y, float z);
	Vector3D& set(Vector3D* b);

	float mag();
	Vector3D& norm();

	Vector3D& mult(float n);
	Vector3D& div(float n);
	Vector3D& add(float n);
	Vector3D& sub(float n);


	float dot(Vector3D* b);
	Vector3D& cross(Vector3D* b);
	Vector3D& add(Vector3D* b);
	Vector3D& sub(Vector3D* b);

	float x;
	float y;
	float z;
};

#endif