#pragma once

#include"Math.h"

//Forward declarations
class Vector2;
class Vector4;

/*
* A vector in R^3 (3-dimensional space).
*/
class Vector3
{
public:
	//x,y, and z components are made public to allow for easy manipulation.
	//This is permissible, since encapsulation is not critical here 
	//(the vector may have been represented as a struct as well).

	float x;
	float y;
	float z;

public:

	  /****************/
	 /* CONSTRUCTORS */
	/****************/

	//Initialize the vector to the Zero vector.
	//Vector initialized to: <0,0,0>.
	Vector3();

	//Initialize the components of the vector to a single value.
	//Vector initialized to: <scalar, scalar, scalar>
	explicit Vector3(float scalar);

	//Initialize the components of the vector.
	//Vector initialized to: <inX, inY, inZ>
	Vector3(float inX, float inY, float inZ);

	//Initialize the components of the vector to a 2D vector and a z value.
	//Vector initialized to: <v, inZ> = <v.x, v.y, inZ>
	Vector3(const Vector2& v, float inZ);

	//Initialize the components of the vector to an x value and a 2D vector.
	//Vector initialized to: <inX, v> = <inX, v.y, v.z>
	Vector3(float inX, const Vector2& v);

	//Initialize the vector to another 3D vector. (Copy constructor)
	Vector3(const Vector3& v);

	//Initialize the components of the vector to the x, y and z components of a 4D vector.
	//Vector initialized to: <v.x, v.y, v.z>
	//NOTE: v.w is simply dropped, i.e. no projection is performed (no division by v.w)
	//TODO: Remove!
	Vector3(const Vector4& v);


	  /************************/
   /* ASSIGNMENT OPERATORS */
	/************************/

	Vector3& operator = (const Vector3& v);


	  /*******************/
	 /* UNARY OPERATORS */
	/*******************/

	//Return the n-th vector component, counting from 0.
	//That is to say, v.x=v[0], v.y=[1], v.z=v[2].
	//NOTE: Index must be between 0 and 2. If index is out of bounds, an assertion is raised.
	float& operator[](int n);

	//Return the n-th vector component of a const vector, counting from 0.
  //That is to say, v.x=v[0], v.y=[1], v.z=v[2].
	//NOTE: Index must be between 0 and 2. If index is out of bounds, an assertion is raised.
	const float& operator[](int n) const;

	//Negates all vector components.
	//Note that the operator does not modify the existing object, but
	//returns vew Vector3 object with negated components.
	Vector3 operator-() const;


	  /************************/
	 /* ARITHMETIC OPERATORS */
	/************************/

	Vector3 operator+ (const Vector3& v) const;

	//NOTE: The operator modifies the current object.
	Vector3& operator+= (const Vector3& v);

	Vector3 operator- (const Vector3& v) const;

	//NOTE: The operator modifies the current object.
	Vector3& operator-= (const Vector3& v);

	Vector3 operator* (float scalar) const; //Opposite direction, i.e scalar*vector, is handled by a non-member operator.

	//NOTE: The operator modifies the current object.
	Vector3& operator*= (float scalar);

	Vector3 operator/ (float scalar) const;

	//NOTE: The operator modifies the current object.
	Vector3& operator/= (float scalar);


	  /*********************************/
	 /* ADDITIONAL VECTOR ARITHMETICS */
	/*********************************/

	//Calculates the dot product of the current vector and the input vector 'v'.
	float dot(const Vector3& v) const;

	//A static function to calculate the dot product of two vectors.
	//TODO: Remove!
	static float dotProduct(const Vector3& v1, const Vector3& v2);
	//An shorthand operator for the dot product operation.
	//TODO: Remove!
	float operator*(const Vector3& v)const;

	//Calculates the cross product of the current vector and the input vector 'v'.
	Vector3 cross(const Vector3& v) const;

