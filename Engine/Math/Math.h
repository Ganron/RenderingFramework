#pragma once

class Vector2;
class Vector3;
class Vector4;

//TODO Change namespace?

/* CONSTANTS */

//Math constants
const float PI = 3.14159265359f;
const float TO_DEG_CONST = 57.2957795131f;
const float TO_RAD_CONST = 0.01745329251f;

//tolerance constants
const float EPSILON_EQUAL = 0.0000001f;
//TODO remove vector-specific epsilon constants
const float EPSILON_VECTOR_UNIT = 0.0000002f; //set to 2*eps_equal to account for the length squared in isUnit()
const float EPSILON_VECTOR_ORTHOGONAL = 0.0000001f;
const float EPSILON_VECTOR_ORTHONORMAL = 0.0000001f;
const float EPSILON_VECTOR_PARALLEL = 0.0000001f;
const float EPSILON_NEAR_ZERO_SQUARED = 0.0000002f; //set to 2*eps_new_zero to account for the length squared
const float EPSILON_NEAR_ZERO = 0.0000001f;
const float EPSILON_QUAT_SLERP_TO_LERP = 0.1f;


/* TRIGONOMETRIC FUNCTIONS */

//Angle must be in radians.
float Sin(float angle);

//Angle must be in radians.
float Cos(float angle);

//Angle must be in radians.
float Tan(float angle);

float Asin(float x);

float Acos(float x);

float Atan(float x);

float Atan2(float y, float x);


/* EXPONENTIAL FUNCTIONS */

float Exp(float x);
float Pow(float a, float x);
float Pow2(float x);


/* LOGARITHMIC FUNCTIONS */

float Log2(float x);
float Log10(float x);
float LogE(float x);
float LogX(float base, float x);


/* OTHER FUNCTIONS */

//Get the absolute value of the number.
float Abs(float x);

//Get the absolute value of the number/s.
template <class T>
T Abs(T x);

//Find the smallest integral n, such that n>=x.
float Ceil(float x);

//Find the smallest integral n, such that n>=x.
int CeilToInt(float x);

//Clamp x between the min and max values.
template<class T>
T Clamp(T x, T min, T max);

//Find the greatest integral n, such that n<=x.
float Floor(float x);

//Find the greatest integral n, such that n<=x.
int FloorToInt(float x);

//Get the fractional component of the number.
float Fractional(float x);

//Get the integral component of the number.
float Integral(float x);

//Compute the greatest common divisor of a and b.
int GCD(int a, int b);

//Compute the least common multiplier of a and b.
int LCM(int a, int b);

//Find the greater of the two values.
template<class T>
T Max(T a, T b);

//Find the greatest of the three values.
template<class T>
T Max(T a, T b, T c);

//Find the smaller of the two values.
template<class T>
T Min(T a, T b);

//Find the smallest of the three values.
template<class T>
T Min(T a, T b, T c);

//Compare the two numbers within a given tolerance.
bool isEqualTo(float a, float b, float tolerance=EPSILON_EQUAL);

//Check whether a number is close to zero (within a given tolerance).
bool NearlyZero(float a, float tolerance=EPSILON_NEAR_ZERO);

//Round x to the nearest integer. Halfway cases are round away from zero.
float Round(float x);

//Round x to the nearest integer. Halfway cases are round away from zero.
int RoundToInt(float x);

//Returns 1 if x is positive, -1 if x is negative and 0 if x equals 0.
template<class T>
T Sign(T x);

//Compute the square root of x.
float Sqrt(float x);


/* CONVERSIONS */

//Convert an angle from degrees to radians.
float DegToRad(float angle);

//Convert an angle from radians to degrees.
float RadToDeg(float angle);

/*
 Convert 3D cartesian coordinates <x,y,z> to spherical coordinates <r,theta,phi>. 
 Theta (-PI <= Theta <= PI) is the azimuthal angle(in radians).
 Phi (0 <= Phi <= PI) is the polar angle(in radians). 
*/
void CartToSpherical(const Vector3& cartesian, Vector3& spherical);

