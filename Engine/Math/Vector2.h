#pragma once

#include "Math.h"

//A vector in 2D space.
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

	static float dotProduct(const Vector2& v1, const Vector2& v2);
	float operator*(const Vector2& v) const;

	//Multiply v1 by v2 componentwise.
	static Vector2 compMult(const Vector2& v1, const Vector2& v2);

	//Devide v1 by v2 componentwise.
	static Vector2 compDiv(const Vector2& v1, const Vector2& v2);


	/* GETTERS */

	//Get a vector with unit length pointing in the same direction.
	Vector2 getNormalized() const;

	//Calculate the magnitude of the vector.
	float getLength() const;

	//Calculate the squared magnitude of the vector.
	float getLengthSquared() const;

	//Calculate the distance between v1 and v2 (as a scalar).
	static float getDistance(const Vector2& v1, const Vector2& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	static float getDistanceSquared(const Vector2& v1, const Vector2& v2);

	/*
	 Calculate the angle(in radians) between v1 and v2.
	 v1 and v2 need not be normalized.
	*/
	static float getAngle(const Vector2& v1, const Vector2& v2);
	

	/* PROPERTIES */

	//Check whether the vector has a magnitude of 1.
	bool isUnit(float tolerance = EPSILON_VECTOR_UNIT) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool isEqualTo(const Vector2& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether v1 and v2 are orthogonal
	static bool orthogonal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHOGONAL);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	static bool orthonormal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHONORMAL);

	//Check whether v1 and v2 are parallel
	static bool parallel(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_PARALLEL);


	/* ADDITIONAL OPERATIONS */

	//Get the projection of this vector onto v.
	Vector2 projectOnTo(const Vector2& v) const;

	//normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	void normalize();

	//TODO remove or make it print to log
	void print() const;

	~Vector2();
};

