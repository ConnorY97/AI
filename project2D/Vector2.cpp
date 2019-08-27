#include "Vector2.h"
#include <math.h>
#include <cassert>



Vector2::Vector2()
{
	x = 0;
	y = 0; 
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y; 
}




Vector2::~Vector2()
{
}

//magnitude
float Vector2::magnitude()
{
	float result; 
	result = (x * x + y * y);
	return sqrtf(result); 
}
float Vector2::magnitudeSqr()
{
	float result;
	result = (x * x) + (y * y);
	return result; 
}

//normalise
void Vector2::normalise()
{
	float mag = magnitude();

	_STL_ASSERT(mag != 0.0f, "- normalise: Diveded by zero -"); 

	if (mag != 0.0f)
	{
		x = x / mag;
		y = y / mag; 
	}
}

//dot
float Vector2::dot(const Vector2& rhs)
{
	return (x * rhs.x) + (y * rhs.y);
}

//Direction
Vector2 Vector2::Right()
{
	return Vector2(-y, x);
}
Vector2 Vector2::Left()
{
	return Vector2(y, -x); 
}

//Arithmitic Operators
Vector2 Vector2::operator+(const Vector2& rhs) //Addition
{
	return Vector2(x + rhs.x, y + rhs.y); 
}
Vector2 Vector2::operator-(const Vector2& rhs) //Subtraction
{
	return Vector2(x - rhs.x, y - rhs.y); 
}
Vector2 Vector2::operator*(const float rhs) //Multiplication rhs only 
{
	return Vector2(x * rhs, y * rhs);
}
Vector2 operator*(float lhs, Vector2 rhs) //Multiplication lhs only 
{
	return Vector2(lhs * rhs.x, lhs * rhs.y); 
}
Vector2 Vector2::operator/(const float rhs) //Devision
{
	return Vector2(x / rhs, y / rhs); 
}
		
//Arithmitic Equals Operators
Vector2 Vector2::operator+=(const Vector2& rhs) //Addition
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}
Vector2 Vector2::operator-=(const Vector2& rhs) //Subtraction
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}
Vector2 Vector2::operator*=(const float rhs) //Multiplication
{
	x *= rhs;
	y *= rhs;

	return *this;
}
Vector2 Vector2::operator/=(const float rhs) //Division
{
	x /= rhs;
	y /= rhs;

	return *this;
}

//Subscript
float& Vector2::operator[](int index)
{
	return *(&x + index);
}

//Float operator
Vector2::operator float *()
{
	return &x; 
}