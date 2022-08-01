#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include<iostream>
#include<cmath>

float Sin(float angle)
{
	return sinf(angle);
}

float Cos(float angle)
{
	return cosf(angle);
}

float Tan(float angle)
{
	return tanf(angle);
}

float Asin(float x)
{
	return asinf(x);
}

float Acos(float x)
{
	return acosf(x);
}

float Atan(float x)
{
	return atanf(x);
}

float Atan2(float y, float x)
{
	return atan2f(y, x);
}

float Exp(float x)
{
	return expf(x);
}

float Pow(float a, float x)
{
	return powf(a, x);
}

float Pow2(float x)
{
	return powf(2, x);
}

float Log2(float x)
{
	return log2f(x);
}

float Log10(float x)
{
	return log10f(x);
}

float LogE(float x)
{
	return logf(x);
}

float LogX(float Base, float x)
{
	return logf(x) / logf(Base);
}

float Abs(float x)
{
	return abs(x);
}

float Ceil(float x)
{
	return ceilf(x);
}

int CeilToInt(float x)
{
	return (int)ceilf(x);
}

float Floor(float x)
{
	return floorf(x);
}

int FloorToInt(float x)
{
	return (int)floorf(x);
}

float Fractional(float x)
{
	if (x >= 0.0f)
	{
		return x - Floor(x);
	}
	else
	{
		return x - Ceil(x);
	}
}

float Integral(float x)
{
	return x - Fractional(x);
}

int GCD(int a, int b)
{
	if (a < 0) a = Abs(a);
	if (b < 0) b = Abs(b);

	if (b == 0)
		return a;
	return GCD(b, a % b);
}

int LCM(int a, int b)
{
	return a * b / GCD(a, b);
}

bool isEqualTo(float a, float b, float tolerance)
{
	return Abs(a - b) <= tolerance;
}

bool NearlyZero(float a, float tolerance)
{
	return Abs(a) <= tolerance;;
}

float Round(float x)
{
	return roundf(x);
}

int RoundToInt(float x)
{
	return (int)roundf(x);
}

float Sqrt(float x)
{
	return sqrtf(x);
}
