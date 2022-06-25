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

float Vector2::dotProduct(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

float Vector2::operator*(const Vector2 & v) const
{
	return (x*v.x + y * v.y);
}

Vector2 Vector2::compMult(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x*v2.x, v1.y*v2.y);
}

Vector2 Vector2::compDiv(const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1.x / v2.x, v1.y / v2.y);
}

Vector2 Vector2::getNormalized() const
{
	float length = getLength();
	if (length != 0.0f)
	{
		return (*this / length);
	}
	else return Vector2();
}

float Vector2::getLength() const
{
	return Sqrt(x*x + y*y);
}

float Vector2::getLengthSquared() const
{
	return(x*x + y*y);
}


float Vector2::getDistance(const Vector2 & v1, const Vector2 & v2)
{
	return (v2 - v1).getLength();
}

float Vector2::getDistanceSquared(const Vector2 & v1, const Vector2 & v2)
{
	return (v2 - v1).getLengthSquared();
}

float Vector2::getAngle(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 a = v1.getNormalized();
	Vector2 b = v2.getNormalized();

	return Acos(dotProduct(a, b));
}

bool Vector2::isUnit(float tolerance) const
{
	return Abs(getLength() - 1.0f) < tolerance;
}

bool Vector2::isEqualTo(const Vector2 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance);
}

bool Vector2::orthogonal(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	float dotProd = dotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector2::orthonormal(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	return (orthogonal(v1, v2, tolerance) && v1.isUnit(tolerance) && v2.isUnit(tolerance));
}

bool Vector2::parallel(const Vector2 & v1, const Vector2 & v2, float tolerance)
{
	float absDotProd = Abs(dotProduct(v1, v2));
	float lengthProd = v1.getLength()*v2.getLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector2 Vector2::projectOnTo(const Vector2 & v) const
{
	float length = v.getLength();
	return Vector2(
		v * ((*this * v) / (length * length))
	);
}

void Vector2::normalize()
{
	*this = this->getNormalized();
}


void Vector2::print() const
{
	std::cout << x << " " << y << " ";
}

Vector2::~Vector2()
{
}
