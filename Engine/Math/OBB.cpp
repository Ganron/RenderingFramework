#include"OBB.h"

OBB::OBB(): localAxes(Matrix3()),center(Vector3(0.0f)),extents(Vector3(0.5f))
{
}

OBB::OBB(const Vector3 & inCenter, const Vector3 & inExtents, const Matrix3 & inAxes): localAxes(inAxes),center(inCenter),extents(inExtents)
{
}

OBB::OBB(const OBB & inOBB):localAxes(inOBB.localAxes), center(inOBB.center), extents(inOBB.extents)
{
}

OBB & OBB::operator=(const OBB & obb)
{
	localAxes = obb.localAxes;
	center = obb.center;
	extents = obb.extents;
	return *this;
}

bool OBB::Contains(const Vector3 & point) const
{
	Vector3 centerToPoint = point - center;
	float uProjected = Abs(centerToPoint*localAxes[0]);
	float vProjected = Abs(centerToPoint*localAxes[1]);
	float wProjected = Abs(centerToPoint*localAxes[2]);
	return uProjected <= extents.x && vProjected <= extents.y && wProjected <= extents.z;
}

OBB OBB::Transform(const Matrix3 & rotation, const Vector3 & translation, const Vector3 scaleFactors) const
{
	return OBB(center+translation, extents.compMult(scaleFactors),localAxes*rotation);
}
