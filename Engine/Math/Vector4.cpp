#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include<iostream>
#include<assert.h>

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

float & Vector4::operator[](int n)
{
	assert(n >= 0 && n <= 2);

	if (n == 0)
		return x;
	else if (n == 1)
		return y;
	else if (n == 2)
		return z;
	else
		return w;
}

const float & Vector4::operator[](int n) const
{
	assert(n >= 0 && n <= 2);

	if (n == 0)
		return x;
	else if (n == 1)
		return y;
	else if (n == 2)
		return z;
	else
		return w;
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

float Vector4::dot(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

float Vector4::dotProduct(const Vector4 & v1, const Vector4 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w);
}

float Vector4::operator*(const Vector4 & v) const
{
	return (x*v.x + y*v.y + z*v.z + w*v.w);
}

Vector4 Vector4::compMult(const Vector4& v)
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vector4 Vector4::compDiv(const Vector4& v)
{
	//Division by zero not allowed - raise assertion.
	assert(!(NearlyZero(v.x) || NearlyZero(v.y) || NearlyZero(v.z) || NearlyZero(v.w)));
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4 Vector4::getNormalized() const
{
	float length = getLength();
	//Raise assertion in case of zero vector.
	assert(!NearlyZero(length));
	return (*this / length);
}

float Vector4::getLength() const
{
	return Sqrt(x*x + y*y + z*z + w*w);
}

float Vector4::getLengthSquared() const
{
	return (x*x + y*y + z*z + w*w);
}

float Vector4::getDistanceTo(const Vector4& v) const
{
	return (v - *this).getLength();
}

float Vector4::getDistanceSquaredTo(const Vector4& v) const
{
	return (v - *this).getLengthSquared();
}

float Vector4::getAngleTo(const Vector4& v) const
{
	//By properties of the dot product:
	//	a dot b = len(a) * len(b) * cos(angle)
	//Ensuring normal vectors, we have:
	//	angle = acos(a dot b)

	Vector3 a = this->getNormalized();
	Vector3 b = v.getNormalized();

	return Acos(a.dot(b));
}

float Vector4::getAngleToUnit(const Vector4& v) const
{
	//In case of unit vectors, we can avoid calculating the length (= to 1.0).
	return Acos(this->dot(v));
}


float Vector4::getDistance(const Vector4 & v1, const Vector4 & v2)
{
	return (v2 - v1).getLength();
}

float Vector4::getDistanceSquared(const Vector4 & v1, const Vector4 & v2)
{
	return (v2 - v1).getLengthSquared();
}

Vector2 Vector4::xy() const
{
	return Vector2(x, y);
}

Vector2 Vector4::yz() const
{
	return Vector2(y, z);
}

Vector2 Vector4::zw() const
{
	return Vector2(z, w);
}

Vector3 Vector4::xyz() const
{
	return Vector3(x, y, z);
}

Vector3 Vector4::yzw() const
{
	return Vector3(y, z, w);
}

bool Vector4::isUnit(float tolerance) const
{
	//Here we use the squared length to gain performance.
	//The difference in the result is negligible, but to nevertheless account for the change,
	//we use double tolerance (encoded in the constant itself).
	return NearlyZero(getLengthSquared() - 1.0f, tolerance);
}

bool Vector4::isEqualTo(const Vector4 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance && Abs(z - v.z) <= tolerance && Abs(w - v.w) <= tolerance);
}

bool Vector4::isOrthogonalTo(const Vector4& v, float tolerance) const
{
	//The two vectors are orthogonal if their dot prouct is zero.
	//We perform the comparison with some tolerance to account for floating point error.
	float dotProd = this->dot(v);
	return NearlyZero(dotProd, tolerance);
}

bool Vector4::isOrthonormalTo(const Vector4& v, float tolerance)
{
	//Two vectors are orthonormal if they are orthogonal and they are both unit vectors.
	return (this->isOrthogonalTo(v, tolerance) && this->isUnit() && v.isUnit());
}

bool Vector4::isParallelTo(const Vector4& v, float tolerance)
{
	//Assuming the angle between the two vectors is 'alpha', then the two vectors are parallel when cos(alpha)=1.
	//Therefore, |a dot b| = len(a) * len (b)
	//We perform the comparison with some tolerance to account for floating point error.
	float absDotProd = Abs(this->dot(v));
	float lengthProd = this->getLength() * v.getLength();
	return NearlyZero(absDotProd - lengthProd, tolerance);
}

bool Vector4::orthogonal(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	float dotProd = dotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector4::orthonormal(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	return (orthogonal(v1, v2, tolerance) && v1.isUnit(tolerance) && v2.isUnit(tolerance));
}

bool Vector4::parallel(const Vector4 & v1, const Vector4 & v2, float tolerance)
{
	float absDotProd = Abs(dotProduct(v1, v2));
	float lengthProd = v1.getLength()*v2.getLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector4 Vector4::projectOnToUnit(const Vector4& v) const
{
	//Assuming unit length vectors, projection formula becomes:
	//proj_a_onto_b = proj_length * b = a.dot(b) * b
	return v * this->dot(v);
}

Vector4 Vector4::projectOnTo(const Vector4 & v) const
{
	//Projection formula:
	//proj_a_onto_b = proj_length * b_unit = a.dot(b) * b/len(b)

	float lengthSq = v.getLengthSquared();
	//In case of zero vector, an assertion is raised.
	//Note the use of the appropriate constant for comparison with length squared.
	assert(!NearlyZero(lengthSq, EPSILON_NEAR_ZERO_SQUARED));

	return v * (this->dot(v) / (lengthSq));
}

void Vector4::normalize()
{
	*this = this->getNormalized();
}

void Vector4::print() const
{
	std::cout << x << " " << y << " " << z << " " << w << " ";
}

Vector4::~Vector4()
{
}

Vector4 operator*(const float scalar, const Vector4& v)
{
	return v * scalar;
}