/*
 Convert spherical coordinates <r,theta,phi> to 3D cartesian coordinates <x,y,z>.
 Theta (-PI <= Theta <= PI) is the azimuthal angle(in radians).
 Phi (0 <= Phi <= PI) is the polar angle(in radians).
*/
void SphericalToCart(const Vector3& spherical, Vector3& cartesian);


/* INTERPOLATION, SMOOTHING AND CURVES */

template<class T>
T Lerp(T& x, T& y, float t);

template<class T>
T BiLerp(T& x1, T& x2, T& y1, T& y2, float t1, float t2);

template<class T>
T QuadraticBezier(T a, T b, T c, float t);

template<class T>
T CubicBezier(T a, T b, T c, T d, float t);

//A step function that returns 0.0 if x<edge and 1.0 otherwise.
float Step(float x, float edge);

/*
 A step function that returns 0.0 if x[i]<edge[i] and 1.0 otherwise.
 Operates componentwise.
*/
Vector2 Step(Vector2& x, Vector2& edge);

/*
 A step function that returns 0.0 if x[i]<edge[i] and 1.0 otherwise.
 Operates componentwise.
*/
Vector3 Step(Vector3& x, Vector3& edge);

/*
 A step function that returns 0.0 if x[i]<edge[i] and 1.0 otherwise.
 Operates componentwise.
*/
Vector4 Step(Vector4& x, Vector4& edge);

//Perform Hermite interpolation between 0.0 and 1.0 when edge0 < x < edge1.
float Smoothstep(float edge0, float edge1, float x);

/*
 Perform Hermite interpolation between 0.0 and 1.0 when edge0[i] < x[i] < edge1[i].
 Operates componentwise.
*/
Vector2 Smoothstep(Vector2& edge0, Vector2& edge1, Vector2& x);

/*
 Perform Hermite interpolation between 0.0 and 1.0 when edge0[i] < x[i] < edge1[i].
 Operates componentwise.
*/
Vector3 Smoothstep(Vector3& edge0, Vector3& edge1, Vector3& x);

/*
 Perform Hermite interpolation between 0.0 and 1.0 when edge0[i] < x[i] < edge1[i].
 Operates componentwise.
*/
Vector4 Smoothstep(Vector4& edge0, Vector4& edge1, Vector4& x);


/* TEMPLATE IMPLEMENTATIONS */

template<class T>
inline T Abs(T x)
{
	if (x >= (T)x)
		return x;
	else
		return -x;
}

template<class T>
inline T Clamp(T x, T min, T max)
{
	return Max(min, Min(x, max));
}

template<class T>
inline T Max(T a, T b)
{
	if (a >= b)
		return a;
	else
		return b;
}

template<class T>
inline T Max(T a, T b, T c)
{
	return Max(a, Max(b, c));
}

template<class T>
inline T Min(T a, T b)
{
	if (a <= b)
		return a;
	else
		return b;
}

template<class T>
inline T Min(T a, T b, T c)
{
	return Min(a, Min(b, c));
}


template<class T>
inline T Sign(T x)
{
	return (T)((x>(T)0) - (x<(T)0));
}

/*
 Perform linear interpolation between two values. 
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T Lerp(T& x, T& y, float t)
{
	return (T)(x*(1 - t) + y * t);
}

/*
 Perform bilinear interpolation between four values.
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T BiLerp(T& x1, T& x2, T& y1, T& y2, float t1, float t2)
{
	T x = Lerp<T>(x1,x2,t1);
	T y = Lerp<T>(y1, y2, t1);
	return Lerp<T>(x, y, t2);
}

/*
 Compute a point on a quadratic bezier curve with control points a, b, and c.
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T QuadraticBezier(T a, T b, T c, float t)
{
	T d = Lerp<T>(a, b, t);
	T e = Lerp<T>(b, c, t);
	return Lerp<T>(d, e, t);
}

/*
 Compute a point on a cubic bezier curve with control points a, b, c, and d.
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T CubicBezier(T a, T b, T c, T d, float t)
{
	T e = Lerp<T>(a, b, t);
	T f = Lerp<T>(b, c, t);
	T g = Lerp<T>(c, d, t);
	return QuadraticBezier<T>(e, f, g, t);
}
