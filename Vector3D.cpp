#include "Vector3D.h"

Vector3D::Vector3D(float x = 0, float y = 0, float z = 0)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::copy(){
	Vector3D vec (x,y,z);
	return vec;
}

Vector3D& Vector3D::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	return *this;
}

Vector3D& Vector3D::set(Vector3D* b)
{
	this->x = b->x;
	this->y = b->y;
	this->z = b->z;

	return *this;
}

float Vector3D::mag()
{
	return sqrt( x * x + y * y + z * z );
}

Vector3D& Vector3D::norm()
{
	float m = mag();
	x = x / m;
	y = y / m;
	z = z / m;

	return *this;
}

Vector3D& Vector3D::mult(float n)
{
	x = x * n;
	y = y * n;
	z = z * n;

	return *this;
}

Vector3D& Vector3D::add(float n)
{
	x = x + n;
	y = y + n;
	z = z + n;

	return *this;
}

Vector3D& Vector3D::sub(float n)
{
	x = x - n;
	y = y - n;
	z = z - n;

	return *this;
}

float Vector3D::dot(Vector3D* b)
{
	return x * b->x + y * b->y + z * b->z;
}

Vector3D& Vector3D::cross(Vector3D* b)
{
	float tmp_x = y * b->z - z * b->y;
	float tmp_y = z * b->x - x * b->z;
	z = x * b->y - y * b->x;

	x = tmp_x;
	y = tmp_y;
	
	return *this;
}

Vector3D& Vector3D::add(Vector3D* b)
{
	x = x + b->x;
	y = y + b->y;
	z = z + b->z;

	return *this;
}

Vector3D& Vector3D::sub(Vector3D* b)
{
	x = x - b->x;
	y = y - b->y;
	z = z - b->z;

	return *this;
}