	//A static function to caluclate the cross product of two vectors.
	//TODO: Remove!
	static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);

	//Multiply the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x * x, etc.
	Vector3 compMult(const Vector3& v) const;

	//Divide the current vector by the input vector 'v' componentwise, i.e.
	//x = this.x / x, etc.
	//NOTE: In case any of the components of 'v' are zero, an assertion is raised.
	Vector3 compDiv(const Vector3& v) const;


	  /***********/
	 /* GETTERS */
	/***********/

	//Get a vector with unit length pointing in the same direction.
	//NOTE: Vector must be non-zero, otherwise an assertion is raised.
	Vector3 getNormalized() const;

	//Calculate the magnitude of the vector.
	float getLength() const;

	//Calculate the squared magnitude of the vector.
	float getLengthSquared() const;

	//Calculate the distance from the current vector to the input vector 'v'.
	float getDistanceTo(const Vector3& v) const;

	//Calculate the squared distance from the current vector to the input vector 'v'.
	float getDistanceSquaredTo(const Vector3& v) const;

	//Calculate the angle (in radians) between the current vector and the input vector 'v'.
	float getAngleTo(const Vector3& v) const;

	//Calculate the angle (in radians) between the current unit vector and the input unit vector 'v'.
	//ASSUMPTION: Both vectors must be unit vectors, otherwise the results will be incorrect.
	float getAngleToUnit(const Vector3& v) const;

	//Calculate the distance between v1 and v2 (as a scalar).
	//TODO: Remove!
	static float getDistance(const Vector3& v1, const Vector3& v2);

	//Calculate the squared distance between v1 and v2 (as a scalar).
	//TODO: Remove!
	static float getDistanceSquared(const Vector3& v1, const Vector3& v2);

	//Calculate the angle(in radians) between v1 and v2.
	//TODO Remove!
	static float getAngle(const Vector3& v1, const Vector3& v2);

	//Get a 2D vector (Vector2), composed of the x and y components of the current vector.
	Vector2 xy();

	//Get a 2D vector (Vector2), composed of the y and z coponents of the current vector.
	Vector2 yz();


	  /**************/
	 /* PROPERTIES */
	/**************/

	//Check whether the vector is a unit vector (i.e., has a magnitude of 1).
	//NOTE: Compares to length squared. Take in mind when choosing tolerance.
	bool isUnit(float tolerance = EPSILON_NEAR_ZERO_SQUARED) const;

	//Check wheter the vector is equal to another vector (within a given tolerance).
	bool isEqualTo(const Vector3& v, float tolerance = EPSILON_EQUAL) const;

	//Check whether the current vector is orthogonal to the input vector 'v'.
	bool isOrthogonalTo(const Vector3& v, float tolerance = EPSILON_NEAR_ZERO) const;

	//Check whether the current vector is orthonormal to the input vector 'v', i.e. the two vectors are orthogonal and 
	//are both unit vectors.
	bool isOrthonormalTo(const Vector3& v, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether the current vector is parallel to the input vector 'v'.
	bool isParallelTo(const Vector3& v, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether v1 and v2 are orthogonal
	//TODO: Remove
	static bool orthogonal(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether v1 and v2 are orthonormal (have unit length and are orthogonal).
	//TODO: Remove
	static bool orthonormal(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_NEAR_ZERO);

	//Check whether v1 and v2 are parallel
	//TODO: Remove
	static bool parallel(const Vector3& v1, const Vector3& v2, float tolerance = EPSILON_NEAR_ZERO);


	  /*************************/
	 /* ADDITIONAL OPERATIONS */
	/*************************/

	//Get the projection of this vector onto the unit vector 'v'.
	//Quicker than the ordinary projection function.
	//ASSUMPTION: 'v' must be a unit vector, otherwise the result will be incorrect.
	Vector3 projectOnToUnit(const Vector3& v) const;

	//Get the projection of this vector onto v.
	//NOTE: 'v' must be non-zero vector, otherwise an assertion is raised.
	Vector3 projectOnTo(const Vector3& v) const;

	//Calculate the direction of light reflected from a surface,
	//given the direction to the light source and the normal of the surface.
	//TODO come up with a better place for this function!
	static Vector3 reflect(const Vector3& light, const Vector3& normal);

	//Calculate the direction of light refracted on the boundary of two surfaces,
	//given the direction to the light source, the normal of the surface and the indices of refraction
	//of the material the light is leaving and the material the light is entering.
	//TODO: come up with a better place for this function
	static Vector3 refract(const Vector3& light, const Vector3& normal, float etaLeaving, float etaEntering);

	//Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
	//NOTE: Function modifies the current vector.
	void normalize();

	//TODO Remove or make it print to log
	void print() const;

	~Vector3();
};

//A non-member operator to handle scalar * vector multiplication.
Vector3 operator*(const float scalar, const Vector3& v);
