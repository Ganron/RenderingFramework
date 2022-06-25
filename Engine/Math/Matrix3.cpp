#include"Matrix3.h"
#include"Matrix4.h"
#include"Vector3.h"
#include"Quaternion.h"
#include<iostream>
#include<iomanip>

Matrix3::Matrix3()
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] = 0.0f;
	}
	matrixEntry[0] = matrixEntry[4] = matrixEntry[8] = 1.0f;
}

Matrix3::Matrix3(float scalar)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] = scalar;
	}
}

Matrix3::Matrix3(float m0, float m3, float m6, float m1, float m4, float m7, float m2, float m5, float m8)
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
}

Matrix3::Matrix3(float * entries)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] = entries[i];
	}
}

Matrix3::Matrix3(const Vector3 & v)
{
	for (int i = 0; i < 3; i++)
	{
		matrixEntry[3 * i] = v.x;
		matrixEntry[3 * i + 1] = v.y;
		matrixEntry[3 * i + 2] = v.z;
	}
}

Matrix3::Matrix3(const Vector3 & x, const Vector3 & y, const Vector3 & z)
{
	matrixEntry[0] = x.x;
	matrixEntry[1] = x.y;
	matrixEntry[2] = x.z;

	matrixEntry[3] = y.x;
	matrixEntry[4] = y.y;
	matrixEntry[5] = y.z;

	matrixEntry[6] = z.x;
	matrixEntry[7] = z.y;
	matrixEntry[8] = z.z;
}

Matrix3::Matrix3(const Matrix3 & m)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] = m.matrixEntry[i];
	}
}

Matrix3::Matrix3(const Matrix4 & m, int row, int col)
{
	Clamp<int>(row, 0, 3);
	Clamp<int>(col, 0, 3);

	int i = 0;
	for (int j = 0; j < 16; j++)
	{
		if (j / 4 != col && j % 4 != row)
		{
			matrixEntry[i] = m.matrixEntry[j];
			i++;
		}
	}
}

Matrix3 & Matrix3::operator=(const Matrix3 & m)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] = m.matrixEntry[i];
	}
	return *this;
}

Matrix3 Matrix3::operator-() const
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = -matrixEntry[i];
	}

	return result;
}

Vector3 & Matrix3::operator[](int i)
{
	Clamp<int>(i, 0, 2);
	return (Vector3&)matrixEntry[i * 3];
}

const Vector3 & Matrix3::operator[](int i) const
{
	Clamp<int>(i, 0, 2);
	return (Vector3&)matrixEntry[i * 3];
}

Matrix3 Matrix3::operator+(const Matrix3 & m) const
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] + m.matrixEntry[i];
	}

	return result;
}

Matrix3 & Matrix3::operator+=(const Matrix3 & m)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] += m.matrixEntry[i];
	}
	return *this;
}

Matrix3 Matrix3::operator-(const Matrix3 & m) const
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] - m.matrixEntry[i];
	}

	return result;
}

Matrix3 & Matrix3::operator-=(const Matrix3 & m)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] -= m.matrixEntry[i];
	}
	return *this;
}

Matrix3 Matrix3::operator*(float scalar) const
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] * scalar;
	}

	return result;
}

Matrix3 & Matrix3::operator*=(float scalar)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] *= scalar;
	}
	return *this;
}

Matrix3 Matrix3::operator/(float scalar) const
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] / scalar;
	}

	return result;
}

Matrix3 & Matrix3::operator/=(float scalar)
{
	for (int i = 0; i < 9; i++)
	{
		matrixEntry[i] /= scalar;
	}
	return *this;
}

Vector3 Matrix3::operator*(const Vector3 & v) const
{
	return Vector3(
		matrixEntry[0] * v.x + matrixEntry[3] * v.y + matrixEntry[6] * v.z,
		matrixEntry[1] * v.x + matrixEntry[4] * v.y + matrixEntry[7] * v.z,
		matrixEntry[2] * v.x + matrixEntry[5] * v.y + matrixEntry[8] * v.z);
}

