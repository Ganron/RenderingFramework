#include"Quaternion.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix3.h"


Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(const Quaternion & q) : w(q.w), x(q.x), y(q.y), z(q.z) {}

Quaternion::Quaternion(float inW, float inX, float inY, float inZ) : w(inW), x(inX), y(inY), z(inZ) {}

Quaternion::Quaternion(float scalar, const Vector3 & vector) : w(scalar), x(vector.x), y(vector.y), z(vector.z) {}

Quaternion::Quaternion(float scalar) : w(scalar), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(const Vector3 & vector) : w(0.0f), x(vector.x), y(vector.y), z(vector.z) {}

Quaternion::Quaternion(const Vector4 & v): w(v.x), x(v.y), y(v.z), z(v.w) {}

Quaternion & Quaternion::operator=(const Quaternion & q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-w, -x, -y, -z);
}

Quaternion Quaternion::operator+(const Quaternion & q) const
{
	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion & Quaternion::operator+=(const Quaternion & q)
{
	return *this = (*this + q);
}

Quaternion Quaternion::operator-(const Quaternion & q) const
{
	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

Quaternion & Quaternion::operator-=(const Quaternion & q)
{
	return *this = (*this - q);
}

Quaternion Quaternion::operator*(float scalar) const
{
	return Quaternion(w*scalar, x*scalar, y*scalar, z*scalar);
}

Quaternion & Quaternion::operator*=(float scalar)
{
	return *this = (*this * scalar);
}

Quaternion Quaternion::operator/(float scalar) const
{
	return Quaternion(w/scalar, x/scalar, y/scalar, z/scalar);
}

Quaternion & Quaternion::operator/=(float scalar)
{
	return *this = (*this / scalar);
}

Quaternion Quaternion::operator*(const Quaternion & q) const
{
	return Quaternion(
		w*q.w - x*q.x - y*q.y - z*q.z,
		w*q.x + q.w*x + y*q.z - z*q.y,
		w*q.y + q.w*y + z*q.x - x*q.z,
		w*q.z + q.w*z + x*q.y - y*q.x
	);
}

Quaternion & Quaternion::operator*=(const Quaternion & q)
{
	return *this = (*this * q);
}

bool Quaternion::operator==(const Quaternion & q) const
{
	return (w == q.w && x == q.x && y == q.y && z == q.z);
}

bool Quaternion::operator!=(const Quaternion & q) const
{
	return !(*this == q);
}

float Quaternion::DotProduct(const Quaternion & q1, const Quaternion & q2)
{
	return q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
}

Quaternion Quaternion::GetInverse() const
{
	return GetConjugate()/GetNormSquared();
}

Quaternion Quaternion::GetConjugate() const
{
	return Quaternion(w, -x, -y, -z);
}

float Quaternion::GetNorm() const
{
	return Sqrt(w * w + x * x + y * y + z * z);
}

float Quaternion::GetNormSquared() const
{
	return w * w + x * x + y * y + z * z;
}

Quaternion Quaternion::GetNormalized() const
{
	return *this/GetNorm();
}

//TODO Assert -1<w<1 ?
float Quaternion::GetRotationAngle() const
{
	return Acos(w) * 2;
}

//TODO Assert(1-w*w > 0)
Vector3 Quaternion::GetRotationAxis() const
{
	float sinSquared = 1 - w * w;
	if (sinSquared < EPSILON_NEAR_ZERO_SQUARED)
	{
		return Vector3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		float invSin = 1 / Sqrt(sinSquared);
		return Vector3(x*invSin, y*invSin, z*invSin);
	}
}

bool Quaternion::IsUnit(float tolerance) const
{
	return Abs(GetNorm() - 1.0f) < tolerance;
}

bool Quaternion::NearlyEqual(const Quaternion & q, float tolerance) const
{
	return Abs(w-q.w)<tolerance && Abs(x - q.x) < tolerance && Abs(y - q.y) < tolerance && Abs(z - q.z) < tolerance;
}

Quaternion Quaternion::CreateFromTwoVectors(const Vector3 & v1, const Vector3 & v2)
{
	float scalarPart = Vector3::DotProduct(v1, v2);
	Vector3 vectorPart;
	if (Abs(scalarPart) < EPSILON_NEAR_ZERO)
	{
		scalarPart = 0.0f;
		vectorPart = Abs(v1.x) > Abs(v1.z) ? Vector3(-v1.y, v1.x, 0.0f) : Vector3(0.0f, -v1.z, v1.y);
	}
	else
		vectorPart = Vector3::CrossProduct(v1, v2);
	return Quaternion(scalarPart,vectorPart).GetNormalized();
}

Quaternion Quaternion::CreateAxisAngle(float angle, const Vector3 & axis)
{
	angle *= 0.5f;
	float s = Sin(angle);
	return Quaternion(Cos(angle), axis*s);
}

Quaternion Quaternion::CreateFromMatrix(const Matrix3 & m)
{
	Quaternion result;

	float trace = m[0][0] + m[1][1] + m[2][2];
	if (trace > 0)
	{
		float K = 0.5f / Sqrt(trace + 1.0f); // 1/4W
		result.w = 0.25f / K;
		result.x = (m[1][2] - m[2][1])*K;
		result.y = (m[2][0] - m[0][2])*K;
		result.z = (m[0][1] - m[1][0])*K;
	}
	else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
	{
		float K = 0.5f / Sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]); // 1/4X
		result.x = 0.25f / K;
		result.w = (m[1][2] - m[2][1])*K;
		result.y = (m[1][0] + m[0][1])*K;
		result.z = (m[2][0] + m[0][2])*K;
	}
	else if (m[1][1] > m[2][2])
	{
		float K = 0.5f / Sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]); // 1/4Y
		result.y = 0.25f / K;
		result.w = (m[2][0] - m[0][2])*K;
		result.x = (m[1][0] + m[0][1])*K;
		result.z = (m[2][1] + m[1][2])*K;
	}
	else
	{
		float K = 0.5f / Sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]); // 1/4Z
		result.z = 0.25f / K;
		result.w = (m[0][1] - m[1][0])*K;
		result.x = (m[2][0] + m[0][2])*K;
		result.y = (m[2][1] + m[1][2])*K;
	}

	return result;
}


