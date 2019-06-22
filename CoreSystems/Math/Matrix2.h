#pragma once
#include"Math.h"

class Matrix3;
class Vector2;

//a 2x2 Matrix
class Matrix2
{
public:
	float matrixEntry[4];

	/* CONSTRUCTORS */

	//The matrix is initialized to the Identity Matrix.
	Matrix2();

	//The matrix entries are initialized to a single value.
	Matrix2(float scalar);

	//The matrix entries are initialized to a set of values. (row0: <m0, m2>; row1: <m1, m3>)
	Matrix2(float m0, float m2, float m1, float m3);

	//The matrix entries are initialized to an array. (in column-major order)
	Matrix2(float* entries);

	//The columns of the matrix are initialized to a single 2D vector.
	Matrix2(const Vector2& v);

	//The columns of the matrix are initialized to the x and y 2D Vectors (correspondingly).
	Matrix2(const Vector2& x, const Vector2& y);

	//The matrix is initialized to another matrix. (Copy constructor)
	Matrix2(const Matrix2 & m);

	//The matrix is initialized to a 3x3 matrix with deleted row and column (indices between 0 and 2).
	Matrix2(const Matrix3& m, int row, int col);


	/* ASSIGNMENT OPERATOR */

	Matrix2& operator=(const Matrix2& m);


	/* UNARY OPERATORS */

	Matrix2 operator-() const;
	Vector2& operator[](int i);
	const Vector2& operator[](int i) const;


	/* ARITHMETIC OPERATORS */

	Matrix2 operator+(const Matrix2& m) const;
	Matrix2& operator+=(const Matrix2& m);

	Matrix2 operator-(const Matrix2& m) const;
	Matrix2& operator-=(const Matrix2& m);

	Matrix2 operator*(float scalar) const;
	Matrix2& operator*=(float scalar);

	Matrix2 operator/(float scalar) const;
	Matrix2& operator/=(float scalar);

	Vector2 operator*(const Vector2& v) const;
	Matrix2 operator*(const Matrix2& m) const;
	Matrix2& operator*=(const Matrix2& m);


	/* BOOLEAN OPERATORS */

	bool operator==(const Matrix2& m) const;
	bool operator!=(const Matrix2& m) const;


	/* ADDITIONAL ARITHMETICS */

	//Multiply m1 by m2 componentwise.
	static Matrix2 CompMult(const Matrix2& m1, const Matrix2& m2);

	//Divide m1 by m2 componentwise.
	static Matrix2 CompDiv(const Matrix2& m1, const Matrix2& m2);


	/* PROPERTIES */

	//Check wheter the matrix is equal to another matrix (within a given tolerance).
	bool NearlyEqual(const Matrix3& m, float tolerance = EPSILON_EQUAL) const;


	/* GETTERS */

	float GetDeterminant() const;

	Matrix2 GetTranspose() const;

	Matrix2 GetInverse() const;

	//Get a row of the matrix (index between 0 and 1).
	Vector2 GetRow(int row) const;

	//Get a column of the matrix (index between 0 and 1).
	Vector2 GetColumn(int col) const;


	/* SETTERS */

	//Set the matrix as the Identity matrix (main diagonal entries equal 1, all other - 0).
	void SetAsIdentity();

	//Set a row of the matrix (index between 0 and 1).
	void SetRow(int row, const Vector2& v);

	//Set a row of the matrix (index between 0 and 1).
	void SetRow(int row, float x, float y);

	//Set a column of the matrix (index between 0 and 1).
	void SetColumn(int col, const Vector2& v);

	//Set a column of the matrix (index between 0 and 1).
	void SetColumn(int col, float x, float y);

	//TODO Remove or make it print to log
	void Print() const;


	~Matrix2();
};