Matrix3 Matrix3::operator*(const Matrix3 & m) const
{
	float entry[9];

	entry[0] = matrixEntry[0] * m.matrixEntry[0] + matrixEntry[3] * m.matrixEntry[1] + matrixEntry[6] * m.matrixEntry[2];
	entry[1] = matrixEntry[1] * m.matrixEntry[0] + matrixEntry[4] * m.matrixEntry[1] + matrixEntry[7] * m.matrixEntry[2];
	entry[2] = matrixEntry[2] * m.matrixEntry[0] + matrixEntry[5] * m.matrixEntry[1] + matrixEntry[8] * m.matrixEntry[2];

	entry[3] = matrixEntry[0] * m.matrixEntry[3] + matrixEntry[3] * m.matrixEntry[4] + matrixEntry[6] * m.matrixEntry[5];
	entry[4] = matrixEntry[1] * m.matrixEntry[3] + matrixEntry[4] * m.matrixEntry[4] + matrixEntry[7] * m.matrixEntry[5];
	entry[5] = matrixEntry[2] * m.matrixEntry[3] + matrixEntry[5] * m.matrixEntry[4] + matrixEntry[8] * m.matrixEntry[5];

	entry[6] = matrixEntry[0] * m.matrixEntry[6] + matrixEntry[3] * m.matrixEntry[7] + matrixEntry[6] * m.matrixEntry[8];
	entry[7] = matrixEntry[1] * m.matrixEntry[6] + matrixEntry[4] * m.matrixEntry[7] + matrixEntry[7] * m.matrixEntry[8];
	entry[8] = matrixEntry[2] * m.matrixEntry[6] + matrixEntry[5] * m.matrixEntry[7] + matrixEntry[8] * m.matrixEntry[8];

	return Matrix3(entry);
}

Matrix3 & Matrix3::operator*=(const Matrix3 & m)
{
	return (*this = *this * m);
}

bool Matrix3::operator==(const Matrix3 & m) const
{
	for (int i = 0; i < 9; i++)
	{
		if (matrixEntry[i]!=matrixEntry[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix3::operator!=(const Matrix3 & m) const
{
	return !(*this == m);
}

Matrix3 Matrix3::compMult(const Matrix3 & m1, const Matrix3 & m2)
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] * m2.matrixEntry[i];
	}

	return result;
}

Matrix3 Matrix3::compDiv(const Matrix3 & m1, const Matrix3 & m2)
{
	Matrix3 result;

	for (int i = 0; i < 9; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] / m2.matrixEntry[i];
	}

	return result;
}

bool Matrix3::isEqualTo(const Matrix3 & m, float tolerance) const
{
	for (int i = 0; i < 9; i++)
	{
		if ( Abs(matrixEntry[i] - matrixEntry[i])>tolerance )
		{
			return false;
		}
	}
	return true;
}

float Matrix3::GetDeterminant() const
{
	float cofactor1 = matrixEntry[4] * matrixEntry[8] - matrixEntry[7] * matrixEntry[5];
	float cofactor2 = matrixEntry[1] * matrixEntry[8] - matrixEntry[7] * matrixEntry[2];
	float cofactor3 = matrixEntry[1] * matrixEntry[5] - matrixEntry[4] * matrixEntry[2];
	return matrixEntry[0] * cofactor1 - matrixEntry[3] * cofactor2 + matrixEntry[6] * cofactor3;
}

Matrix3 Matrix3::GetTranspose() const
{
	return Matrix3(
		matrixEntry[0], matrixEntry[1], matrixEntry[2],
		matrixEntry[3], matrixEntry[4], matrixEntry[5],
		matrixEntry[6], matrixEntry[7], matrixEntry[8]
	);
}

Matrix3 Matrix3::GetInverse() const
{
	float det = GetDeterminant();
	if (Abs(det)<EPSILON_EQUAL)
	{
		return Matrix3();
	}
	det = 1.0f / det;

	float entry[9];
	entry[0] = det * (matrixEntry[4] * matrixEntry[8] - matrixEntry[7] * matrixEntry[5]);
	entry[3] = det * (matrixEntry[6] * matrixEntry[5] - matrixEntry[3] * matrixEntry[8]);
	entry[6] = det * (matrixEntry[3] * matrixEntry[7] - matrixEntry[6] * matrixEntry[4]);

	entry[1] = det * (matrixEntry[7] * matrixEntry[2] - matrixEntry[1] * matrixEntry[8]);
	entry[4] = det * (matrixEntry[0] * matrixEntry[8] - matrixEntry[6] * matrixEntry[2]);
	entry[7] = det * (matrixEntry[6] * matrixEntry[1] - matrixEntry[0] * matrixEntry[7]);

	entry[2] = det * (matrixEntry[1] * matrixEntry[5] - matrixEntry[4] * matrixEntry[2]);
	entry[5] = det * (matrixEntry[3] * matrixEntry[2] - matrixEntry[0] * matrixEntry[5]);
	entry[8] = det * (matrixEntry[0] * matrixEntry[4] - matrixEntry[3] * matrixEntry[1]);

	return Matrix3(entry);
}

Matrix3 Matrix3::GetInverseScale(const Matrix3& m)
{
	Matrix3 result = m;
	result[0][0] = 1.0f / result[0][0];
	result[1][1] = 1.0f / result[1][1];
	result[2][2] = 1.0f / result[2][2];
	return result;
}

Matrix3 Matrix3::GetInverseRotation(const Matrix3 & m)
{
	return m.GetTranspose();
}

