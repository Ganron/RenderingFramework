#pragma once
#include"Plane.h"

class Vector3;
class Matrix4;
class AABB;
class OBB;
class Sphere;

enum FrustumCullResult { Inside, Intersects, Outside };

//A camera frustum class. Plane normals point to the inside of the frustum.
class Frustum
{
public:
	Plane planes[6]; //left, right, bottom, top, near, far

public:

	/* CONSTRUCTORS */

	//Construct a frustum from a view-projection matrix.
	Frustum(const Matrix4& viewProjMatrix);

	/*
	 Construct a frustum.
	 focalLength must be in the interval (near, far).
	 aspectRatio = height/width.
	*/
	Frustum(float focalLength, float aspectRatio, float near, float far);

	//Initialize the frustum to another frustum.
	Frustum(const Frustum& inFrustum);


	/* SETTER */

	//Extract new frustum planes from a view-projection matrix.
	void SetFrustum(const Matrix4& viewProjMatrix);


	/* CULLING TESTS */

	//Check whether a sphere is inside the frustum, is outside the frustum, or intersects the frustum.
	FrustumCullResult CullTest(const Sphere& sphere);

	//Check whether an AABB is inside the frustum, is outside the frustum, or intersects the frustum.
	FrustumCullResult CullTest(const AABB& aabb);

	//Check whether an OBB is inside the frustum, is outside the frustum, or intersects the frustum.
	FrustumCullResult CullTest(const OBB& obb);
	
};