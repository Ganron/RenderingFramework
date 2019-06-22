#include"Plane.h"
#include"Matrix3.h"
#include"Matrix4.h"
#include"Vector4.h"

Plane::Plane() : normal(0.0f, 0.0f, 1.0f), offset(0.0f)
{
}

Plane::Plane(const Vector3 & inNormal, float inOffset) : normal(inNormal), offset(inOffset)
{
}

Plane::Plane(const Vector4 & inPlane):normal(inPlane.x,inPlane.y,inPlane.z), offset(inPlane.w)
{
}

Plane::Plane(const Plane & inPlane)
{
	normal = inPlane.GetNormal();
	offset = inPlane.GetOffset();
}

Plane::Plane(const Vector3 & inNormal, const Vector3 & inPoint)
{
	normal = inNormal;
	offset = -inNormal * inPoint;
}

Plane::Plane(const Vector3 & point0, const Vector3 & point1, const Vector3 & point2)
{
	normal = (Vector3::CrossProduct(point1 - point0, point2 - point0)).GetNormalized();
}

Plane & Plane::operator=(const Plane & plane)
{
	normal = plane.GetNormal();
	offset = plane.GetOffset();
	return *this;
}

Vector3 Plane::GetNormal() const
{
	return normal;
}

float Plane::GetOffset() const
{
	return offset;
}

void Plane::SetNormal(const Vector3 & inNormal)
{
	normal = inNormal;
}

void Plane::SetOffset(float inOffset)
{
	offset = inOffset;
}

float Plane::Distance(const Vector3 & point) const
{
	return normal*point + offset;
}

//TODO make a faster version of GetNormalized or use LengthSquared
Vector3 Plane::ProjectVector(const Vector3 & vector) const
{
	Vector3 n = normal.GetNormalized();
	return vector - vector.ProjectOnTo(n);
}

Plane Plane::Transform(const Matrix3 & rotation, const Vector3& translation) const
{
	Matrix3 rotationInv = rotation.GetInverse();
	Matrix4 transform = Matrix4(rotationInv, -rotationInv * translation).GetTranspose();
	Vector4 plane(normal, offset);
	return (Plane)(transform*plane);
}

Plane Plane::TransformFast(const Matrix3& rotation, const Vector3& translation) const
{
	Matrix4 transform = Matrix4(rotation, - rotation.GetTranspose()*translation).GetTranspose();
	Vector4 plane(normal, offset);
	return (Plane)(transform*plane);
}

void Plane::Normalize()
{
	normal.Normalize();
}

Plane::~Plane()
{
}
