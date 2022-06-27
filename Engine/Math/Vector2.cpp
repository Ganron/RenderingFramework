#include "Vector2.h"
#include<iostream>
#include<assert.h>

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

float & Vector2::operator[](int n)
{
	assert(n == 0 || n == 1);

	if (n == 0) 
		return x;
	else
		return y;
}

const float & Vector2::operator[](int n) const
{
	assert(n == 0 || n == 1);

	if (n == 0)
		return x;
	else
		return y;
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

float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::dotProduct(const Vector2 & v1, const Vector2 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

float Vector2::operator*(const Vector2 & v) const
{
	return (x*v.x + y * v.y);
}

Vector2 Vector2::compMult(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::compDiv(const Vector2& v) const
{
	//Division by zero not allowed - raise assertion.
	assert(!(NearlyZero(v.x) || NearlyZero(v.y)));
	return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::getNormalized() const
{
	float length = getLength();
	//Raise assertion in case of zero vector.
	assert(!NearlyZero(length));
	return (*this / length);
}

float Vector2::getLength() const
{
	return Sqrt(x*x + y*y);
}

float Vector2::getLengthSquared() const
{
	return(x*x + y*y);
}

float Vector2::getDistanceTo(const Vector2& v) const
{
	return (v - *this).getLength();
}

float Vector2::getDistanceSquaredTo(const Vector2& v) const
{
	return (v - *this).getLengthSquared();
}

float Vector2::getAngleTo(const Vector2& v) const
{
	//By properties of the dot product:
	//	a dot b = len(a) * len(b) * cos(angle)
	//Ensuring normal vectors, we have:
	//	angle = acos(a dot b)

	Vector2 a = this->getNormalized();
	Vector2 b = v.getNormalized();

	return Acos(a.dot(b));
}

float Vector2::getAngleToUnit(const Vector2& v) const
{
	//In case of unit vectors, we can avoid calculating the length (eq to 1.0).
	return Acos(this->dot(v));
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
	//Here we use the squared length to gain performance.
	//The difference in the result is negligible, but to nevertheless account for the change,
	//we use double tolerance (encoded in the constant itself).
	return NearlyZero(getLengthSquared() - 1.0f, tolerance);
}

bool Vector2::isEqualTo(const Vector2 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance);
}

bool Vector2::isOrthogonalTo(const Vector2& v, float tolerance) const
{
	//The two vectors are orthogonal if their dot prouct is zero.
	//We perform the comparison with some tolerance to account for floating point error.
	float dotProd = this->dot(v);
	return NearlyZero(dotProd, tolerance);
}

bool Vector2::isOrthonormalTo(const Vector2& v, float tolerance)
{
	//Two vectors are orthonormal if they are orthogonal and they are both unit vectors.
	return (this->isOrthogonalTo(v, tolerance) && this->isUnit() && v.isUnit());
}

bool Vector2::isParallelTo(const Vector2& v, float tolerance)
{
	//Assuming the angle between the two vectors is 'alpha', then the two vectors are parallel when cos(alpha)=1.
	//Therefore, |a dot b| = len(a) * len (b)
	//We perform the comparison with some tolerance to account for floating point error.
	float absDotProd = Abs(this->dot(v));
	float lengthProd = this->getLength() * v.getLength();
	return NearlyZero(absDotProd - lengthProd, tolerance);
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

Vector2 Vector2::projectOnToUnit(const Vector2& v) const
{
	//Assuming unit length vectors, projection formula becomes:
	//proj_a_onto_b = proj_length * b = a.dot(b) * b
	return v * this->dot(v);
}

Vector2 Vector2::projectOnTo(const Vector2 & v) const
{
	//Projection formula:
	//proj_a_onto_b = proj_length * b_unit = a.dot(b) * b/len(b)

	float lengthSq = v.getLengthSquared();
	//In case of zero vector, an assertion is raised.
	//Note the use of the appropriate constant for comparison with length squared.
	assert(!NearlyZero(lengthSq, EPSILON_NEAR_ZERO_SQUARED));

	return v * (this->dot(v) / (lengthSq));
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

Vector2 operator*(const float scalar, const Vector2& v)
{
	return v*scalar;
}
