#pragma once
#include"Math.h"

class Vector3;
class Vector4;
class Matrix3;

class Quaternion
{
public:
	float w;
	float x;
	float y;
	float z;

public:

	/* CONSTRUCTORS */

	//Initialize the quaternion to the Identity quaternion - <1,0,0,0>.
	Quaternion();

	//Initialize the quaternion to another quaternion. (Copy constructor)
	Quaternion(const Quaternion& q);

	//Initialize the components of the quaternion.
	Quaternion(float inW, float inX, float inY, float inZ);

	//Initialize the scalar and vector components of the quaternion.
	Quaternion(float scalar, const Vector3& vector);

	//Create a real quaternion - <scalar,0,0,0>.
	Quaternion(float scalar);

	//Create a pure quaternion - <0,vector>.
	Quaternion(const Vector3& vector);

	//Initialize the components of the quaternion to a 4D vector.
	Quaternion(const Vector4& v);


	/* ASSIGNMENT OPERATOR */

	Quaternion& operator=(const Quaternion& q);


	/* UNARY OPERATORS */

	Quaternion operator-() const;


	/* ARITHMETIC OPERATORS */

	Quaternion operator+(const Quaternion& q) const;
	Quaternion& operator+=(const Quaternion& q);
	
	Quaternion operator-(const Quaternion& q) const;
	Quaternion& operator-=(const Quaternion& q);

	Quaternion operator*(float scalar) const;
	Quaternion& operator*=(float scalar);

	Quaternion operator/(float scalar) const;
	Quaternion& operator/=(float scalar);

	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion& q);


	/* BOOLEAN OPERATORS */

	bool operator==(const Quaternion& q) const;
	bool operator!=(const Quaternion& q) const;


	/* ADDITIONAL ARITHMETICS */

	static float DotProduct(const Quaternion& q1, const Quaternion& q2);


	/* GETTERS */

	Quaternion GetInverse() const;

	Quaternion GetConjugate() const;

	float GetNorm() const;

	float GetNormSquared() const;

	Quaternion GetNormalized() const;

	/*
	 Get the angle of rotation (in radians). 
	 Quaternion must be normalized.
	*/
	float GetRotationAngle() const;

	/*
	 Get the axis of rotation (in radians).
	 Quaternion must be normalized.
	*/
	Vector3 GetRotationAxis() const;

	/* PROPERTIES */

	bool IsUnit(float tolerance = EPSILON_EQUAL) const;

	bool NearlyEqual(const Quaternion& q, float tolerance = EPSILON_EQUAL) const;


	/* ADDITIONAL OPERATIONS */

	//Create a quaternion that performs a rotation from v1 to v2. (v1 and v2 need not be normalized)
	static Quaternion CreateFromTwoVectors(const Vector3& v1, const Vector3& v2);

	/*
	 Convert a rotation from angle/axis to quaternion representation.
	 The angle must be in radians.
	*/
	static Quaternion CreateAxisAngle(float angle, const Vector3& axis);

	//Convert a rotation matrix to a quaternion. (Matrix must represent a pure rotation)
	static Quaternion CreateFromMatrix(const Matrix3& m);

	/*
	 Find the angular distance (along the shorter arc) to quaternion q. (angle in radians) 
	 Both quaternions must be normalized.
	*/
	float AngularDistance(const Quaternion& q) const;

	//T must be between 0.0 and 1.0.
	static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float T, bool shortestPath = true);

	//T must be between 0.0 and 1.0; q1 and q2 must be normalized.
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float T, bool shortestPath = true);

	Vector3 RotateVector(const Vector3& v) const;

	void Normalize();

	~Quaternion();
};

