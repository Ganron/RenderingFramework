#pragma once

#include "Math.h"

/*
* A vector in R^2 (2-dimensional space).
*/
class Vector2
{
public:
	//x and y components are made public to allow for easy manipulation.
  //This is permissible, since encapsulation is not critical here 
  //(the vector may have been represented as a struct as well).
	float x;
	float y;

public:

		/****************/
	 /* CONSTRUCTORS */
	/****************/

	//Initialize the vector to the Zero vector.
	//Vector initialized to: <0,0>.
	Vector2();

	//Initialize the components of the vector to a single value.
	//Vector initialized to: <scalar, scalar>
	explicit Vector2(float scalar);

	//Initialize the components of the vector.
	//Vector initialized to: <inX, inY>
	Vector2(float inX, float inY);

	//Initialize the vector to another 2D vector. (Copy constructor)
	Vector2(const Vector2& v);


		/************************/
	 /* ASSIGNMENT OPERATORS */
	/************************/

	Vector2& operator=(const Vector2& v);


		/*******************/
	 /* UNARY OPERATORS */
	/*******************/

	//Return the n-th vector component, counting from 0.
	//That is to say, v.x=v[0], v.y=[1].
	//NOTE: Index must be either 0 or 1. If index is out of bounds, an assertion is raised.
	float& operator[](int n);

	//Return the n-th vector component of a const vector, counting from 0.
	//That is to say, v.x=v[0], v.y=[1].
	//NOTE: Index must be either 0 or 1. If index is out of bounds, an assertion is raised.
	const float& operator[](int n) const;

	//Negates all vector components.
  //Note that the operator does not modify the existing object, but
  //returns vew Vector3 object with negated components.
	Vector2 operator-() const;


		/************************/
	 /* ARITHMETIC OPERATORS */
	/************************/

	Vector2 operator+(const Vector2& v) const;

	//NOTE: The operator modifies the current object.
	Vector2& operator+=(const Vector2& v);

	Vector2 operator-(const Vector2& v) const;

	//NOTE: The operator modifies the current object.
	Vector2& operator-=(const Vector2& v);

	Vector2 operator*(float scalar) const; //Opposite direction, i.e scalar*vector, is handled by a non-member operator.

	//NOTE: The operator modifies the current object.
	Vector2& operator*=(float scalar);

	Vector2 operator/(float scalar) const;

	//NOTE: The operator modifies the current object.
	Vector2& operator/=(float scalar);


		/*********************************/
	 /* ADDITIONAL VECTOR ARITHMETICS */
	/*********************************/

	//Calculates the dot product of the current vector and the input vector 'v'.
	float dot(const Vector2& v) const;

	//A static function to calculate the dot product of two vectors.
	//TODO: Remove!
	static float dotProduct(const Vector2& v1, const Vector2& v2);
	float operator*(const Vector2& v) const;

	//Multiply the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x * x, etc.
	Vector2 compMult(const Vector2& v) const;

	//Divide the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x / x, etc.
	//NOTE: In case any of the components of 'v' are zero, an assertion is raised.
	Vector2 compDiv(const Vector2& v) const;


		/***********/
	 /* GETTERS */
	/***********/

	//Get a vector with unit length pointing in the same direction.
	//NOTE: Vector must be non-zero, otherwise an assertion is raised.
	Vector2 getNormalized() const;

	//Calculate the magnitude of the vector.
	float getLength() const;

	//Calculate the squared magnitude of the vector.
	float getLengthSquared() const;

	//Calculate the distance from the current vector to the input vector 'v'.
	float getDistanceTo(const Vector2& v) const;

	//Calculate the squared distance from the current vector to the input vector 'v'.
	float getDistanceSquaredTo(const Vector2& v) const;

	//Calculate the angle (in radians) between the current vector and the input vector 'v'.
	float getAngleTo(const Vector2& v) const;

	//Calculate the angle (in radians) between the current unit vector and the input unit vector 'v'.
	//ASSUMPTION: Both vectors must be unit vectors, otherwise the results will be incorrect.
	float getAngleToUnit(const Vector2& v) const;

	//Calculate the distance between v1 and v2 (as a scalar).
	//TODO: Remove!
	static float getDistance(const Vector2& v1, const Vector2& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	//TODO: Remove!
	static float getDistanceSquared(const Vector2& v1, const Vector2& v2);

	//Calculate the angle(in radians) between v1 and v2.
	//TODO Remove!
	static float getAngle(const Vector2& v1, const Vector2& v2);
	

		/**************/
	 /* PROPERTIES */
	/**************/

	//Check whether the vector is a unit vector (i.e., has a magnitude of 1).
	//NOTE: Compares to length squared. Take in mind when choosing tolerance.
	bool isUnit(float tolerance = EPSILON_NEAR_ZERO_SQUARED) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool isEqualTo(const Vector2& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether the current vector is orthogonal to the input vector 'v'.
	bool isOrthogonalTo(const Vector2& v, float tolerance = EPSILON_NEAR_ZERO) const;

	//Check whether the current vector is orthonormal to the input vector 'v', i.e. the two vectors are orthogonal and 
	//are both unit vectors.
	bool isOrthonormalTo(const Vector2& v, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether the current vector is parallel to the input vector 'v'.
	bool isParallelTo(const Vector2& v, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether v1 and v2 are orthogonal
	//TODO: Remove
	static bool orthogonal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHOGONAL);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	//TODO: Remove
	static bool orthonormal(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_ORTHONORMAL);

	//Check whether v1 and v2 are parallel
	//TODO: Remove
	static bool parallel(const Vector2& v1, const Vector2& v2, float tolerance = EPSILON_VECTOR_PARALLEL);


		/*************************/
	 /* ADDITIONAL OPERATIONS */
	/*************************/

	//Get the projection of this vector onto the unit vector 'v'.
	//Quicker than the ordinary projection function.
	//ASSUMPTION: 'v' must be a unit vector, otherwise the result will be incorrect.
	Vector2 projectOnToUnit(const Vector2& v) const;

	//Get the projection of this vector onto v.
	//NOTE: 'v' must be non-zero vector, otherwise an assertion is raised.
	Vector2 projectOnTo(const Vector2& v) const;

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	//NOTE: Function modifies the current vector.
	void normalize();

	//TODO remove or make it print to log
	void print() const;

	~Vector2();
};

//A non-member operator to handle scalar * vector multiplication.
Vector2 operator*(const float scalar, const Vector2& v);