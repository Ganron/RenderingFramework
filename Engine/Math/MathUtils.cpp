#include"MathUtils.h"
#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

float DegToRad(float angle)
{
	return angle * TO_RAD_CONST;
}

float RadToDeg(float angle)
{
	return angle * TO_DEG_CONST;
}

void CartToSpherical(const Vector3& cartesian, Vector3& spherical)
{
	spherical.x = cartesian.getLength();
	if (spherical.x < EPSILON_NEAR_ZERO)
	{
		spherical.y = 0.0f;
		spherical.z = 0.0f;
		return;
	}

	float x = cartesian.x;
	float y = cartesian.y;
	float z = cartesian.z;

	spherical.y = Atan2(x, z);

	float zxLength = Sqrt(z * z + x * x);

	spherical.z = Atan2(zxLength, y);

	/*spherical.y = Atan2(y, x);

	float xyLength = Sqrt(x * x + y * y);

	spherical.z = Atan2(xyLength, z);*/
}

void SphericalToCart(const Vector3& spherical, Vector3& cartesian)
{
	cartesian.x = spherical.x * Sin(spherical.z) * Sin(spherical.y);
	cartesian.y = spherical.x * Cos(spherical.z);
	cartesian.z = spherical.x * Sin(spherical.z) * Cos(spherical.y);

	/*cartesian.x = spherical.x * Sin(spherical.z)*Cos(spherical.y);
	cartesian.y = spherical.x * Sin(spherical.z)*Sin(spherical.y);
	cartesian.z = spherical.x * Cos(spherical.z);*/
}

float Step(float x, float edge)
{
	if (x < edge) return 0.0f;
	else return 1.0f;
}

Vector2 Step(Vector2& x, Vector2& edge)
{
	return Vector2(Step(x.x, edge.x), Step(x.y, edge.y));
}

Vector3 Step(Vector3& x, Vector3& edge)
{
	return Vector3(Step(x.x, edge.x), Step(x.y, edge.y), Step(x.z, edge.z));
}

Vector4 Step(Vector4& x, Vector4& edge)
{
	return Vector4(Step(x.x, edge.x), Step(x.y, edge.y), Step(x.z, edge.z), Step(x.w, edge.w));
}

float Smoothstep(float edge0, float edge1, float x)
{
	float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	return t * t * (3 - 2 * t);
}

Vector2 Smoothstep(Vector2& edge0, Vector2& edge1, Vector2& x)
{
	return Vector2(
		Smoothstep(edge0.x, edge1.x, x.x),
		Smoothstep(edge0.y, edge1.y, x.y));
}

Vector3 Smoothstep(Vector3& edge0, Vector3& edge1, Vector3& x)
{
	return Vector3(
		Smoothstep(edge0.x, edge1.x, x.x),
		Smoothstep(edge0.y, edge1.y, x.y),
		Smoothstep(edge0.z, edge1.z, x.z));
}

Vector4 Smoothstep(Vector4& edge0, Vector4& edge1, Vector4& x)
{
	return Vector4(
		Smoothstep(edge0.x, edge1.x, x.x),
		Smoothstep(edge0.y, edge1.y, x.y),
		Smoothstep(edge0.z, edge1.z, x.z),
		Smoothstep(edge0.w, edge1.w, x.w));
}