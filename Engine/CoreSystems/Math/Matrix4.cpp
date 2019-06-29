#include"Matrix4.h"
#include"Matrix3.h"
#include"Vector4.h"
#include"Vector3.h"
#include<iostream>
#include<iomanip>

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] = 0.0f;
	}
	matrixEntry[0] = matrixEntry[5] = matrixEntry[10] = matrixEntry[15] = 1.0f;
}

Matrix4::Matrix4(float scalar)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] = scalar;
	}
}

Matrix4::Matrix4(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15)
{
	matrixEntry[0] = m0;
	matrixEntry[1] = m1;
	matrixEntry[2] = m2;
	matrixEntry[3] = m3;

	matrixEntry[4] = m4;
	matrixEntry[5] = m5;
	matrixEntry[6] = m6;
	matrixEntry[7] = m7;

	matrixEntry[8] = m8;
	matrixEntry[9] = m9;
	matrixEntry[10] = m10;
	matrixEntry[11] = m11;

	matrixEntry[12] = m12;
	matrixEntry[13] = m13;
	matrixEntry[14] = m14;
	matrixEntry[15] = m15;
}

Matrix4::Matrix4(float * entries)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] = entries[i];
	}
}

Matrix4::Matrix4(const Vector4 & v)
{
	for (int i = 0; i < 4; i++)
	{
		matrixEntry[4 * i] = v.x;
		matrixEntry[4 * i + 1] = v.y;
		matrixEntry[4 * i + 2] = v.z;
		matrixEntry[4 * i + 3] = v.w;
	}
}

Matrix4::Matrix4(const Vector4 & x, const Vector4 & y, const Vector4 & z, const Vector4 & w)
{
	matrixEntry[0] = x.x;
	matrixEntry[1] = x.y;
	matrixEntry[2] = x.z;
	matrixEntry[3] = x.w;

	matrixEntry[4] = y.x;
	matrixEntry[5] = y.y;
	matrixEntry[6] = y.z;
	matrixEntry[7] = y.w;

	matrixEntry[8] = z.x;
	matrixEntry[9] = z.y;
	matrixEntry[10] = z.z;
	matrixEntry[11] = z.w;

	matrixEntry[12] = w.x;
	matrixEntry[13] = w.y;
	matrixEntry[14] = w.z;
	matrixEntry[15] = w.w;
}

Matrix4::Matrix4(const Matrix3 & m)
{
	matrixEntry[0] = m.matrixEntry[0];
	matrixEntry[4] = m.matrixEntry[3];
	matrixEntry[8] = m.matrixEntry[6];

	matrixEntry[1] = m.matrixEntry[1];
	matrixEntry[5] = m.matrixEntry[4];
	matrixEntry[9] = m.matrixEntry[7];

	matrixEntry[2] = m.matrixEntry[2];
	matrixEntry[6] = m.matrixEntry[5];
	matrixEntry[10] = m.matrixEntry[8];

	matrixEntry[3] = matrixEntry[7] = matrixEntry[11] = matrixEntry[12] = matrixEntry[13] = matrixEntry[14] = 0.0f;
	matrixEntry[15] = 1.0f;
}

Matrix4::Matrix4(const Matrix3 & m, const Vector3 & v)
{
	matrixEntry[0] = m.matrixEntry[0];
	matrixEntry[4] = m.matrixEntry[3];
	matrixEntry[8] = m.matrixEntry[6];

	matrixEntry[1] = m.matrixEntry[1];
	matrixEntry[5] = m.matrixEntry[4];
	matrixEntry[9] = m.matrixEntry[7];

	matrixEntry[2] = m.matrixEntry[2];
	matrixEntry[6] = m.matrixEntry[5];
	matrixEntry[10] = m.matrixEntry[8];

	matrixEntry[12] = v.x;
	matrixEntry[13] = v.y;
	matrixEntry[14] = v.z;

	matrixEntry[3] = matrixEntry[7] = matrixEntry[11] = 0.0f;
	matrixEntry[15] = 1.0f;
}

Matrix4::Matrix4(const Matrix4 & m)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] = m.matrixEntry[i];
	}
}

Matrix4 & Matrix4::operator=(const Matrix4 & m)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] = m.matrixEntry[i];
	}
	return *this;
}

Matrix4 Matrix4::operator-() const
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = -matrixEntry[i];
	}

	return result;
}

Vector4 & Matrix4::operator[](int i)
{
	Clamp<int>(i, 0, 3);
	return (Vector4&)matrixEntry[i * 4];
}

