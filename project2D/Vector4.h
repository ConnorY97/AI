#pragma once
class Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	~Vector4();

	//magnitude
	float magnitude();
	float magnitudeSqr();

	//normalise
	void normalise();

	//dot
	float dot(const Vector4& rhs);

	//Operators 
	Vector4 operator+(const Vector4& rhs);	//Add two Vectors together
	Vector4 operator-(const Vector4& rhs);	//Sub one Vector from antoher 
	Vector4 operator*(const float rhs);		//Multiply two Vectors
	Vector4 operator/(const float rhs);		//Divide two Vectors 

	//Equals operators 
	Vector4 operator+=(const Vector4& rhs);
	Vector4 operator-=(const Vector4& rhs);
	Vector4 operator*=(const float rhs);
	Vector4 operator/=(const float rhs);

	//Subscript
	float& operator[](int index);

	//Float operator
	operator float*();

	//cross
	Vector4 cross(const Vector4& rhs);



	float x;
	float y;
	float z;
	float w; 

};

// Multiply float with Vector
Vector4 operator*(float lhs, Vector4 rhs);


