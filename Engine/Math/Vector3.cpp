#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include<iostream>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {}

Vector3::Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

Vector3::Vector3(const Vector2 & v, float inZ) : x(v.x), y(v.y), z(inZ) {}

Vector3::Vector3(float inX, const Vector2 & v) : x(inX), y(v.x), z(v.y) {}

Vector3::Vector3(const Vector3 & v) : x(v.x), y(v.y), z(v.z) {}

Vector3::Vector3(const Vector4 & v) : x(v.x), y(v.y), z(v.z) {}

Vector3 & Vector3::operator=(const Vector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3 & Vector3::operator=(const Vector4 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3 & Vector3::operator=(float scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
	return *this;
}

float& Vector3::operator[](int n)
{
	Clamp<int>(n, 0, 2);

	if (n == 0) return x;
	else
	{
		if (n == 1) return y;
		else
		{
			return z;
		}
	}
}

const float & Vector3::operator[](int n) const
{
	Clamp<int>(n, 0, 2);

	if (n == 0) return x;
	else
	{
		if (n == 1) return y;
		else
		{
			return z;
		}
	}
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3 & v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 & Vector3::operator+=(const Vector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3 & v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 & Vector3::operator-=(const Vector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 & Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 & Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

bool Vector3::operator==(const Vector3 & v) const
{
	return (x==v.x && y==v.y && z==v.z);
}

bool Vector3::operator!=(const Vector3 & v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

float Vector3::DotProduct(const Vector3 & v1, const Vector3 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

float Vector3::operator*(const Vector3 & v) const
{
	return (x*v.x + y*v.y + z*v.z);
}

Vector3 Vector3::CrossProduct(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}

Vector3 Vector3::CompMult(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
}

Vector3 Vector3::CompDiv(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1.x/v2.x, v1.y/v2.y, v1.z/v2.z);
}

Vector3 Vector3::GetNormalized() const
{
	float length = GetLength();
	if (!NearlyEqual(length,0.0f))
	{
		return (*this / length);
	}
	else return Vector3();
}

float Vector3::GetLength() const
{
	return Sqrt(x*x + y*y + z*z);
}

float Vector3::GetLengthSquared() const
{
	return (x*x + y*y + z*z);
}


float Vector3::GetDistance(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).GetLength();
}

float Vector3::GetDistanceSquared(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).GetLengthSquared();
}

float Vector3::GetAngle(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 a = v1.GetNormalized();
	Vector3 b = v2.GetNormalized();

	return Acos(DotProduct(a, b));

}

Vector2 Vector3::XY()
{
	return Vector2(x, y);
}

Vector2 Vector3::YZ()
{
	return Vector2(y, z);
}

bool Vector3::IsUnit(float tolerance) const
{
	return Abs(GetLength() - 1.0f) < tolerance;
}

bool Vector3::NearlyEqual(const Vector3 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance && Abs(z - v.z) <= tolerance);
}

bool Vector3::Orthogonal(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	float dotProd = DotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector3::Orthonormal(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	return (Orthogonal(v1, v2, tolerance) && v1.IsUnit(tolerance) && v2.IsUnit(tolerance));
}

bool Vector3::Parallel(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	float absDotProd = Abs(DotProduct(v1, v2));
	float lengthProd = v1.GetLength()*v2.GetLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector3 Vector3::ProjectOnToUnit(const Vector3 & v) const
{
	return v * (*this * v);
}

Vector3 Vector3::ProjectOnTo(const Vector3 & v) const
{
	float length = v.GetLength();
	return v * ((*this * v) / (length * length));
}

Vector3 Vector3::Reflect(const Vector3 & light, const Vector3 & normal)
{
	return Vector3(
		light - (light - light.ProjectOnTo(normal)) * 2
	);
}

Vector3 Vector3::Refract(const Vector3 & light, const Vector3 & normal, float etaLeaving, float etaEntering)
{
	Vector3 l = light.GetNormalized();
	Vector3 n = normal.GetNormalized();

	float eta = etaLeaving / etaEntering;
	float cos = DotProduct(l, n);
	float k = 1 - eta * eta * (1 - cos * cos);

	if (k < 0.0f)
	{
		return Vector3(0.0f);
	}
	else
	{
		return Vector3(
			n * (eta*cos - Sqrt(k)) - l * eta
		);
	}
}

void Vector3::Normalize()
{
	*this = this->GetNormalized();
}

void Vector3::Print() const
{
	std::cout << x << " " << y << " " << z << " ";
}

Vector3::~Vector3()
{
}
