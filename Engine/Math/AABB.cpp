#include"AABB.h"
#include"Math.h"
#include"Matrix3.h"

AABB::AABB() : min(-0.5f, -0.5f, -0.5f), max(0.5f, 0.5f, 0.5f)
{
}

AABB::AABB(const Vector3 & inMin, const Vector3 & inMax) : min(inMin), max(inMax)
{
}

AABB::AABB(const AABB & inAABB) : min(inAABB.min), max(inAABB.max)
{
}

AABB & AABB::operator=(const AABB & aabb)
{
	min = aabb.min;
	max = aabb.max;
	return *this;
}

Vector3 AABB::GetCenter() const
{
	return (min + max)*0.5f;
}

Vector3 AABB::GetSize() const
{
	return max - min;
}

Vector3 AABB::GetExtents() const
{
	return (max - min)*0.5f;
}

bool AABB::Contains(const Vector3 & point) const
{
	return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
}

bool AABB::Contains(const AABB & aabb) const
{
	return aabb.min.x >= min.x && aabb.max.x <= max.x
		&& aabb.min.y >= min.y && aabb.max.y <= max.y
		&& aabb.min.z >= min.z && aabb.max.z <= max.z;
}

float AABB::Distance(const Vector3 & point) const
{
	return Sqrt(DistanceSquared(point));
}

float AABB::DistanceSquared(const Vector3 & point) const
{
	float x = Max<float>(min.x - point.x, 0.0f, point.x - max.x);
	float y = Max<float>(min.y - point.y, 0.0f, point.y - max.y);
	float z = Max<float>(min.z - point.z, 0.0f, point.z - max.z);
	return x*x + y*y + z*z;
}

void AABB::Expand(const Vector3 & point)
{
	if (min.NearlyEqual(Vector3(0.0f)) && max.NearlyEqual(Vector3(0.0f)))
	{
		min = max = point;
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		min[i] = Min<float>(min[i], point[i]);
		max[i] = Max<float>(max[i], point[i]);
	}
	return;
}

void AABB::Expand(const AABB & aabb)
{
	if (aabb.min.NearlyEqual(Vector3(0.0f)) && aabb.max.NearlyEqual(Vector3(0.0f)))
	{
		return;
	}
	if (min.NearlyEqual(Vector3(0.0f)) && max.NearlyEqual(Vector3(0.0f)))
	{
		min = aabb.min;
		max = aabb.max;
		return;
	}
	for (int i = 0; i < 3; i++)
	{
		min[i] = Min<float>(min[i], aabb.min[i]);
		max[i] = Max<float>(max[i], aabb.max[i]);
	}
}

AABB AABB::Transform(const Matrix3 & rotation, const Vector3 & translation) const
{
	AABB newAABB(translation, translation);
	float a, b;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a = rotation[i][j] * min[i];
			b = rotation[i][j] * max[i];
			if (a < b)
			{
				newAABB.min[j] += a;
				newAABB.max[j] += b;
			}
			else
			{
				newAABB.min[j] += b;
				newAABB.max[j] += a;
			}
		}
	}
	return newAABB;
}

AABB::~AABB()
{
}
