#pragma once

#include"Math.h"

class Vector2;
class Vector4;

//A vector in 3D space.
class Vector3
{
public:

	float x;
	float y;
	float z;

public:

	/* CONSTRUCTORS */

	//Initialize the vector to the Zero vector - <0,0,0>.
	Vector3();

	//Initialize the components of the vector to a single value.
	Vector3(float scalar);

	//Initialize the components of the vector.
	Vector3(float inX, float inY, float inZ);

	//Initialize the components of the vector to a 2D vector and a z value.
	Vector3(const Vector2& v, float inZ);

	//Initialize the components of the vector to an x value and a 2D vector.
	Vector3(float inX, const Vector2& v);

	//Initialize the vector to another 3D vector. (Copy constructor)
	Vector3(const Vector3& v);

	//Initialize the components of the vector to the x, y and z components of a 4D vector.
	Vector3(const Vector4& v);


	/* ASSIGNMENT OPERATORS */

	Vector3& operator = (const Vector3& v);
	Vector3& operator = (const Vector4& v);
	Vector3& operator = (float scalar);


	/* UNARY OPERATORS */

	float& operator[](int n);
	const float& operator[](int n) const;
	Vector3 operator-() const;


	/* ARITHMETIC OPERATORS */

	Vector3 operator+ (const Vector3& v) const;
	Vector3& operator+= (const Vector3& v);

	Vector3 operator- (const Vector3& v) const;
	Vector3& operator-= (const Vector3& v);

	Vector3 operator* (float scalar) const;
	Vector3& operator*= (float scalar);

	Vector3 operator/ (float scalar) const;
	Vector3& operator/= (float scalar);


	/* BOOLEAN OPERATORS */

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;


	/* ADDITIONAL ARITHMETICS */

	static float DotProduct(const Vector3& v1, const Vector3& v2);
	float operator*(const Vector3& v)const;

	static Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);

	//Multiply v1 by v2 componentwise.
	static Vector3 CompMult(const Vector3& v1, const Vector3& v2);

	//Devide v1 by v2 componentwise.
	static Vector3 CompDiv(const Vector3& v1, const Vector3& v2);


	/* GETTERS */

	//Get a vector with unit length pointing in the same direction.
	Vector3 GetNormalized() const;

	//Calculate the magnitude of the vector.
	float GetLength() const;

	//Calculate the squared magnitude of the vector.
	float GetLengthSquared() const;

	//Calculate the distance between v1 and v2 (as a scalar).
	static float GetDistance(const Vector3& v1, const Vector3& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	static float GetDistanceSquared(const Vector3& v1, const Vector3& v2);

	//Calculate the angle(in radians) between v1 and v2.
	static float GetAngle(const Vector3& v1, const Vector3& v2);

	Vector2 XY();

	Vector2 YZ();


	/* PROPERTIES */

	//Check whether the vector has a magnitude of 1.
	bool IsUnit(float tolerance = EPSILON_VECTOR_UNIT) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool NearlyEqual(const Vector3& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether v1 and v2 are orthogonal
	static bool Orthogonal(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_VECTOR_ORTHOGONAL);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	static bool Orthonormal(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_VECTOR_ORTHONORMAL);

	//Check whether v1 and v2 are parallel
	static bool Parallel(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_VECTOR_PARALLEL);


	/* ADDITIONAL OPERATIONS */

	//TODO make unit version of Project on to

	//Get the projection of this vector onto v.
	Vector3 ProjectOnTo(const Vector3& v) const;

	/* Calculate the direction of light reflected from a surface,
	given the direction to the light source and the normal of the surface.*/
	static Vector3 Reflect(const Vector3& light, const Vector3& normal);

	/* Calculate the direction of light refracted on the boundary of two surfaces,
	given the direction to the light source, the normal of the surface and the indices of refraction
	of the material the light is leaving and the material the light is entering. */
	static Vector3 Refract(const Vector3& light, const Vector3& normal, float etaLeaving, float etaEntering);

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	void Normalize();

	//TODO Remove or make it print to log
	void Print() const;

	~Vector3();
};

