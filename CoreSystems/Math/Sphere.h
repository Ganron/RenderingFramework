#pragma once
#include"Vector3.h"

class Matrix3;

//A basic sphere class.
class Sphere
{
private:
	Vector3 center;
	float radius;

public:

	/* CONSTRUCTORS */

	//Create a unit sphere.(Center=<0,0,0> and radius=1)
	Sphere();

	//Initialize the center and the radius of the sphere.
	Sphere(const Vector3& inCenter, float inRadius);

	//Initialize the sphere to another sphere.
	Sphere(const Sphere& inSphere);


	/* ASSIGNMENT OPERATOR */
	Sphere& operator=(const Sphere& sphere);


	/* GETTERS */

	//Get the center of the sphere.
	Vector3 GetCenter() const;

	//Get the radius of the sphere.
	float GetRadius() const;


	/* SETTERS */

	//Set the center of the sphere.
	void SetCenter(const Vector3& inCenter);

	//Set the radius of the sphere.
	void SetRadius(float inRadius);


	/* ADDITIONAL OPERATIONS */

	//Calculate a transformed sphere.
	Sphere Transform(const Matrix3& rotation, const Vector3& translation, float scale);

	//Check whether a point is inside this sphere.
	bool Contains(const Vector3& point);

	//Check whether another sphere is inside this sphere.
	bool Contains(const Sphere& sphere);

	~Sphere();
};

//TODO expand {point, aabb, sphere} ??