const Vector4 & Matrix4::operator[](int i) const
{
	Clamp<int>(i, 0, 3);
	return (Vector4&)matrixEntry[i * 4];
}

Matrix4 Matrix4::operator+(const Matrix4 & m) const
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] + m.matrixEntry[i];
	}

	return result;
}

Matrix4 & Matrix4::operator+=(const Matrix4 & m)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] += m.matrixEntry[i];
	}
	return *this;
}

Matrix4 Matrix4::operator-(const Matrix4 & m) const
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] - m.matrixEntry[i];
	}

	return result;
}

Matrix4 & Matrix4::operator-=(const Matrix4 & m)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] -= m.matrixEntry[i];
	}
	return *this;
}

Matrix4 Matrix4::operator*(float scalar) const
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] * scalar;
	}

	return result;
}

Matrix4 & Matrix4::operator*=(float scalar)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] *= scalar;
	}
	return *this;
}

Matrix4 Matrix4::operator/(float scalar) const
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] / scalar;
	}

	return result;
}

Matrix4 & Matrix4::operator/=(float scalar)
{
	for (int i = 0; i < 16; i++)
	{
		matrixEntry[i] /= scalar;
	}
	return *this;
}

Vector4 Matrix4::operator*(const Vector4 & v) const
{
	return Vector4(
		matrixEntry[0] * v.x + matrixEntry[4] * v.y + matrixEntry[8] * v.z + matrixEntry[12] * v.w,
		matrixEntry[1] * v.x + matrixEntry[5] * v.y + matrixEntry[9] * v.z + matrixEntry[13] * v.w,
		matrixEntry[2] * v.x + matrixEntry[6] * v.y + matrixEntry[10] * v.z + matrixEntry[14] * v.w,
		matrixEntry[3] * v.x + matrixEntry[7] * v.y + matrixEntry[11] * v.z + matrixEntry[15] * v.w
		);
}

Matrix4 Matrix4::operator*(const Matrix4 & m) const
{
	float entry[16];
	entry[0] = matrixEntry[0] * m.matrixEntry[0] + matrixEntry[4] * m.matrixEntry[1] + matrixEntry[8] * m.matrixEntry[2] + matrixEntry[12] * m.matrixEntry[3];
	entry[1] = matrixEntry[1] * m.matrixEntry[0] + matrixEntry[5] * m.matrixEntry[1] + matrixEntry[9] * m.matrixEntry[2] + matrixEntry[13] * m.matrixEntry[3];
	entry[2] = matrixEntry[2] * m.matrixEntry[0] + matrixEntry[6] * m.matrixEntry[1] + matrixEntry[10] * m.matrixEntry[2] + matrixEntry[14] * m.matrixEntry[3];
	entry[3] = matrixEntry[3] * m.matrixEntry[0] + matrixEntry[7] * m.matrixEntry[1] + matrixEntry[11] * m.matrixEntry[2] + matrixEntry[15] * m.matrixEntry[3];

	entry[4] = matrixEntry[0] * m.matrixEntry[4] + matrixEntry[4] * m.matrixEntry[5] + matrixEntry[8] * m.matrixEntry[6] + matrixEntry[12] * m.matrixEntry[7];
	entry[5] = matrixEntry[1] * m.matrixEntry[4] + matrixEntry[5] * m.matrixEntry[5] + matrixEntry[9] * m.matrixEntry[6] + matrixEntry[13] * m.matrixEntry[7];
	entry[6] = matrixEntry[2] * m.matrixEntry[4] + matrixEntry[6] * m.matrixEntry[5] + matrixEntry[10] * m.matrixEntry[6] + matrixEntry[14] * m.matrixEntry[7];
	entry[7] = matrixEntry[3] * m.matrixEntry[4] + matrixEntry[7] * m.matrixEntry[5] + matrixEntry[11] * m.matrixEntry[6] + matrixEntry[15] * m.matrixEntry[7];

	entry[8] = matrixEntry[0] * m.matrixEntry[8] + matrixEntry[4] * m.matrixEntry[9] + matrixEntry[8] * m.matrixEntry[10] + matrixEntry[12] * m.matrixEntry[11];
	entry[9] = matrixEntry[1] * m.matrixEntry[8] + matrixEntry[5] * m.matrixEntry[9] + matrixEntry[9] * m.matrixEntry[10] + matrixEntry[13] * m.matrixEntry[11];
	entry[10] = matrixEntry[2] * m.matrixEntry[8] + matrixEntry[6] * m.matrixEntry[9] + matrixEntry[10] * m.matrixEntry[10] + matrixEntry[14] * m.matrixEntry[11];
	entry[11] = matrixEntry[3] * m.matrixEntry[8] + matrixEntry[7] * m.matrixEntry[9] + matrixEntry[11] * m.matrixEntry[10] + matrixEntry[15] * m.matrixEntry[11];

	entry[12] = matrixEntry[0] * m.matrixEntry[12] + matrixEntry[4] * m.matrixEntry[13] + matrixEntry[8] * m.matrixEntry[14] + matrixEntry[12] * m.matrixEntry[15];
	entry[13] = matrixEntry[1] * m.matrixEntry[12] + matrixEntry[5] * m.matrixEntry[13] + matrixEntry[9] * m.matrixEntry[14] + matrixEntry[13] * m.matrixEntry[15];
	entry[14] = matrixEntry[2] * m.matrixEntry[12] + matrixEntry[6] * m.matrixEntry[13] + matrixEntry[10] * m.matrixEntry[14] + matrixEntry[14] * m.matrixEntry[15];
	entry[15] = matrixEntry[3] * m.matrixEntry[12] + matrixEntry[7] * m.matrixEntry[13] + matrixEntry[11] * m.matrixEntry[14] + matrixEntry[15] * m.matrixEntry[15];

	return Matrix4(entry);
}

