#include"Matrix2.h"
#include"Matrix3.h"
#include"Vector2.h"
#include<iostream>
#include<iomanip>


Matrix2::Matrix2()
{
	matrixEntry[0] = matrixEntry[3] = 1.0f;
	matrixEntry[1] = matrixEntry[2] = 0.0f;
}

Matrix2::Matrix2(float scalar)
{
	matrixEntry[0] = scalar;
	matrixEntry[1] = scalar;

	matrixEntry[2] = scalar;
	matrixEntry[3] = scalar;
}

Matrix2::Matrix2(float m0, float m2, float m1, float m3)
{
	matrixEntry[0] = m0;
	matrixEntry[1] = m1;

	matrixEntry[2] = m2;
	matrixEntry[3] = m3;
}

Matrix2::Matrix2(float * entries)
{
	matrixEntry[0] = entries[0];
	matrixEntry[1] = entries[1];

	matrixEntry[2] = entries[2];
	matrixEntry[3] = entries[3];
}

Matrix2::Matrix2(const Vector2 & v)
{
	matrixEntry[0] = v.x;
	matrixEntry[1] = v.y;

	matrixEntry[2] = v.x;
	matrixEntry[3] = v.y;
}

Matrix2::Matrix2(const Vector2 & x, const Vector2 & y)
{
	matrixEntry[0] = x.x;
	matrixEntry[1] = x.y;

	matrixEntry[2] = y.x;
	matrixEntry[3] = y.y;
}

Matrix2::Matrix2(const Matrix2 & m)
{
	matrixEntry[0] = m.matrixEntry[0];
	matrixEntry[1] = m.matrixEntry[1];

	matrixEntry[2] = m.matrixEntry[2];
	matrixEntry[3] = m.matrixEntry[3];
}

Matrix2::Matrix2(const Matrix3& m, int row, int col)
{
	Clamp<int>(row, 0, 2);
	Clamp<int>(col, 0, 2);

	int i = 0;
	for (int j = 0; j < 9; j++)
	{
		if (j / 3 != col && j % 3 != row)
		{
			matrixEntry[i] = m.matrixEntry[j];
			i++;
		}
	}
}

Matrix2 & Matrix2::operator=(const Matrix2 & m)
{
	matrixEntry[0] = m.matrixEntry[0];
	matrixEntry[1] = m.matrixEntry[1];

	matrixEntry[2] = m.matrixEntry[2];
	matrixEntry[3] = m.matrixEntry[3];

	return *this;
}

Matrix2 Matrix2::operator-() const
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = -matrixEntry[i];
	}

	return result;
}

Vector2 & Matrix2::operator[](int i)
{
	Clamp<int>(i, 0, 1);
	return (Vector2&)matrixEntry[i * 2];
}

const Vector2 & Matrix2::operator[](int i) const
{
	Clamp<int>(i, 0, 1);
	return (Vector2&)matrixEntry[i * 2];
}

Matrix2 Matrix2::operator+(const Matrix2 & m) const
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] + m.matrixEntry[i];
	}

	return result;
}

Matrix2 & Matrix2::operator+=(const Matrix2 & m)
{
	for (int i = 0; i < 4; i++)
	{
		matrixEntry[i] += m.matrixEntry[i];
	}
	return *this;
}

Matrix2 Matrix2::operator-(const Matrix2 & m) const
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] - m.matrixEntry[i];
	}

	return result;
}

Matrix2 & Matrix2::operator-=(const Matrix2 & m)
{
	for (int i = 0; i < 4; i++)
	{
		matrixEntry[i] -= m.matrixEntry[i];
	}
	return *this;
}

Matrix2 Matrix2::operator*(float scalar) const
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] * scalar;
	}

	return result;
}

Matrix2 & Matrix2::operator*=(float scalar)
{
	for (int i = 0; i < 4; i++)
	{
		matrixEntry[i] *= scalar;
	}
	return *this;
}

Matrix2 Matrix2::operator/(float scalar) const
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = matrixEntry[i] / scalar;
	}

	return result;
}

Matrix2 & Matrix2::operator/=(float scalar)
{
	for (int i = 0; i < 4; i++)
	{
		matrixEntry[i] /= scalar;
	}
	return *this;
}

