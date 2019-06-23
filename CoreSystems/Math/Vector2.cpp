#include "Vector2.h"
#include<iostream>

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float scalar) : x(scalar), y(scalar) {}

Vector2::Vector2(float inX, float inY) : x(inX), y(inY) {}

Vector2::Vector2(const Vector2 & v) : x(v.x), y(v.y) {}

Vector2& Vector2::operator=(const Vector2 & v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 & Vector2::operator=(float scalar)
{
	x = scalar;
	y = scalar;
	return *this;
}

float & Vector2::operator[](int n)
{
	Clamp<int>(n, 0, 1);

	if (n == 0) return x;
	else
	{
		return y;
	}
}

const float & Vector2::operator[](int n) const
{
	Clamp<int>(n, 0, 1);

	if (n == 0) return x;
	else
	{
		return y;
	}
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x,-y);
}

Vector2 Vector2::operator+(const Vector2 & v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 & Vector2::operator+=(const Vector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2 & v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 & Vector2::operator-=(const Vector2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 & Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2 & Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2 & v) const
{
	return (x == v.x && y == v.y);
}

bool Vector2::operator!=(const Vector2 & v) const
{
	return (x != v.x || y != v.y);
}

float Vector2::DotProduct(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

float Vector2::operator*(const Vector2 & v) const
{
	return (x*v.x + y * v.y);
}

Vector2 Vector2::CompMult(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x*v2.x, v1.y*v2.y);
}

Vector2 Vector2::CompDiv(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x / v2.x, v1.y / v2.y);
}

Vector2 Vector2::GetNormalized(const Vector2& v)
{
	float length = v.GetLength();
	if (length != 0.0f)
	{
		return (v / length);
	}
	else return Vector2();
}

float Vector2::GetLength() const
{
	return Sqrt(x*x + y*y);
}

float Vector2::GetLengthSquared() const
{
	return(x*x + y*y);
}


float Vector2::GetDistance(const Vector2 & v1, const Vector2 & v2)
{
	return (v2 - v1).GetLength();
}

float Vector2::GetDistanceSquared(const Vector2 & v1, const Vector2 & v2)
{
	return (v2 - v1).GetLengthSquared();
}

float Vector2::GetAngle(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 a = GetNormalized(v1);
	Vector2 b = GetNormalized(v2);

	return Acos(DotProduct(a, b));
}

bool Vector2::IsUnit(float tolerance) const
{
	return Abs(GetLength() - 1.0f) < tolerance;
}

bool Vector2::NearlyEqual(const Vector2 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance);
}

bool Vector2::Orthogonal(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	float dotProd = DotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector2::Orthonormal(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	return (Orthogonal(v1, v2, tolerance) && v1.IsUnit(tolerance) && v2.IsUnit(tolerance));
}

bool Vector2::Parallel(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	float absDotProd = Abs(DotProduct(v1, v2));
	float lengthProd = v1.GetLength()*v2.GetLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector2 Vector2::ProjectOnTo(const Vector2 & v) const
{
	float length = v.GetLength();
	return Vector2(
		v * ((*this * v) / (length * length))
	);
}

void Vector2::Normalize()
{
	*this = GetNormalized(*this);
}


void Vector2::Print() const
{
	std::cout << x << " " << y << " ";
}

Vector2::~Vector2()
{
}