Matrix4 & Matrix4::operator*=(const Matrix4 & m)
{
	return (*this = *this * m);
}

bool Matrix4::operator==(const Matrix4 & m) const
{
	for (int i = 0; i < 16; i++)
	{
		if (matrixEntry[i] != matrixEntry[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4 & m) const
{
	return !(*this == m);
}

Matrix4 Matrix4::CompMult(const Matrix4 & m1, const Matrix4 & m2)
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] * m2.matrixEntry[i];
	}

	return result;
}

Matrix4 Matrix4::CompDiv(const Matrix4 & m1, const Matrix4 & m2)
{
	Matrix4 result;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] / m2.matrixEntry[i];
	}

	return result;
}

bool Matrix4::NearlyEqual(const Matrix3 & m, float tolerance) const
{
	for (int i = 0; i < 16; i++)
	{
		if (Abs(matrixEntry[i] - matrixEntry[i]) > tolerance)
		{
			return false;
		}
	}
	return true;
}

float Matrix4::GetDeterminant() const
{
	float m[4];
	m[0] = matrixEntry[0] * (
		matrixEntry[5] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[11] * matrixEntry[14]) +
		matrixEntry[9] * (matrixEntry[7] * matrixEntry[14] - matrixEntry[6] * matrixEntry[15]) +
		matrixEntry[13] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[7] * matrixEntry[10]));
	m[1] = matrixEntry[4] * (
		matrixEntry[1] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[11] * matrixEntry[14]) +
		matrixEntry[9] * (matrixEntry[3] * matrixEntry[14] - matrixEntry[2] * matrixEntry[15]) +
		matrixEntry[13] * (matrixEntry[2] * matrixEntry[11] - matrixEntry[3] * matrixEntry[10]));
	m[2] = matrixEntry[8] * (
		matrixEntry[1] * (matrixEntry[6] * matrixEntry[15] - matrixEntry[7] * matrixEntry[14]) +
		matrixEntry[5] * (matrixEntry[3] * matrixEntry[14] - matrixEntry[2] * matrixEntry[15]) +
		matrixEntry[13] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[3] * matrixEntry[6]));
	m[3] = matrixEntry[12] * (
		matrixEntry[1] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[7] * matrixEntry[10]) +
		matrixEntry[5] * (matrixEntry[3] * matrixEntry[10] - matrixEntry[2] * matrixEntry[11]) +
		matrixEntry[9] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[3] * matrixEntry[6]));

	return m[0] - m[1] + m[2] - m[3];
}

Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(
		matrixEntry[0], matrixEntry[1], matrixEntry[2], matrixEntry[3],
		matrixEntry[4], matrixEntry[5], matrixEntry[6], matrixEntry[7],
		matrixEntry[8], matrixEntry[9], matrixEntry[10], matrixEntry[11],
		matrixEntry[12], matrixEntry[13], matrixEntry[14], matrixEntry[15]
	);
}