float Quaternion::AngularDistance(const Quaternion & q) const
{
	return Acos(Abs(DotProduct(q,*this)));
}

Quaternion Quaternion::Lerp(const Quaternion & q1, const Quaternion & q2, float T, bool shortestPath)
{
	Quaternion result;
	float dot = DotProduct(q1, q2);
	if (dot<0.0f && shortestPath)
	{
		result = q1 * (1 - T) - q2 * T;
	}
	else
	{
		result = q1 * (1 + T) - q2 * T;
	}
	return result.GetNormalized();
}

Quaternion Quaternion::Slerp(const Quaternion & q1, const Quaternion & q2, float T, bool shortestPath)
{
	float dot = DotProduct(q1, q2);
	if (Abs(dot) > 1 - EPSILON_QUAT_SLERP_TO_LERP)
	{
		return Lerp(q1, q2, T, shortestPath);
	}
	else
	{
		Quaternion newQ2;
		if (dot < 0.0f && shortestPath)
		{
			newQ2 = -q2;
			dot = -dot;
		}
		else
		{
			newQ2 = q2;
		}

		float angle = Acos(dot);
		float invSin = 1 / Sqrt(1 - dot * dot);
		return (q1*Sin(angle*(1 - T)) + q2 * Sin(angle*T))*invSin;
	}
}

Vector3 Quaternion::RotateVector(const Vector3 & v) const
{
	Vector3 xyz(x, y, z);
	Vector3 t = Vector3::CrossProduct(xyz, v) * 2;
	return v + t * w + Vector3::CrossProduct(xyz, t);
}

void Quaternion::Normalize()
{
	*this = this->GetNormalized();
}

Quaternion::~Quaternion()
{

}
