#pragma once

class Vector2;
class Vector3;
class Vector4;

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

/*
 Perform linear interpolation between two values.
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T Lerp(T& x, T& y, float t)
{
	return (T)(x * (1 - t) + y * t);
}

/*
 Perform bilinear interpolation between four values.
 t must be between 0.0 and 1.0.
*/
template<class T>
inline T BiLerp(T& x1, T& x2, T& y1, T& y2, float t1, float t2)
{
	T x = Lerp<T>(x1, x2, t1);
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