Matrix4 Matrix4::GetInverse() const
{
	Matrix4 result;

	float m[16];

	m[0] = matrixEntry[5] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[14] * matrixEntry[11]) -
		matrixEntry[9] * (matrixEntry[6] * matrixEntry[15] - matrixEntry[14] * matrixEntry[7]) +
		matrixEntry[13] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[10] * matrixEntry[7]);

	m[1] = -matrixEntry[1] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[14] * matrixEntry[11]) +
		matrixEntry[9] * (matrixEntry[2] * matrixEntry[15] - matrixEntry[14] * matrixEntry[3]) -
		matrixEntry[13] * (matrixEntry[2] * matrixEntry[11] - matrixEntry[10] * matrixEntry[3]);

	m[2] = matrixEntry[1] * (matrixEntry[6] * matrixEntry[15] - matrixEntry[14] * matrixEntry[7]) -
		matrixEntry[5] * (matrixEntry[2] * matrixEntry[15] - matrixEntry[14] * matrixEntry[3]) +
		matrixEntry[13] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[6] * matrixEntry[3]);

	m[3] = -matrixEntry[1] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[10] * matrixEntry[7]) +
		matrixEntry[5] * (matrixEntry[2] * matrixEntry[11] - matrixEntry[10] * matrixEntry[3]) -
		matrixEntry[9] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[6] * matrixEntry[3]);

	m[4] = -matrixEntry[4] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[14] * matrixEntry[11]) +
		matrixEntry[8] * (matrixEntry[6] * matrixEntry[15] - matrixEntry[14] * matrixEntry[7]) -
		matrixEntry[12] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[10] * matrixEntry[7]);

	m[5] = matrixEntry[0] * (matrixEntry[10] * matrixEntry[15] - matrixEntry[14] * matrixEntry[11]) -
		matrixEntry[8] * (matrixEntry[2] * matrixEntry[15] - matrixEntry[14] * matrixEntry[3]) +
		matrixEntry[12] * (matrixEntry[2] * matrixEntry[11] - matrixEntry[10] * matrixEntry[3]);

	m[6] = -matrixEntry[0] * (matrixEntry[6] * matrixEntry[15] - matrixEntry[14] * matrixEntry[7]) +
		matrixEntry[4] * (matrixEntry[2] * matrixEntry[15] - matrixEntry[14] * matrixEntry[3]) -
		matrixEntry[12] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[6] * matrixEntry[3]);

	m[7] = matrixEntry[0] * (matrixEntry[6] * matrixEntry[11] - matrixEntry[10] * matrixEntry[7]) -
		matrixEntry[4] * (matrixEntry[2] * matrixEntry[11] - matrixEntry[10] * matrixEntry[3]) +
		matrixEntry[8] * (matrixEntry[2] * matrixEntry[7] - matrixEntry[6] * matrixEntry[3]);

	m[8] = matrixEntry[4] * (matrixEntry[9] * matrixEntry[15] - matrixEntry[13] * matrixEntry[11]) -
		matrixEntry[8] * (matrixEntry[5] * matrixEntry[15] - matrixEntry[13] * matrixEntry[7]) +
		matrixEntry[12] * (matrixEntry[5] * matrixEntry[11] - matrixEntry[9] * matrixEntry[7]);

	m[9] = -matrixEntry[0] * (matrixEntry[9] * matrixEntry[15] - matrixEntry[13] * matrixEntry[11]) +
		matrixEntry[8] * (matrixEntry[1] * matrixEntry[15] - matrixEntry[13] * matrixEntry[3]) -
		matrixEntry[12] * (matrixEntry[1] * matrixEntry[11] - matrixEntry[9] * matrixEntry[3]);

	m[10] = matrixEntry[0] * (matrixEntry[5] * matrixEntry[15] - matrixEntry[13] * matrixEntry[7]) -
		matrixEntry[4] * (matrixEntry[1] * matrixEntry[15] - matrixEntry[13] * matrixEntry[3]) +
		matrixEntry[12] * (matrixEntry[1] * matrixEntry[7] - matrixEntry[5] * matrixEntry[3]);

	m[11] = -matrixEntry[0] * (matrixEntry[5] * matrixEntry[11] - matrixEntry[9] * matrixEntry[7]) +
		matrixEntry[4] * (matrixEntry[1] * matrixEntry[11] - matrixEntry[9] * matrixEntry[3]) -
		matrixEntry[8] * (matrixEntry[1] * matrixEntry[7] - matrixEntry[5] * matrixEntry[3]);

	m[12] = -matrixEntry[4] * (matrixEntry[9] * matrixEntry[14] - matrixEntry[13] * matrixEntry[10]) +
		matrixEntry[8] * (matrixEntry[5] * matrixEntry[14] - matrixEntry[13] * matrixEntry[6]) -
		matrixEntry[12] * (matrixEntry[5] * matrixEntry[10] - matrixEntry[9] * matrixEntry[6]);

	m[13] = matrixEntry[0] * (matrixEntry[9] * matrixEntry[14] - matrixEntry[13] * matrixEntry[10]) -
		matrixEntry[8] * (matrixEntry[1] * matrixEntry[14] - matrixEntry[13] * matrixEntry[2]) +
		matrixEntry[12] * (matrixEntry[1] * matrixEntry[10] - matrixEntry[9] * matrixEntry[2]);

	m[14] = -matrixEntry[0] * (matrixEntry[5] * matrixEntry[14] - matrixEntry[13] * matrixEntry[6]) +
		matrixEntry[4] * (matrixEntry[1] * matrixEntry[14] - matrixEntry[13] * matrixEntry[2]) -
		matrixEntry[12] * (matrixEntry[1] * matrixEntry[6] - matrixEntry[5] * matrixEntry[2]);

	m[15] = matrixEntry[0] * (matrixEntry[5] * matrixEntry[10] - matrixEntry[9] * matrixEntry[6]) -
		matrixEntry[4] * (matrixEntry[1] * matrixEntry[10] - matrixEntry[9] * matrixEntry[2]) +
		matrixEntry[8] * (matrixEntry[1] * matrixEntry[6] - matrixEntry[5] * matrixEntry[2]);

	float det = matrixEntry[0] * m[0] + matrixEntry[4] * m[1] + matrixEntry[8] * m[2] + matrixEntry[12] * m[3];

	if (Abs(det) < EPSILON_EQUAL)
	{
		return Matrix4();
	}

	det = 1.0f / det;

	for (int i = 0; i < 16; i++)
	{
		result.matrixEntry[i] = det * m[i];
	}

	return result;
}

