/**
 * Vector3DTest unit tests for the class Vector3D
 *
 * @author Øystein Schrøder Elvik
 * @version 1.0
 * @since 05.11.2014
 */

#include <iostream>
#include <cassert>
#include "Vector3D.cpp"

int main()
{
	
	std::cout  << "Vector3DTest" << std::endl; // 5

	// Vector3D(float x, float y, float z);
	Vector3D a (3,4,0);
	assert(a.x==3);
	assert(a.y==4);
	assert(a.z==0);

	// Vector3D copy();
	Vector3D b = a.copy();
	assert(b.x==3);
	assert(b.y==4);
	assert(b.z==0);

	// Vector3D set(float x, float y, float z);
	b.set(1,1,1);
	assert(b.x==1);
	assert(b.y==1);
	assert(b.z==1);

	// Vector3D set(Vector3D* b)
	b.set(&a);
	assert(b.x==3);
	assert(b.y==4);
	assert(b.z==0);

	// float mag();
	assert(a.mag()==5);

	// Vector3D& norm();
	a.norm();
	assert(a.mag()==1);
	assert(a.x==0.6f);
	assert(a.y==0.8f);
	assert(a.z==0);
	a.mult(3).norm();
	assert(a.mag()==1);
	assert(a.x==0.6f);
	assert(a.y==0.8f);
	assert(a.z==0);

	// Vector3D& mult(float n);
	a.mult(5);
	assert(a.mag()==5);
	assert(a.x==3);
	assert(a.y==4);
	assert(a.z==0);

	// Vector3D& add(float n);
	a.add(7);
	assert(a.x==10);
	assert(a.y==11);
	assert(a.z==7);

	// Vector3D& sub(float n);
	a.sub(2);
	assert(a.x==8);
	assert(a.y==9);
	assert(a.z==5);

	// float dot(Vector3D* b);
	b.x = 8;
	b.y = 9;
	b.z = 5;
	assert(a.dot(&b) == 170);

	// Vector3D& cross(Vector3D* b);
	a.cross(&b);
	assert(a.x==0);
	assert(a.y==0);
	assert(a.z==0);

	a.x = 1;
	a.y = 1;
	a.z = 0;
	b.x = 0;
	b.y = 1;
	b.z = 1;

	a.cross(&b);

	assert(a.x==1);
	assert(a.y==-1);
	assert(a.z==1);

	// Vector3D& add(Vector3D* b);
	a.add(&b);
	assert(a.x==1);
	assert(a.y==0);
	assert(a.z==2);

	// Vector3D& sub(Vector3D* b);
	a.sub(&b);
	assert(a.x==1);
	assert(a.y==-1);
	assert(a.z==1);

	//Test method chaining
	a.add(1).add(&b).mult(2);
	assert(a.x==4);
	assert(a.y==2);
	assert(a.z==6);

	// cout.setf(ios::fixed);
	// std::cout  << a.z << std::endl;

	std::cout  << "Vector3DTest: All tests passed" << std::endl;

	
	return 0;
}