Vector3 Matrix3::GetRow(int row) const
{
	Clamp<int>(row, 0, 2);
	return Vector3(matrixEntry[0 + row], matrixEntry[3 + row], matrixEntry[6 + row]);
}

Vector3 Matrix3::GetColumn(int col) const
{
	Clamp<int>(col, 0, 2);
	return Vector3(matrixEntry[col * 3], matrixEntry[col * 3 + 1], matrixEntry[col * 3 + 2]);
}

Matrix3 Matrix3::CreateScale(float scaleFactor)
{
	return Matrix3(
		scaleFactor, 0.0f, 0.0f,
		0.0f, scaleFactor, 0.0f,
		0.0f, 0.0f, scaleFactor);
}

Matrix3 Matrix3::CreateScale(float factorX, float factorY, float factorZ)
{
	return Matrix3(
		factorX, 0.0f, 0.0f,
		0.0f, factorY, 0.0f,
		0.0f, 0.0f, factorZ);
}

Matrix3 Matrix3::CreateScale(const Vector3 & scaleFactors)
{
	return Matrix3(
		scaleFactors.x, 0.0f, 0.0f,
		0.0f, scaleFactors.y, 0.0f,
		0.0f, 0.0f, scaleFactors.z);
}

Matrix3 Matrix3::CreateScale(float factorX, float factorY, float factorZ, const Vector3 & axisX, const Vector3 & axisY, const Vector3 & axisZ)
{
	Matrix3 newCoordSyst = { axisX, axisY, axisZ };
	Matrix3 scaleMat;
	scaleMat = CreateScale(factorX, factorY, factorZ);
	Matrix3 toCartesianCoord = newCoordSyst.GetInverse();

	return (newCoordSyst * scaleMat * toCartesianCoord);
}

Matrix3 Matrix3::CreateScale(const Vector3 & scaleFactors, const Vector3 & axisX, const Vector3 & axisY, const Vector3 & axisZ)
{
	return CreateScale(scaleFactors.x, scaleFactors.y, scaleFactors.z, axisX, axisY, axisZ);
}

Matrix3 Matrix3::CreateRotation(float angle, float x, float y, float z)
{
	Vector3 a = { x,y,z };
	a.normalize();

	float s = Sin(angle);
	float c = Cos(angle);

	float entry[9];
	entry[0] = c + (1 - c)* a.x * a.x;
	entry[1] = (1 - c) * a.x * a.y + s * a.z;
	entry[2] = (1 - c) * a.x * a.z - s * a.y;
	entry[3] = (1 - c) * a.x * a.y - s * a.z;
	entry[4] = c + (1 - c) * a.y * a.y;
	entry[5] = (1 - c) * a.y * a.z + s * a.x;
	entry[6] = (1 - c) * a.x * a.z + s * a.y;
	entry[7] = (1 - c) * a.y * a.z - s * a.x;
	entry[8] = c + (1 - c) * a.z * a.z;

	return Matrix3(entry);
}

Matrix3 Matrix3::CreateRotation(float angle, const Vector3 & axis)
{
	return CreateRotation(angle, axis.x, axis.y, axis.z);
}

Matrix3 Matrix3::CreateRotation(Quaternion & q)
{
	return Matrix3(
		1 - 2.0f*q.y*q.y - 2.0f*q.z*q.z, 
		2.0f*q.x*q.y - 2.0f*q.w*q.z, 
		2.0f*q.x*q.z + 2.0f*q.w*q.y,

		2.0f*q.x*q.y + 2.0f*q.w*q.z, 
		1 - 2.0f*q.x*q.x - 2.0f*q.z*q.z, 
		2.0f*q.y*q.z - 2.0f*q.w*q.x,

		2.0f*q.x*q.z - 2.0f*q.w*q.y, 
		2.0f*q.y*q.z + 2.0f*q.w*q.x, 
		1 - 2.0f*q.x*q.x - 2.0f*q.y*q.y
	);
}

void Matrix3::SetAsIdentity()
{
	*this = Matrix3();
}

void Matrix3::SetRow(int row, const Vector3 & v)
{
	SetRow(row, v.x, v.y, v.z);
}

void Matrix3::SetRow(int row, float x, float y, float z)
{
	Clamp<int>(row, 0, 2);
	matrixEntry[row] = x;
	matrixEntry[row + 3] = y;
	matrixEntry[row + 6] = z;
}

void Matrix3::SetColumn(int col, const Vector3 & v)
{
	SetColumn(col, v.x, v.y, v.z);
}

void Matrix3::SetColumn(int col, float x, float y, float z)
{
	Clamp<int>(col, 0, 2);
	matrixEntry[col * 3] = x;
	matrixEntry[col * 3 + 1] = y;
	matrixEntry[col * 3 + 2] = z;
}

void Matrix3::print() const
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

Matrix3::~Matrix3()
{
}
