#pragma once
#include"Math.h"

class Vector3;
class Matrix4;
class Quaternion;

//a 3x3 Matrix
class Matrix3
{
public:
	float matrixEntry[9];

	/* CONSTRUCTORS */

	//The matrix is initialized to the Identity Matrix.
	Matrix3();

	//The matrix entries are initialized to a single value.
	Matrix3(float scalar);

	//The matrix entries are initialized to a set of values. (row0: <m0, m3, m6>, etc.)
	Matrix3(float m0, float m3, float m6, float m1, float m4, float m7, float m2, float m5, float m8);

	//The matrix entries are initialized to an array. (in column-major order)
	Matrix3(float* entries);

	//The columns of the matrix are initialized to a single 3D vector.
	Matrix3(const Vector3& v);

	//The columns of the matrix are initialized to the x, y, and z 3D Vectors (correspondigly).
	Matrix3(const Vector3& x, const Vector3& y, const Vector3& z);

	//The matrix is initialized to another matrix. (Copy constructor)
	Matrix3(const Matrix3& m);

	//The matrix is initialized to a 4x4 matrix with deleted row and column (indices between 0 and 3).
	Matrix3(const Matrix4& m, int row, int col);


	/* ASSIGNMENT OPERATOR */

	Matrix3& operator=(const Matrix3& m);


	/* UNARY OPERATORS */

	Matrix3 operator-() const;
	Vector3& operator[](int i);
	const Vector3& operator[](int i) const;


	/* ARITHMETIC OPERATORS */

	Matrix3 operator+(const Matrix3& m) const;
	Matrix3& operator+=(const Matrix3& m);

	Matrix3 operator-(const Matrix3& m) const;
	Matrix3& operator-=(const Matrix3& m);

	Matrix3 operator*(float scalar) const;
	Matrix3& operator*=(float scalar);

	Matrix3 operator/(float scalar) const;
	Matrix3& operator/=(float scalar);

	Vector3 operator*(const Vector3& v) const;
	Matrix3 operator*(const Matrix3& m) const;
	Matrix3& operator*=(const Matrix3& m);


	/* BOOLEAN OPERATORS */

	bool operator==(const Matrix3& m) const;
	bool operator!=(const Matrix3& m) const;


	/* ADDITIONAL ARITHMETICS */

	//Multiply m1 by m2 componentwise.
	static Matrix3 CompMult(const Matrix3& m1, const Matrix3& m2);

	//Divide m1 by m2 componentwise.
	static Matrix3 CompDiv(const Matrix3& m1, const Matrix3& m2);


	/* PROPERTIES */

	//Check wheter the matrix is equal to another matrix (within a given tolerance).
	bool NearlyEqual(const Matrix3& m, float tolerance = EPSILON_EQUAL) const;


	/* GETTERS */

	float GetDeterminant() const;

	Matrix3 GetTranspose() const;

	Matrix3 GetInverse() const;

	//Get the inverse of a scaling matrix.
	static Matrix3 GetInverseScale(const Matrix3& m);

	//Get the inverse of a pure rotation matrix.
	static Matrix3 GetInverseRotation(const Matrix3& m);

	//Get a row of the matrix (index between 0 and 2).
	Vector3 GetRow(int row) const;

	//Get a column of the matrix (index between 0 and 2).
	Vector3 GetColumn(int col) const;


	/* TRANSFORM MATRICES GENERATION */

	//Generate a matrix that performs scaling by a single factor on all three axis.
	static Matrix3 CreateScale(float scaleFactor);

	//Generate a matrix that performs scaling by different factors on the x, y and z axis.
	static Matrix3 CreateScale(float factorX, float factorY, float factorZ);

	//Generate a matrix that performs scaling by different factors (given as the components of a vector) on the x, y and z axis.
	static Matrix3 CreateScale(const Vector3& scaleFactors);

	//Generate a matrix that peforms scaling by different factors on three arbitrary axis. 
	static Matrix3 CreateScale(float factorX, float factorY, float factorZ, const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ);

	//Generate a matrix that performs scaling by different factors (given as the components of a vector) on three arbitrary axis.
	static Matrix3 CreateScale(const Vector3& scaleFactors, const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ);

	//Generate a matrix that performs a rotation by a given angle(in radians) about an arbitrary axis (defined by the x, y and z parameters).
	static Matrix3 CreateRotation(float angle, float x, float y, float z);

	//Generate a matrix that performs a rotation by a given angle(in radians) about an arbitrary axis.
	static Matrix3 CreateRotation(float angle, const Vector3& axis);

	//Convert a quaternion to a rotation matrix.
	static Matrix3 CreateRotation(Quaternion& q);
	

	/* SETTERS */

	//Set the matrix as the Identity matrix (main diagonal entries equal 1, all other - 0).
	void SetAsIdentity();

	//Set a row of the matrix (index between 0 and 2).
	void SetRow(int row, const Vector3& v);

	//Set a row of the matrix (index between 0 and 2).
	void SetRow(int row, float x, float y, float z);

	//Set a column of the matrix (index between 0 and 2).
	void SetColumn(int col, const Vector3& v);

	//Set a column of the matrix (index between 0 and 2).
	void SetColumn(int col, float x, float y, float z);

	//TODO Remove or make it print to log
	void Print() const;


	~Matrix3();
};