#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include<iostream>
#include<assert.h>

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

float& Vector3::operator[](int n)
{
	assert(n >= 0 && n <= 2);

	if (n == 0) 
		return x;
	else if (n == 1) 
		return y;
	else
		return z;
}

const float & Vector3::operator[](int n) const
{
	assert(n >= 0 && n <= 2);

	if (n == 0)
		return x;
	else if (n == 1)
		return y;
	else
		return z;
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

float Vector3::dot(const Vector3& v) const
{
	return x*v.x + y*v.y + z*v.z;
}

float Vector3::dotProduct(const Vector3 & v1, const Vector3 & v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

float Vector3::operator*(const Vector3 & v) const
{
	return (x*v.x + y*v.y + z*v.z);
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

Vector3 Vector3::crossProduct(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}

Vector3 Vector3::compMult(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::compDiv(const Vector3& v) const
{
	//Division by zero not allowed - raise assertion.
	assert(!(NearlyZero(v.x) || NearlyZero(v.y) || NearlyZero(v.z)));
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::getNormalized() const
{
	float length = getLength();
	//Raise assertion in case of zero vector.
	assert(!NearlyZero(length));
	return (*this / length);
}

float Vector3::getLength() const
{
	return Sqrt(x*x + y*y + z*z);
}

float Vector3::getLengthSquared() const
{
	return (x*x + y*y + z*z);
}

float Vector3::getDistanceTo(const Vector3& v) const
{
	return (v - *this).getLength();
}

float Vector3::getDistanceSquaredTo(const Vector3& v) const
{
	return (v - *this).getLengthSquared();
}

float Vector3::getAngleTo(const Vector3& v) const
{
	//By properties of the dot product:
  //	a dot b = len(a) * len(b) * cos(angle)
  //Ensuring normal vectors, we have:
  //	angle = acos(a dot b)

	Vector3 a = this->getNormalized();
	Vector3 b = v.getNormalized();

	return Acos(a.dot(b));
}

float Vector3::getAngleToUnit(const Vector3& v) const
{
	//In case of unit vectors, we can avoid calculating the length (eq to 1.0).
	return Acos(this->dot(v));
}


float Vector3::getDistance(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).getLength();
}

float Vector3::getDistanceSquared(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).getLengthSquared();
}

float Vector3::getAngle(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 a = v1.getNormalized();
	Vector3 b = v2.getNormalized();

	return Acos(dotProduct(a, b));

}

Vector2 Vector3::xy()
{
	return Vector2(x, y);
}

Vector2 Vector3::yz()
{
	return Vector2(y, z);
}

bool Vector3::isUnit(float tolerance) const
{
	//Here we use the squared length to gain performance.
	//The difference in the result is negligible, but to nevertheless account for the change,
	//we use double tolerance (encoded in the constant itself).
	return NearlyZero(getLengthSquared() - 1.0f, tolerance);
}

bool Vector3::isEqualTo(const Vector3 & v, float tolerance) const
{
	return (Abs(x - v.x) <= tolerance && Abs(y - v.y) <= tolerance && Abs(z - v.z) <= tolerance);
}

bool Vector3::isOrthogonalTo(const Vector3& v, float tolerance) const
{
	//The two vectors are orthogonal if their dot prouct is zero.
	//We perform the comparison with some tolerance to account for floating point error.
	float dotProd = this->dot(v);
	return NearlyZero(dotProd, tolerance);
}

bool Vector3::isOrthonormalTo(const Vector3& v, float tolerance)
{
	//Two vectors are orthonormal if they are orthogonal and they are both unit vectors.
	return (this->isOrthogonalTo(v, tolerance) && this->isUnit() && v.isUnit());
}

bool Vector3::isParallelTo(const Vector3& v, float tolerance)
{
	//Assuming the angle between the two vectors is 'alpha', then the two vectors are parallel when cos(alpha)=1.
	//Therefore, |a dot b| = len(a) * len (b)
	//We perform the comparison with some tolerance to account for floating point error.
	float absDotProd = Abs(this->dot(v));
	float lengthProd = this->getLength() * v.getLength();
	return NearlyZero(absDotProd - lengthProd, tolerance);
}

bool Vector3::orthogonal(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	float dotProd = dotProduct(v1, v2);
	return (Abs(dotProd) < tolerance);
}

bool Vector3::orthonormal(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	return (orthogonal(v1, v2, tolerance) && v1.isUnit(tolerance) && v2.isUnit(tolerance));
}

bool Vector3::parallel(const Vector3 & v1, const Vector3 & v2, float tolerance)
{
	float absDotProd = Abs(dotProduct(v1, v2));
	float lengthProd = v1.getLength()*v2.getLength();
	return (Abs(absDotProd - lengthProd) < tolerance);
}

Vector3 Vector3::projectOnToUnit(const Vector3 & v) const
{
	//Assuming unit length vectors, projection formula becomes:
	//proj_a_onto_b = proj_length * b = a.dot(b) * b
	return v * this->dot(v);
}

Vector3 Vector3::projectOnTo(const Vector3 & v) const
{
	//Projection formula:
  //proj_a_onto_b = proj_length * b_unit = a.dot(b) * b/len(b)

	float lengthSq = v.getLengthSquared();
	//In case of zero vector, an assertion is raised.
	//Note the use of the appropriate constant for comparison with length squared.
	assert(!NearlyZero(lengthSq,EPSILON_NEAR_ZERO_SQUARED));

	return v * (this->dot(v) / (lengthSq));
}

Vector3 Vector3::reflect(const Vector3 & light, const Vector3 & normal)
{
	return Vector3(
		light - (light - light.projectOnTo(normal)) * 2
	);
}

Vector3 Vector3::refract(const Vector3 & light, const Vector3 & normal, float etaLeaving, float etaEntering)
{
	Vector3 l = light.getNormalized();
	Vector3 n = normal.getNormalized();

	float eta = etaLeaving / etaEntering;
	float cos = dotProduct(l, n);
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

void Vector3::normalize()
{
	*this = this->getNormalized();
}

void Vector3::print() const
{
	std::cout << x << " " << y << " " << z << " ";
}

Vector3::~Vector3()
{
}

Vector3 operator*(const float scalar, const Vector3& v)
{
	return v*scalar;
}
