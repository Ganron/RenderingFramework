#pragma once
#include"Vector3.h"

class Matrix3;

//An Axis-aligned Bounding Box
class AABB
{
public:
	Vector3 min;
	Vector3 max;

public:

	/* CONSTRUCTORS */

	//Create a unit AABB. (min = -0.5, max = 0.5)
	AABB();

	//Initialize the min and max points of the AABB.
	AABB(const Vector3& inMin, const Vector3& inMax);

	//Initialize the AABB to another AABB.
	AABB(const AABB& inAABB);
	

	/* ASSIGNMENT OPERATOR */

	AABB& operator=(const AABB& aabb);


	/* GETTERS */

	//Get the center of the AABB.
	Vector3 GetCenter();

	//Get the size of the AABB along the three dimensions.
	Vector3 GetSize();

	//Get the extents (half-lengths) of the AABB along the three dimensions.
	Vector3 GetExtents();


	/* ADDITIONAL OPERATIONS */

	//Check whether a point is inside this AABB. 
	bool Contains(const Vector3& point);

	//Check whether another AABB is inside this AABB.
	bool Contains(const AABB& aabb);

	/* 
	 Calculate the shortest distance from a given point to the surface of the AABB.
	 Distance = 0 if the point lies on the AABB or if it is inside the AABB.
	*/
	float Distance(const Vector3& point);

	/*
	 Calculate the square of the shortest distance from a given point to the surface of the AABB.
	 Distance = 0 if the point lies on the AABB or if it is inside the AABB.
	*/
	float DistanceSquared(const Vector3& point);

	//Expand the AABB so that it includes a given point.
	void Expand(const Vector3& point);

	//Expand the AABB so that it includes another AABB.
	void Expand(const AABB& aabb);

	//Calculate a transformed AABB.
	AABB Transform(const Matrix3 & rotation, const Vector3 & translation);

	~AABB();
};