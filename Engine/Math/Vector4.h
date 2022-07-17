#pragma once

#include "Math.h"

class Vector2;
class Vector3;

/*
* A vector in R^4 (4-dimensional space).
*/
class Vector4
{
public:
	//x,y,z, and w components are made public to allow for easy manipulation.
	//This is permissible, since encapsulation is not critical here 
	//(the vector may have been represented as a struct as well).

	float x;
	float y;
	float z;
	float w;

public:

		/****************/
	 /* CONSTRUCTORS */
	/****************/

	//Initialize the vector to the Zero vector.
	//Vector initialized to: <0,0,0>.
	Vector4();

	//Initialize the components of the vector to a single value.
	//Vector initialized to: <scalar, scalar, scalar, scalar>
	explicit Vector4(float scalar);

	//Initialize the components of the vector.
	//Vector initialized to: <inX, inY, inZ, inW>
	Vector4(float inX, float inY, float inZ, float inW = 1.0f);

	//Initialize the vector to another 4D vector. (Copy constructor)
	Vector4(const Vector4& v);

	//Initialize the components of the vector to a 3D vector and a w value.
	//Vector initialized to: <v, inW> = <v.x, v.y, v.z, inW>
	Vector4(const Vector3& v, float inW = 1.0f);

	//Initialize the components of the vector to an x value and a 3D vector.
	//Vector initialized to: <inX, v> = <inX, v.x, v.y, v.z>
	Vector4(float inX, const Vector3& v);

	//Initialize the components of the vector to two 2D vectors.
	//Vector initialized to: <v1, v2> = <v1.x, v1.y, v2.x, v2.y>
	Vector4(const Vector2& v1, const Vector2& v2);

	//Initialize the components of the vector to a 2D vector, a z value, and a w value.
	//Vector initialized to: <v, inZ, inW> = <v.x, v.y, inZ, inW>
	Vector4(const Vector2& v, float inZ, float inW);

	//Initialize the components of the vector to an x value, a 2D vector, and a w value.
	//Vector initialized to: <inX, v, inW> = <inX, v.x, v.y, inW>
	Vector4(float inX, const Vector2& v, float inW);

	//Initialize the components of the vector to an x value, a y value, and a 2D vector.
	//Vector initialized to: <inX, inY, v> = <inX, inY, v.x, v.y>
	Vector4(float inX, float inY, const Vector2& v);


		/************************/
	 /* ASSIGNMENT OPERATORS */
	/************************/

	Vector4& operator=(const Vector4& v);


		/*******************/
	 /* UNARY OPERATORS */
	/*******************/

	//Return the n-th vector component, counting from 0.
	//That is to say, v.x=v[0], v.y=[1], v.z=v[2], v.w=v[3].
	//NOTE: Index must be between 0 and 3. If index is out of bounds, an assertion is raised.
	float& operator[](int n);

	//Return the n-th vector component of a const vector, counting from 0.
	//That is to say, v.x=v[0], v.y=[1], v.z=v[2], v.w=v[3].
	//NOTE: Index must be between 0 and 3. If index is out of bounds, an assertion is raised.
	const float& operator[](int n) const;

	//Negates all vector components.
	//Note that the operator does not modify the existing object, but
	//returns vew Vector3 object with negated components.
	Vector4 operator-() const;


		/************************/
	 /* ARITHMETIC OPERATORS */
	/************************/

	Vector4 operator+ (const Vector4& v) const;

	//NOTE: The operator modifies the current object.
	Vector4& operator+= (const Vector4& v);

	Vector4 operator- (const Vector4& v) const;

	//NOTE: The operator modifies the current object.
	Vector4& operator-= (const Vector4& v);

	Vector4 operator* (const float scalar) const;//Opposite direction, i.e scalar*vector, is handled by a non-member operator.

	//NOTE: The operator modifies the current object.
	Vector4& operator*= (const float scalar);

	Vector4 operator/ (const float scalar) const;

	//NOTE: The operator modifies the current object.
	Vector4& operator/= (const float scalar);


		/*********************************/
	 /* ADDITIONAL VECTOR ARITHMETICS */
	/*********************************/

	//Calculates the dot product of the current vector and the input vector 'v'.
	float dot(const Vector4& v) const;

	//Multiply the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x * x, etc.
	Vector4 compMult(const Vector4& v);

	//Divide the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x / x, etc.
	//NOTE: In case any of the components of 'v' are zero, an assertion is raised.
	Vector4 compDiv(const Vector4& v);


		/***********/
	 /* GETTERS */
	/***********/

	//Get a vector with unit length pointing in the same direction.
	//NOTE: Vector must be non-zero, otherwise an assertion is raised.
	Vector4 getNormalized() const;

	//Calculate the magnitude of the vector.
	float getLength() const;

	//Calculate the squared magnitude of the vector.
	float getLengthSquared() const;

	//Calculate the distance from the current vector to the input vector 'v'.
	float getDistanceTo(const Vector4& v) const;

	//Calculate the squared distance from the current vector to the input vector 'v'.
	float getDistanceSquaredTo(const Vector4& v) const;

	//Calculate the angle (in radians) between the current vector and the input vector 'v'.
	float getAngleTo(const Vector4& v) const;

	//Calculate the angle (in radians) between the current unit vector and the input unit vector 'v'.
	//ASSUMPTION: Both vectors must be unit vectors, otherwise the results will be incorrect.
	float getAngleToUnit(const Vector4& v) const;

	//Get a 2D vector (Vector2), composed of the x and y components of the current vector.
	Vector2 xy() const;

	//Get a 2D vector (Vector2), composed of the y and z components of the current vector.
	Vector2 yz() const;

	//Get a 2D vector (Vector2), composed of the z and w components of the current vector.
	Vector2 zw() const;

	//Get a 3D vector (Vector3), composed of the x, y, and z components of the current vector.
	Vector3 xyz() const;

	//Get a 3D vector (Vector3), composed of the y, z, and w components of the current vector.
	Vector3 yzw() const;


		/**************/
	 /* PROPERTIES */
	/**************/

	//Check whether the vector is a unit vector (i.e., has a magnitude of 1).
	//NOTE: Compares to length squared. Take in mind when choosing tolerance.
	bool isUnit(float tolerance = EPSILON_VECTOR_UNIT) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool isEqualTo(const Vector4& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether the current vector is orthogonal to the input vector 'v'.
	bool isOrthogonalTo(const Vector4& v, float tolerance = EPSILON_NEAR_ZERO) const;

	//Check whether the current vector is orthonormal to the input vector 'v', i.e. the two vectors are orthogonal and 
	//are both unit vectors.
	bool isOrthonormalTo(const Vector4& v, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether the current vector is parallel to the input vector 'v'.
	bool isParallelTo(const Vector4& v, float tolerance = EPSILON_NEAR_ZERO);


		/*************************/
	 /* ADDITIONAL OPERATIONS */
	/*************************/

	//Get the projection of this vector onto the unit vector 'v'.
	//Quicker than the ordinary projection function.
	//ASSUMPTION: 'v' must be a unit vector, otherwise the result will be incorrect.
	Vector4 projectOnToUnit(const Vector4& v) const;

	//Get the projection of this vector onto v.
	//NOTE: 'v' must be non-zero vector, otherwise an assertion is raised.
	Vector4 projectOnTo(const Vector4& v) const;

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	//NOTE: Function modifies the current vector.
	void normalize();

	//TODO Remove or make it print to log
	void print() const;

	~Vector4();
};

//A non-member operator to handle scalar * vector multiplication.
Vector4 operator*(const float scalar, const Vector4& v);