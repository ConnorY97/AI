#include "Vector4.h"
#include <math.h>
#include <cassert>
#include <yvals.h>


Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;

}

Vector4::~Vector4()
{
}

//magnitude
float Vector4::magnitude()
{
	float result;
	result = (x * x) + (y * y) + (z * z);
	return sqrtf(result);
}
float Vector4::magnitudeSqr()
{
	float result;
	result = (x * x) + (y * y) + (z * z);
	return result;
}

//normalise
void Vector4::normalise()
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
float Vector4::dot(const Vector4& rhs)
{
	return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

//Operators
Vector4 Vector4::operator+(const Vector4& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}
Vector4 Vector4::operator-(const Vector4& rhs)
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}
Vector4 Vector4::operator*(const float rhs)
{
	return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}
Vector4 operator*(float lhs, Vector4 rhs)
{
	return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}
Vector4 Vector4::operator/(const float rhs)
{
	return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

//Equals operators
Vector4 Vector4::operator+=(const Vector4& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;

	return *this;
}
Vector4 Vector4::operator-=(const Vector4& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;

	return *this;
}
Vector4 Vector4::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;

	return *this;
}
Vector4 Vector4::operator/=(const float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;

	return *this;
}

//Subscript
float& Vector4::operator[](int index)
{
	return *(&x + index);
}

//Float operator
Vector4::operator float*()
{
	return &x;
}

//cross
Vector4 Vector4::cross(const Vector4& rhs)
{
	Vector4 result;

	result.x = (y * rhs.z) - (z * rhs.y);
	result.y = (z * rhs.x) - (x * rhs.z);
	result.z = (x * rhs.y) - (y * rhs.x);
	result.w = 0;

	return result;
}
