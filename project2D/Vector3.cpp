#include "Vector3.h"
#include <math.h>
#include <cassert>
#include <yvals.h>


Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0; 
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

//magnitude
float Vector3::magnitude()
{
	float result;
	result = (x * x) + (y * y) + (z * z); 
	return sqrtf(result);
}
float Vector3::magnitudeSqr()
{
	float result;
	result = (x * x) + (y * y) + (z * z);
	return result; 
}

//normalise
void Vector3::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "- normalise: Diveded by zero -");

	if (mag != 0.0f)
	{
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
}

//dot
float Vector3::dot(const Vector3& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}


//Operators 
Vector3 Vector3::operator+(const Vector3& rhs)		//Add two Vectors together
{
	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}
Vector3 Vector3::operator-(const Vector3& rhs)		//Sub one Vector from antoher 
{
	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}
Vector3 Vector3::operator*(const float rhs)			//Multiply two Vectors
{
	return Vector3(x * rhs, y * rhs, z * rhs);
}
Vector3 operator*(const float lhs, Vector3 rhs)	
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}
Vector3 Vector3::operator/(const float rhs)			//Divide two Vectors
{
	return Vector3(x / rhs, y / rhs, z / rhs);
}
	 
//Equals operators 
Vector3 Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}
Vector3 Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}
Vector3 Vector3::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}
Vector3 Vector3::operator/=(const float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

//Subscript
float& Vector3::operator[](int index)
{
	return *(&x + index);
}

//Float operator
Vector3::operator float*()
{
	return &x;
}

//cross
Vector3 Vector3::cross(const Vector3& rhs)
{
	Vector3 result;

	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);

	return result;
}

