#pragma once
#include"Vector3.h"

class Matrix3;

//A 3D plane
class Plane 
{
private:
	Vector3 normal;
	float offset;

public:

	/* CONSTRUCTORS */

	//Initialize the plane to <0,0,1,0>
	Plane();

	//Initialize the normal vector and the offset of the plane.
	Plane(const Vector3& inNormal, float inOffset);

	//Initialize the plane to another plane (represented as a 4D vector).
	Plane(const Vector4& inPlane);

	//Initialize the plane to another plane.
	Plane(const Plane& inPlane);

	//Use a normal vector and a point to initialize the plane.
	Plane(const Vector3& inNormal, const Vector3& inPoint);

	//Use three points to initialize the plane.
	Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2);


	/* ASSIGNMENT OPERATOR */
	Plane& operator=(const Plane& plane);


	/* GETTERS */
	//Get the normal vector of the plane.
	Vector3 GetNormal() const;

	/*
	 Get the offset (relative to the origin) of the plane.
	 If positive, the origin is on the positive side of the plane.
	*/
	float GetOffset() const;
	

	/* SETTERS */
	//Set the normal vector of the plane.
	void SetNormal(const Vector3& inNormal);

	//Set the offset of the plane.
	void SetOffset(float inOffset);


	/* ADDITIONAL OPERATIONS */

	//Find the signed distance from a point in space to the plane.
	float Distance(const Vector3& point) const;

	//Calculate the orthographic projection of a 3D vector on the plane.
	Vector3 ProjectVector(const Vector3& vector) const;

	 //Calculate a transformed plane.
	Plane Transform(const Matrix3& rotation, const Vector3& translation) const;

	/*
	 Calculate a transformed plane.
	 The rotation matrix must be orhogonal.
	*/
	Plane TransformFast(const Matrix3& rotation, const Vector3& translation) const;

	void Normalize();

	~Plane();
};

//TODO IsOnPlane??