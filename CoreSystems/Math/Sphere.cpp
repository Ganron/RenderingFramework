#include"Sphere.h"
#include"Vector3.h"
#include"Matrix3.h"

Sphere::Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f)
{
}

Sphere::Sphere(const Vector3 & inCenter, float inRadius) :center(inCenter), radius(inRadius)
{
}

Sphere::Sphere(const Sphere & inSphere)
{
	center = inSphere.GetCenter();
	radius = inSphere.GetRadius();
}

Sphere & Sphere::operator=(const Sphere & sphere)
{
	center = sphere.GetCenter();
	radius = sphere.GetRadius();
	return *this;
}

Vector3 Sphere::GetCenter() const
{
	return center;
}

float Sphere::GetRadius() const
{
	return radius;
}

void Sphere::SetCenter(const Vector3 & inCenter)
{
	center = inCenter;
}

void Sphere::SetRadius(float inRadius)
{
	radius = inRadius;
}

Sphere Sphere::Transform(const Matrix3 & rotation, const Vector3 & translation, float scale)
{
	return Sphere(rotation*center + translation, radius*scale);
}

bool Sphere::Contains(const Vector3 & point)
{
	return (center - point).GetLengthSquared() <= radius * radius;
}

bool Sphere::Contains(const Sphere & sphere)
{
	float radiusDiff = radius - sphere.GetRadius();
	if (radiusDiff < 0.0f)
	{
		return false;
	}
	return (center - sphere.GetCenter()).GetLengthSquared() <= radiusDiff*radiusDiff;
}

Sphere::~Sphere()
{
}

