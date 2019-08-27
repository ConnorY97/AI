#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	//magnitude
	float magnitude();
	float magnitudeSqr();

	//normalise
	void normalise();

	//dot
	float dot(const Vector3& rhs);

	//Operators 
	Vector3 operator+(const Vector3& rhs);	//Add two Vectors together
	Vector3 operator-(const Vector3& rhs);	//Sub one Vector from antoher 
	Vector3 operator*(const float rhs);		//Multiply two Vectors
	Vector3 operator/(const float rhs);		//Divide two Vectors 
		  
	//Equals operators 
	Vector3 operator+=(const Vector3& rhs);
	Vector3 operator-=(const Vector3& rhs);
	Vector3 operator*=(const float rhs);
	Vector3 operator/=(const float rhs);

	//Subscript
	float& operator[](int index);

	//Float operator
	operator float*();

	//cross
	Vector3 cross(const Vector3& rhs);



	float x;
	float y;
	float z;

};

// Multiply float with Vector
Vector3 operator*(float lhs, Vector3 rhs);