Matrix3 Matrix4::GetRotation() const
{
	return Matrix3(
		matrixEntry[0], matrixEntry[4], matrixEntry[8],
		matrixEntry[1],matrixEntry[5],matrixEntry[9],
		matrixEntry[2],matrixEntry[6],matrixEntry[10]);
}

Vector3 Matrix4::GetTranslation() const
{
	return Vector3(matrixEntry[12],matrixEntry[13],matrixEntry[14]);
}

Matrix4 Matrix4::GetInverseScale(const Matrix4 & m)
{
	Matrix4 result = m;
	result[0][0] = 1.0f / result[0][0];
	result[1][1] = 1.0f / result[1][1];
	result[2][2] = 1.0f / result[2][2];
	result[3][3] = 1.0f / result[3][3];
	return result;
}

Matrix4 Matrix4::GetInverseRotation(const Matrix4 & m)
{
	return m.GetTranspose();
}

Matrix4 Matrix4::GetInverseTranslatoin(const Matrix4 & m)
{
	return -m;
}

Vector4 Matrix4::GetRow(int row) const
{
	Clamp<int>(row, 0, 3);
	return Vector4(matrixEntry[0 + row], matrixEntry[4 + row], matrixEntry[8 + row], matrixEntry[12 + row]);
}

Vector4 Matrix4::GetColumn(int col) const
{
	Clamp<int>(col, 0, 3);
	return Vector4(matrixEntry[col * 4], matrixEntry[col * 4 + 1], matrixEntry[col * 4 + 2], matrixEntry[col * 4 + 2]);
}

Matrix4 Matrix4::CreateScale(float scaleFactor)
{
	return Matrix4(Matrix3::CreateScale(scaleFactor));
}

Matrix4 Matrix4::CreateScale(float factorX, float factorY, float factorZ)
{
	return Matrix4(Matrix3::CreateScale(factorX, factorY, factorZ));
}

Matrix4 Matrix4::CreateScale(const Vector3 & scaleFactors)
{
	return Matrix4(Matrix3::CreateScale(scaleFactors));
}

Matrix4 Matrix4::CreateScale(float factorX, float factorY, float factorZ, const Vector3 & axisX, const Vector3 & axisY, const Vector3 & axisZ)
{
	return Matrix4(Matrix3::CreateScale(factorX, factorY, factorZ, axisX, axisY, axisZ));
}

