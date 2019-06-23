#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include<iostream>

Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){}

Vector4::Vector4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

Vector4::Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

Vector4::Vector4(const Vector4 & v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

Vector4::Vector4(const Vector3 & v, float inW) : x(v.x), y(v.y), z(v.z), w(inW) {}

Vector4::Vector4(float inX, const Vector3 & v): x(inX), y(v.x), z(v.y), w(v.z) {}

Vector4::Vector4(const Vector2 & v1, const Vector2 & v2): x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}

Vector4::Vector4(const Vector2 & v, float inZ, float inW): x(v.x), y(v.y), z(inZ), w(inW) {}

Vector4::Vector4(float inX, const Vector2 & v, float inW): x(inX), y(v.x), z(v.y), w(inW) {}

Vector4::Vector4(float inX, float inY, const Vector2 & v) : x(inX), y(inY), z(v.x), w(v.y) {}

Vector4 & Vector4::operator=(const Vector4 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

Vector4 & Vector4::operator=(const Vector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1.0f;
	return *this;
}

Vector4 & Vector4::operator=(float scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
	w = scalar;
	return *this;
}

float & Vector4::operator[](int n)
{
	Clamp<int>(n, 0, 3);

	if (n == 0) return x;
	else
	{
		if (n == 1) return y;
		else
		{
			if(n == 2) 
				return z;
			else 
				return w;
		}
	}
}

const float & Vector4::operator[](int n) const
{
	Clamp<int>(n, 0, 3);

	if (n == 0) return x;
	else
	{
		if (n == 1) return y;
		else
		{
			if (n == 2) 
				return z;
			else 
				return w;
		}
	}
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const Vector4 & v) const
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 & Vector4::operator+=(const Vector4 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4 & v) const
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 & Vector4::operator-=(const Vector4 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4 Vector4::operator*(const float scalar) const
{
	return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vector4 & Vector4::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4 Vector4::operator/(const float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

Vector4 & Vector4::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

bool Vector4::operator==(const Vector4 & v) const
{
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vector4::operator!=(const Vector4 & v) const
{
	return (x != v.x || y != v.y || z != v.z || w != v.w);
}

float Vector4::DotProduct(const Vector4 & v1, const Vector4 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w);
}

float Vector4::operator*(const Vector4 & v) const
{
	return (x*v.x + y*v.y + z*v.z + w*v.w);
}

Vector4 Vector4::CompMult(const Vector4 & v1, const Vector4 & v2)
{
	return Vector4(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z, v1.w*v2.w);
}

Vector4 Vector4::CompDiv(const Vector4 & v1, const Vector4 & v2)
{
	return Vector4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w/v2.w);
}

Vector4 Vector4::GetNormalized() const
{
	float length = GetLength();
	if (length != 0.0f)
	{
		return (*this / length);
	}
	else return Vector4();
}

float Vector4::GetLength() const
{
	return Sqrt(x*x + y*y + z*z + w*w);
}

float Vector4::GetLengthSquared() const
{
	return (x*x + y*y + z*z + w*w);
}


float Vector4::GetDistance(const Vector4 & v1, const Vector4 & v2)
{
	return (v2 - v1).GetLength();
}

float Vector4::GetDistanceSquared(const Vector4 & v1, const Vector4 & v2)
{
	return (v2 - v1).GetLengthSquared();
}

Vector2 Vector4::XY() const
{
	return Vector2(x, y);
}

Vector2 Vector4::YZ() const
{
	return Vector2(y, z);
}

Vector2 Vector4::ZW() const
{
	return Vector2(z, w);
}

Vector3 Vector4::XYZ() const
{
	return Vector3(x, y, z);
}

Vector3 Vector4::YZW() const
{
	return Vector3(y, z, w);
}

bool Vector4::IsUnit(float tolerance) const
{
	return Abs(GetLength() - 1.0f) < tolerance;
}

bool Vector4::NearlyEqual(const Vector4 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance && Abs(z - v.z) <= tolerance && Abs(w - v.w) <= tolerance);
}

bool Vector4::Orthogonal(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	float dotProd = DotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector4::Orthonormal(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	return (Orthogonal(v1, v2, tolerance) && v1.IsUnit(tolerance) && v2.IsUnit(tolerance));
}

bool Vector4::Parallel(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	float absDotProd = Abs(DotProduct(v1, v2));
	float lengthProd = v1.GetLength()*v2.GetLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector4 Vector4::ProjectOnTo(const Vector4 & v) const
{
	float length = v.GetLength();
	return Vector3(
		v * ((*this * v) / (length * length))
	);
}

void Vector4::Normalize()
{
	*this = this->GetNormalized();
}

void Vector4::Print() const
{
	std::cout << x << " " << y << " " << z << " " << w << " ";
}

Vector4::~Vector4()
{
}

//TODO Vector comparisons? Abs? -> use in NearlyEqual, Step, and Smoothstep functions