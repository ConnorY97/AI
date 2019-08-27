#pragma once
#include "Vector4.h"
#include "Vector3.h"
class Matrix4
{
public:
	Matrix4();
	~Matrix4();

	Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);

	Matrix4 operator*(const Matrix4& rhs);
	Vector4 operator*(const Vector4& rhs);

	Vector4& operator[](int index);

	operator float*();

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3 pos);

	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);

	Vector3 getPosition();
	/*float getRotationZ();
	Vector3 getScale();*/


	float m[16];
};