Matrix4 Matrix4::CreateScale(const Vector3 & scaleFactors, const Vector3 & axisX, const Vector3 & axisY, const Vector3 & axisZ)
{
	return Matrix4(Matrix3::CreateScale(scaleFactors, axisX, axisY, axisZ));
}

Matrix4 Matrix4::CreateRotation(float angle, float x, float y, float z)
{
	return Matrix4(Matrix3::CreateRotation(angle, x, y, z));
}

Matrix4 Matrix4::CreateRotation(float angle, const Vector3 & axis)
{
	return Matrix4(Matrix3::CreateRotation(angle, axis));
}

Matrix4 Matrix4::CreateRotataion(Quaternion & q)
{
	return Matrix4(Matrix3::CreateRotation(q));
}

Matrix4 Matrix4::CreateTranslation(float x, float y, float z)
{
	return Matrix4(Matrix3(), Vector3(x, y, z));
}

Matrix4 Matrix4::CreateTranslation(const Vector3 & v)
{
	return Matrix4(Matrix3(), v);
}

Matrix4 Matrix4::CreateLookAt(const Vector3 & cameraPos, const Vector3 & POI, const Vector3 & up)
{
	Vector3 forward = (cameraPos - POI).GetNormalized();
	Vector3 upN = up.GetNormalized();
	Vector3 right = Vector3::CrossProduct(upN, forward);
	upN = Vector3::CrossProduct(forward, right);

	return Matrix4(
		Vector4(right.x, upN.x, forward.x, 0.0f),
		Vector4(right.y, upN.y, forward.y, 0.0f),
		Vector4(right.z, upN.z, forward.z, 0.0f),
		Vector4(
			-Vector3::DotProduct(right, cameraPos),
			-Vector3::DotProduct(upN, cameraPos),
			-Vector3::DotProduct(forward, cameraPos),
			1.0f
		)
	);
}

Matrix4 Matrix4::CreateProjPersp(float left, float right, float top, float bottom, float near, float far)
{
	return Matrix4(
		2.0f*near / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
		0.0f, 2.0f*near / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
		0.0f, 0.0f, (far + near) / (near - far), 2.0f*near*far / (near - far),
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Matrix4 Matrix4::CreateProjPerspInfinite(float left, float right, float top, float bottom, float near)
{
	return Matrix4(
		2.0f*near / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
		0.0f, 2.0f*near / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
		0.0f, 0.0f, -1.0f, -2.0f*near,
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Matrix4 Matrix4::CreateProjPerspSymmetric(float fovY, float aspectRatio, float near, float far)
{
	float nt = 1.0f / tanf(0.5f * fovY);
	float nr = nt / aspectRatio;
	return Matrix4(
		nr, 0.0f, 0.0f, 0.0f,
		0.0f, nt, 0.0f, 0.0f,
		0.0f, 0.0f, (far + near) / (near - far), 2.0f*far*near / (near - far),
		0.0f, 0.0f, -1.0f, 0.0f
	);
}

Matrix4 Matrix4::CreateProjOrthographic(float left, float right, float top, float bottom, float near, float far)
{
	return Matrix4(
		2.0f / (right - left), 0.0f, 0.0f, (right + left) / (left - right),
		0.0f, 2.0f / (top - bottom), 0.0f, (top + bottom) / (bottom - top),
		0.0f, 0.0f, 2.0f / (near - far), (far + near) / (near - far),
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Matrix4::SetAsIdentity()
{
	*this = Matrix4();
}

void Matrix4::SetRow(int row, const Vector4 & v)
{
	SetRow(row, v.x, v.y, v.z, v.w);
}

void Matrix4::SetRow(int row, float x, float y, float z, float w)
{
	Clamp<int>(row, 0, 3);
	matrixEntry[row] = x;
	matrixEntry[row + 4] = y;
	matrixEntry[row + 8] = z;
	matrixEntry[row + 12] = w;
}

void Matrix4::SetColumn(int col, const Vector4 & v)
{
	SetColumn(col, v.x, v.y, v.z, v.w);
}

void Matrix4::SetColumn(int col, float x, float y, float z, float w)
{
	Clamp<int>(col, 0, 3);
	matrixEntry[col * 4] = x;
	matrixEntry[col * 4 + 1] = y;
	matrixEntry[col * 4 + 2] = z;
	matrixEntry[col * 4 + 3] = w;
}

void Matrix4::Print() const
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			std::cout << std::setw(4) << matrixEntry[r + c * 3] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix4::~Matrix4()
{
}