Vector2 Matrix2::operator*(const Vector2 & v) const
{
	return Vector2(
		matrixEntry[0] * v.x + matrixEntry[2] * v.y,
		matrixEntry[1] * v.x + matrixEntry[3] * v.y);
}

Matrix2 Matrix2::operator*(const Matrix2 & m) const
{
	return Matrix2(
		matrixEntry[0] * m.matrixEntry[0] + matrixEntry[2] * m.matrixEntry[1],
		matrixEntry[0] * m.matrixEntry[2] + matrixEntry[2] * m.matrixEntry[3],

		matrixEntry[1] * m.matrixEntry[0] + matrixEntry[3] * m.matrixEntry[1],
		matrixEntry[1] * m.matrixEntry[2] + matrixEntry[3] * m.matrixEntry[3]
	);
}

Matrix2 & Matrix2::operator*=(const Matrix2 & m)
{
	return (*this = *this * m);
}

bool Matrix2::operator==(const Matrix2 & m) const
{
	for (int i = 0; i < 4; i++)
	{
		if (matrixEntry[i] != matrixEntry[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix2::operator!=(const Matrix2 & m) const
{
	return !(*this == m);
}

Matrix2 Matrix2::compMult(const Matrix2 & m1, const Matrix2 & m2)
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] * m2.matrixEntry[i];
	}

	return result;
}

Matrix2 Matrix2::compDiv(const Matrix2 & m1, const Matrix2 & m2)
{
	Matrix2 result;

	for (int i = 0; i < 4; i++)
	{
		result.matrixEntry[i] = m1.matrixEntry[i] / m2.matrixEntry[i];
	}

	return result;
}

bool Matrix2::isEqualTo(const Matrix3 & m, float tolerance) const
{
	for (int i = 0; i < 4; i++)
	{
		if (Abs(matrixEntry[i] - matrixEntry[i]) > tolerance)
		{
			return false;
		}
	}
	return true;
}

float Matrix2::GetDeterminant() const
{
	return matrixEntry[0] * matrixEntry[3] - matrixEntry[1] * matrixEntry[2];
}

Matrix2 Matrix2::GetTranspose() const
{
	return Matrix2(
		matrixEntry[0], matrixEntry[1],
		matrixEntry[2], matrixEntry[3]);
}

Matrix2 Matrix2::GetInverse() const
{
	float det = GetDeterminant();
	if (Abs(det) < EPSILON_EQUAL)
	{
		return Matrix2();
	}
	det = 1.0f / det;

	float entry[4];
	entry[0] = matrixEntry[3] * det;
	entry[2] = -matrixEntry[2] * det;
	entry[1] = -matrixEntry[1] * det;
	entry[3] = matrixEntry[0] * det;

	return Matrix2(entry);
}

Vector2 Matrix2::GetRow(int row) const
{
	Clamp<int>(row, 0, 1);
	return Vector2(matrixEntry[0 + row], matrixEntry[2 + row]);
}

Vector2 Matrix2::GetColumn(int col) const
{
	Clamp<int>(col, 0, 1);
	return Vector2(matrixEntry[col * 2], matrixEntry[col * 2 + 1]);
}

void Matrix2::SetAsIdentity()
{
	*this = Matrix2();
}

void Matrix2::SetRow(int row, const Vector2 & v)
{
	SetRow(row, v.x, v.y);
}

void Matrix2::SetRow(int row, float x, float y)
{
	Clamp<int>(row, 0, 1);
	matrixEntry[row] = x;
	matrixEntry[row + 2] = y;
}

void Matrix2::SetColumn(int col, const Vector2 & v)
{
	SetColumn(col, v.x, v.y);
}

void Matrix2::SetColumn(int col, float x, float y)
{
	Clamp<int>(col, 0, 1);
	matrixEntry[col * 2] = x;
	matrixEntry[col * 2 + 1] = y;
}

void Matrix2::print() const
{
	for (int r = 0; r < 2; r++)
	{
		for (int c = 0; c < 2; c++)
		{
			std::cout << std::setw(4) << matrixEntry[r + c * 3] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix2::~Matrix2()
{
}
