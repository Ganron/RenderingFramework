#include"Frustum.h"
#include"Vector4.h"
#include"Matrix4.h"
#include"Sphere.h"
#include"AABB.h"
#include"OBB.h"

Frustum::Frustum(const Matrix4 & viewProjMatrix)
{
	planes[0] = (viewProjMatrix.GetRow(3) + viewProjMatrix.GetRow(0)).getNormalized(); //left

	planes[1] = (viewProjMatrix.GetRow(3) - viewProjMatrix.GetRow(0)).getNormalized(); //right

	planes[2] = (viewProjMatrix.GetRow(3) + viewProjMatrix.GetRow(1)).getNormalized(); //bottom

	planes[3] = (viewProjMatrix.GetRow(3) - viewProjMatrix.GetRow(1)).getNormalized(); //top

	planes[4] = (viewProjMatrix.GetRow(3) + viewProjMatrix.GetRow(2)).getNormalized(); //near

	planes[5] = (viewProjMatrix.GetRow(3) - viewProjMatrix.GetRow(2)).getNormalized(); //far
}

Frustum::Frustum(float focalLength, float aspectRatio, float near, float far)
{
	float lrCoeff = 1 / Sqrt(focalLength*focalLength + 1);
	float lrCoeffFL = focalLength * lrCoeff;
	float btCoeff = 1 / Sqrt(focalLength*focalLength + aspectRatio * aspectRatio);
	float btCoeffFL = focalLength * btCoeff;
	float btCoeffAR = -aspectRatio * btCoeff;

	planes[0] = Vector4(lrCoeffFL, 0.0f, -lrCoeff, 0.0f); //left

	planes[1] = Vector4(-lrCoeffFL, 0.0f, -lrCoeff, 0.0f); //right

	planes[2] = Vector4(0.0f, btCoeffFL, btCoeffAR, 0.0f); //bottom

	planes[3] = Vector4(0.0f, -btCoeffFL, btCoeffAR, 0.0f); // top

	planes[4] = Vector4(0.0f, 0.0f, -1.0f, -near); //near

	planes[5] = Vector4(0.0f, 0.0f, 1.0f, far); //far
}

Frustum::Frustum(const Frustum & inFrustum)
{
	for (int i = 0; i < 6; i++)
	{
		planes[i] = inFrustum.planes[i];
	}
}

void Frustum::SetFrustum(const Matrix4 & viewProjMatrix)
{
	*this = Frustum(viewProjMatrix);
}

FrustumCullResult Frustum::CullTest(const Sphere & sphere)
{
	FrustumCullResult result = Inside;

	float radius = sphere.GetRadius();

	for (int i = 0; i < 6; i++)
	{
		float distance = planes[i].Distance(sphere.GetCenter());
		if (distance <= -radius)
		{
			return Outside;
		}
		if (distance <= radius)
		{
			result = Intersects;
		}
	}

	return result;
}

FrustumCullResult Frustum::CullTest(const AABB & aabb)
{
	FrustumCullResult result = Inside;

	Vector3 extents = aabb.GetExtents();
	Vector3 center = aabb.GetCenter();

	for (int i = 0; i < 6; i++)
	{
		Vector3 normal = planes[i].GetNormal();
		float effectiveRadius = Abs(normal.x)*extents.x + Abs(normal.y)*extents.y + Abs(normal.z)*extents.z;

		float distance = planes[i].Distance(center);

		if (distance <= -effectiveRadius)
		{
			return Outside;
		}
		if (distance <= effectiveRadius)
		{
			result = Intersects;
		}
	}

	return result;
}

FrustumCullResult Frustum::CullTest(const OBB & obb)
{
	FrustumCullResult result = Inside;

	for (int i = 0; i < 6; i++)
	{
		Vector3 normal = planes[i].GetNormal();
		float u = Abs(obb.localAxes[0] * normal)*obb.extents[0];
		float v = Abs(obb.localAxes[1] * normal)*obb.extents[1];
		float w = Abs(obb.localAxes[2] * normal)*obb.extents[2];
		float effectiveRadius = u + v + w;

		float distance = planes[i].Distance(obb.center);

		if (distance <= -effectiveRadius)
		{
			return Outside;
		}
		if (distance <= effectiveRadius)
		{
			result = Intersects;
		}
	}
	
	return result;
}

//TODO temporal coherency??