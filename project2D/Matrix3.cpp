#include "Matrix3.h"
#include <memory>



Matrix3::Matrix3()
{
	memset(m, 0, sizeof(float) * 9);
	m[0] = 1;
	m[4] = 1;
	m[8] = 1; 
}

Matrix3::Matrix3(	float m0, float m1, float m2, 
					float m3, float m4, float m5, 
					float m6, float m7, float m8	)
{
	m[0] = m0;
	m[1] = m1;
	m[2] = m2;
	m[3] = m3;
	m[4] = m4;
	m[5] = m5;
	m[6] = m6;
	m[7] = m7;
	m[8] = m8; 
}

Matrix3::~Matrix3()
{
}

Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
	Matrix3 result;

	result.m[0] = (m[0] * rhs.m[0]) + (m[3] * rhs.m[1]) + (m[6] * rhs.m[2]);
	result.m[1] = (m[1] * rhs.m[0]) + (m[4] * rhs.m[1]) + (m[7] * rhs.m[2]);
	result.m[2] = (m[2] * rhs.m[0]) + (m[5] * rhs.m[1]) + (m[8] * rhs.m[2]);
	
	result.m[3] = (m[0] * rhs.m[3]) + (m[3] * rhs.m[4]) + (m[6] * rhs.m[5]);
	result.m[4] = (m[1] * rhs.m[3]) + (m[4] * rhs.m[4]) + (m[7] * rhs.m[5]);
	result.m[5] = (m[2] * rhs.m[3]) + (m[5] * rhs.m[4]) + (m[8] * rhs.m[5]);
														 
	result.m[6] = (m[0] * rhs.m[6]) + (m[3] * rhs.m[7]) + (m[6] * rhs.m[8]);
	result.m[7] = (m[1] * rhs.m[6]) + (m[4] * rhs.m[7]) + (m[7] * rhs.m[8]);
	result.m[8] = (m[2] * rhs.m[6]) + (m[5] * rhs.m[7]) + (m[8] * rhs.m[8]);

	result.rotation = rotation + rhs.rotation;
	result.scale = scale + rhs.scale;
	return result;
}

Vector3 Matrix3::operator*(const Vector3& rhs)
{
	Vector3 result;

	result.x = (m[0] * rhs.x) + (m[3] * rhs.y) + (m[6] * rhs.z); 
	result.y = (m[1] * rhs.x) + (m[4] * rhs.y) + (m[7] * rhs.z); 
	result.z = (m[2] * rhs.x) + (m[5] * rhs.y) + (m[8] * rhs.z); 

	return result; 
}

Vector3& Matrix3::operator[](int index) 
{
	return *((Vector3*)&m[index * 3]);

	//	if (index == 0)
	//		return *((Vector3*)&m[0]);
	//	else if (index == 1)
	//		return *((Vector3*)&m[3]);
	//	else if (index == 2)
	//		return *((Vector3*)&m[6]);

}


Matrix3::operator float*()
{
	return m; 
}

void Matrix3::setRotateX(float radians)
{
	m[4] = cosf(radians);
	m[5] = sinf(radians);

	m[7] = -sinf(radians);
	m[8] = cosf(radians);
}

void Matrix3::setRotateY(float radians)
{
	m[0] = cosf(radians);
	m[2] = -sinf(radians);

	m[6] = sinf(radians);
	m[8] = cosf(radians); 
}

void Matrix3::setRotateZ(float radians)
{
	m[0] = cosf(radians);
	m[1] = sinf(radians);

	m[3] = -sinf(radians);
	m[4] = cosf(radians); 

	rotation = radians; 
}

void Matrix3::setPosition(float x, float y)
{
	m[6] = x; 
	m[7] = y;
}

void Matrix3::setPosition(Vector2 pos)
{
	setPosition(pos.x, pos.y);
}

void Matrix3::setScale(float x, float y)
{
	m[0] = x;
	m[1] = 0;
	m[3] = 0;
	m[4] = y; 

	scale.x = x;
	scale.y = y; 
}

void Matrix3::setScale(Vector2 scale)
{
	setScale(scale.x, scale.y);
}

Vector2 Matrix3::getPosition()
{
	Vector2 position(m[6], m[7]);

	return position;
}
float Matrix3::getRotationZ()
{
	return rotation; 
}
Vector2 Matrix3::getScale()
{
 return scale;
}

