#pragma once

#include "Math.h"

//a vector in 2D space.
class Vector2
{
public:

	float x;
	float y;

public:

	/* CONSTRUCTORS */

	//Initialize the vector to the Zero vector - <0,0>.
	Vector2();

	//Initialize the components of the vector to a single value.
	Vector2(float scalar);

	//Initialize the components of the vector.
	Vector2(float inX, float inY);

	//Initialize the vector to another 2D vector. (Copy constructor)
	Vector2(const Vector2& v);


	/* ASSIGNMENT OPERATORS */

	Vector2& operator=(const Vector2& v);
	Vector2& operator=(float scalar);


	/* UNARY OPERATORS */

	float& operator[](int n);
	const float& operator[](int n) const;
	Vector2 operator-() const;


	/* ARITHMETIC OPERATORS */

	Vector2 operator+(const Vector2& v) const;
	Vector2& operator+=(const Vector2& v);

	Vector2 operator-(const Vector2& v) const;
	Vector2& operator-=(const Vector2& v);

	Vector2 operator*(float scalar) const;
	Vector2& operator*=(float scalar);

	Vector2 operator/(float scalar) const;
	Vector2& operator/=(float scalar);


	/* BOOLEAN OPERATORS */

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;


	/* ADDITIONAL ARITHMETICS */

	static float DotProduct(const Vector2& v1, const Vector2& v2);
	float operator*(const Vector2& v) const;

	//Multiply v1 by v2 componentwise.
	static Vector2 CompMult(const Vector2& v1, const Vector2& v2);

	//Devide v1 by v2 componentwise.
	static Vector2 CompDiv(const Vector2& v1, const Vector2& v2);


	/* GETTERS */

	//Get a vector with unit length pointing in the same direction.
	static Vector2 GetNormalized(const Vector2& v);

	//Calculate the magnitude of the vector.
	float GetLength() const;

	//Calculate the squared magnitude of the vector.
	float GetLengthSquared() const;

	//Calculate the distance between v1 and v2 (as a scalar).
	static float GetDistance(const Vector2& v1, const Vector2& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	static float GetDistanceSquared(const Vector2& v1, const Vector2& v2);

	/*
	 Calculate the angle(in radians) between v1 and v2.
	 v1 and v2 need not be normalized.
	*/
	static float GetAngle(const Vector2& v1, const Vector2& v2);
	

	/* PROPERTIES */

	//Check whether the vector has a magnitude of 1.
	bool IsUnit(float tolerance = EPSILON_VECTOR_UNIT) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool NearlyEqual(const Vector2& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether v1 and v2 are orthogonal
	static bool Orthogonal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHOGONAL);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	static bool Orthonormal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHONORMAL);

	//Check whether v1 and v2 are parallel
	static bool Parallel(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_PARALLEL);


	/* ADDITIONAL OPERATIONS */

	//Get the projection of this vector onto v.
	Vector2 ProjectOnTo(const Vector2& v) const;

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	void Normalize();

	//TODO remove or make it print to log
	void Print() const;

	~Vector2();
};

