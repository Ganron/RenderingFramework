#pragma once

#include "Math.h"

class Vector2;
class Vector3;

//A vector in 4D space.
class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

public:

	/* CONSTRUCTORS */

	//Initialize the vector to the Zero vector - <0,0,0,0>.
	Vector4();

	//Initialize the components of the vector to a single value.
	Vector4(float scalar);

	//Initialize the components of the vector.
	Vector4(float inX, float inY, float inZ, float inW = 1.0f);

	//Initialize the vector to another 4D vector. (Copy constructor)
	Vector4(const Vector4& v);

	//Initialize the components of the vector to a 3D vector and a w value.
	Vector4(const Vector3& v, float inW = 1.0f);

	//Initialize the components of the vector to an x value and a 3D vector.
	Vector4(float inX, const Vector3& v);

	//Initialize the components of the vector to two 2D vectors.
	Vector4(const Vector2& v1, const Vector2& v2);

	//Initialize the components of the vector to a 2D vector, a z value, and a w value.
	Vector4(const Vector2& v, float inZ, float inW);

	//Initialize the components of the vector to an x value, a 2D vector, and a w value.
	Vector4(float inX, const Vector2& v, float inW);

	//Initialize the components of the vector to an x value, a y value, and a 2D vector.
	Vector4(float inX, float inY, const Vector2& v);


	/* ASSIGNMENT OPERATORS */
	Vector4& operator=(const Vector4& v);
	Vector4& operator=(const Vector3& v);
	Vector4& operator=(float scalar);

	/* UNARY OPERATORS */

	float& operator[](int n);
	const float& operator[](int n) const;
	Vector4 operator-() const;


	/* ARITHMETIC OPERATORS */

	Vector4 operator+ (const Vector4& v) const;
	Vector4& operator+= (const Vector4& v);

	Vector4 operator- (const Vector4& v) const;
	Vector4& operator-= (const Vector4& v);

	Vector4 operator* (const float scalar) const;
	Vector4& operator*= (const float scalar);

	Vector4 operator/ (const float scalar) const;
	Vector4& operator/= (const float scalar);


	/* BOOLEAN OPERATORS */

	bool operator==(const Vector4& v) const;
	bool operator!=(const Vector4& v) const;


	/* ADDITIONAL ARITHMETICS */

	static float DotProduct(const Vector4& v1, const Vector4& v2);
	float operator*(const Vector4& v) const;

	//Multiply v1 by v2 componentwise.
	static Vector4 CompMult(const Vector4& v1, const Vector4& v2);

	//Devide v1 by v2 componentwise.
	static Vector4 CompDiv(const Vector4& v1, const Vector4& v2);


	/* GETTERS */

	//TODO make non-static
	//Get a vector with unit length pointing in the same direction.
	static Vector4 GetNormalized(const Vector4& v);

	//Calculate the magnitude of the vector.
	float GetLength() const;

	//Calculate the squared magnitude of the vector.
	float GetLengthSquared() const;

	//Calculate the distance between v1 and v2 (as a scalar).
	static float GetDistance(const Vector4& v1, const Vector4& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	static float GetDistanceSquared(const Vector4& v1, const Vector4& v2);


	Vector2 XY() const;

	Vector2 YZ() const;

	Vector2 ZW() const;

	Vector3 XYZ() const;

	Vector3 YZW() const;


	/* PROPERTIES */

	//Check whether the vector has a magnitude of 1.
	bool IsUnit(float tolerance = EPSILON_VECTOR_UNIT) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool NearlyEqual(const Vector4& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether v1 and v2 are orthogonal
	static bool Orthogonal(const Vector4& v1, const Vector4& v2, float tolerance = EPSILON_VECTOR_ORTHOGONAL);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	static bool Orthonormal(const Vector4& v1, const Vector4& v2, float tolerance = EPSILON_VECTOR_ORTHONORMAL);

	//Check whether v1 and v2 are parallel
	static bool Parallel(const Vector4& v1, const Vector4& v2, float tolerance = EPSILON_VECTOR_PARALLEL);


	/* ADDITIONAL OPERATIONS */

	//Get the projection of this vector onto v.
	Vector4 ProjectOnTo(const Vector4& v) const;

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	void Normalize();

	//TODO Remove or make it print to log
	void Print() const;

	~Vector4();
};