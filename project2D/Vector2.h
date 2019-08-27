#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);

	~Vector2();

	//magnitude
	float magnitude(); 
	float magnitudeSqr(); 

	//normalise
	void normalise(); 

	//dot
	float dot(const Vector2& rhs); 

	//Direction
	Vector2 Right();
	Vector2 Left(); 

	//Operators 
	Vector2 operator+(const Vector2& rhs);	//Add two Vectors together
	Vector2 operator-(const Vector2& rhs);	//Sub one Vector from antoher 
	Vector2 operator*(const float rhs);		//Multiply two Vectors
	Vector2 operator/(const float rhs);		//Divide two Vectors 

	//Equals operators 
	Vector2 operator+=(const Vector2& rhs);
	Vector2 operator-=(const Vector2& rhs);
	Vector2 operator*=(const float rhs);
	Vector2 operator/=(const float rhs);

	//Subscript
	float& operator[](int index); 

	//Float operator
	operator float*(); 




	float x;
	float y; 
};

//Multiplay float with Vector
Vector2 operator*(float lhs, Vector2 rhs);
