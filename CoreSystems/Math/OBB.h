#pragma once
#include"Vector3.h"
#include"Matrix3.h"

//An Object-oriented Bounding Box
class OBB
{
public:
	Matrix3 localAxes;
	Vector3 center;
	Vector3 extents;

public:

	/* CONSTRUCTORS */

	//Create a unit OBB. (center = 0.0f, extents = 0.5f, axes = <x,y,z>)
	OBB();

	//Initialize the center, the extents, and the local axes of the OBB.
	OBB(const Vector3& inCenter, const Vector3& inExtents, const Matrix3& inAxes);

	//Initialize the OBB to another OBB.
	OBB(const OBB& inOBB);


	/* ASSIGNMENT OPERATOR */

	OBB& operator=(const OBB& obb);


	/* ADDITIONAL OPERATIONS */

	//Check whether a point is inside this OBB.
	bool Contains(const Vector3& point) const;

	//Calculate a transformed OBB.
	OBB Transform(const Matrix3& rotation, const Vector3& translation, const Vector3 scaleFactors) const;
};

//TODO distToPoint, contains(OBB), expand, getCorners??