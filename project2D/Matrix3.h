#pragma once
#include "Vector2.h"
#include "Vector3.h"

class Matrix3
{
public:
	Matrix3();
	~Matrix3();
	
	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);
	
	Matrix3 operator*(const Matrix3& rhs);
	Vector3 operator*(const Vector3& rhs);

	Vector3& operator[](int index);

	operator float*();

	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);

	void setPosition(float x, float y);
	void setPosition(Vector2 pos);

	void setScale(float x, float y);
	void setScale(Vector2 scale);

	Vector2 getPosition();
	float getRotationZ(); 
	Vector2 getScale(); 


	/*
	X, Y, T
	0, 3, 6
	1, 4, 7
	2, 5, 8
	*/
	float m[9];
	float rotation; 
	Vector2 scale; 
};

