#pragma once
#include"Math.h"
#include"Vector3.h"

class Vector4;
class Matrix3;
class Matrix2;
class Quaternion;

//A 4x4 matrix
class Matrix4
{
public:
	float matrixEntry[16];

	/* CONSTRUCTORS */

	//The matrix is initialized to the Identity Matrix.
	Matrix4();

	//The matrix entries are initialized to a single value.
	Matrix4(float scalar);

	//The matrix entries are initialized to a set of values. (row0: <m0, m4, m8, m12>, etc.)
	Matrix4(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15);

	//The matrix entries are initialized to an array. (in column-major order)
	Matrix4(float* entries);

	//The columns of the matrix are initialized to a single 4D vector.
	Matrix4(const Vector4& v);

	//The columns of the matrix are initialized to the x, y, z, and w 4D Vectors (correspondigly).
	Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w);

	//A 3x3 matrix is used to initialize a rotaion 4x4 matrix.
	Matrix4(const Matrix3& m);

	//A 3x3 matrix and a 3D vector are used to initialize a rotation + translation 4x4 matrix.
	Matrix4(const Matrix3& m, const Vector3& v);

	//The matrix is initialized to another matrix. (Copy constructor)
	Matrix4(const Matrix4& m);


	/* ASSIGNMENT OPERATOR */

	Matrix4& operator=(const Matrix4& m);


	/* UNARY OPERATORS */

	Matrix4 operator-() const;
	Vector4& operator[](int i);
	const Vector4& operator[](int i) const;


	/* ARITHMETIC OPERATORS */

	Matrix4 operator+(const Matrix4& m) const;
	Matrix4& operator+=(const Matrix4& m);

	Matrix4 operator-(const Matrix4& m) const;
	Matrix4& operator-=(const Matrix4& m);

	Matrix4 operator*(float scalar) const;
	Matrix4& operator*=(float scalar);

	Matrix4 operator/(float scalar) const;
	Matrix4& operator/=(float scalar);

	Vector4 operator*(const Vector4& v) const;
	Matrix4 operator*(const Matrix4& m) const;
	Matrix4& operator*=(const Matrix4& m);


	/* BOOLEAN OPERATORS */

	bool operator==(const Matrix4& m) const;
	bool operator!=(const Matrix4& m) const;


	/* ADDITIONAL ARITHMETICS */

	//Multiply m1 by m2 componentwise.
	static Matrix4 CompMult(const Matrix4& m1, const Matrix4& m2);

	//Divide m1 by m2 componentwise.
	static Matrix4 CompDiv(const Matrix4& m1, const Matrix4& m2);


	/* PROPERTIES */

	//Check wheter the matrix is equal to another matrix (within a given tolerance).
	bool NearlyEqual(const Matrix3& m, float tolerance = EPSILON_EQUAL) const;


	/* GETTERS */

	float GetDeterminant() const;

	Matrix4 GetTranspose() const;

	Matrix4 GetInverse() const;

	Matrix3 GetRotation() const;

	Vector3 GetTranslation() const;

	//Get the inverse of a scaling matrix.
	static Matrix4 GetInverseScale(const Matrix4& m);

	//Get the inverse of a pure rotation matrix.
	static Matrix4 GetInverseRotation(const Matrix4& m);

	//Get the inverse of a pure translation matrix.
	static Matrix4 GetInverseTranslatoin(const Matrix4& m);

	//Get a row of the matrix (index between 0 and 3).
	Vector4 GetRow(int row) const;

	//Get a column of the matrix (index between 0 and 3).
	Vector4 GetColumn(int col) const;


	/* TRANSFORM MATRICES GENERATION */

	//Generate a matrix that performs scaling by a single factor on all three axis.
	static Matrix4 CreateScale(float scaleFactor);

	//Generate a matrix that performs scaling by different factors on the x, y and z axis.
	static Matrix4 CreateScale(float factorX, float factorY, float factorZ);

	//Generate a matrix that performs scaling by different factors (given as the components of a vector) on the x, y and z axis.
	static Matrix4 CreateScale(const Vector3& scaleFactors);

	//Generate a matrix that peforms scaling by different factors on three arbitrary axis. 
	static Matrix4 CreateScale(float factorX, float factorY, float factorZ, const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ);

	//Generate a matrix that performs scaling by different factors (given as the components of a vector) on three arbitrary axis.
	static Matrix4 CreateScale(const Vector3& scaleFactors, const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ);

	//Generate a matrix that performs a rotation by a given angle(in radians) about an arbitrary axis (defined by the x, y, and z parameters).
	static Matrix4 CreateRotation(float angle, float x, float y, float z);

	//Generate a matrix that performs a rotation by a given angle(in radians) about an arbitrary axis.
	static Matrix4 CreateRotation(float angle, const Vector3& axis);

	//Convert a quaternion to a rotation matrix.
	static Matrix4 CreateRotataion(Quaternion& q);

	//Generate a matrix that performs a translation (the translation vector is defined by the x, y, and z parameters).
	static Matrix4 CreateTranslation(float x, float y, float z);

	//Generate a matrix that performs a translation by the given vector.
	static Matrix4 CreateTranslation(const Vector3& v);


	/*Generate a look-at matrix.
	Takes as parameters the Camera Position, the Point of Interest (towards which the camera is looking), and some up direction.*/
	static Matrix4 CreateLookAt(const Vector3& cameraPos, const Vector3& POI, const Vector3& up = Vector3(0.0f, 1.0f, 0.0f));

	/*Generate a perspective projection matrix.
	Takes as parameters the distances to the left, right, top, and bottom edges of the rectangle carved out of the near plane
	by the four side planes of the frustum (measured from the centre of the rectangle), as well as the distances to the near and far frustum planes. */
	static Matrix4 CreateProjPersp(float left, float right, float top, float bottom, float near, float far);

	/*Generate a perspective projection matrix (where the far frustum plane is infinitely far away).
	Takes as parameters the distances to the left, right, top, and bottom edges of the rectangle carved out of the near plane
	by the four side planes of the frustum (measured from the centre of the rectangle), as well as the distance to the near frustum plane. */
	static Matrix4 CreateProjPerspInfinite(float left, float right, float top, float bottom, float near);

	/*Generate a perspective projection matrix (of a symmetric frustum).
	Takes as parameters the vertical Field of View angle (radians), the viewport Aspect Ratio, and the distances to the near and far frustum planes. */
	static Matrix4 CreateProjPerspSymmetric(float fovY, float aspectRatio, float near, float far);

	/*Generate an orthographic projection matrix.
	Takes as parameters the distances to the left, right, top, and bottom edges of the rectangle carved out of the near plane
	by the four side planes of the frustum (measured from the centre of the rectangle), as well as the distances to the near and far frustum planes. */
	static Matrix4 CreateProjOrthographic(float left, float right, float top, float bottom, float near, float far);


	/* SETTERS */

	//Set the matrix as the Identity matrix (main diagonal entries equal 1, all other - 0).
	void SetAsIdentity();

	//Set a row of the matrix (index between 0 and 3).
	void SetRow(int row, const Vector4& v);

	//Set a row of the matrix (index between 0 and 3).
	void SetRow(int row, float x, float y, float z, float w);

	//Set a column of the matrix (index between 0 and 3).
	void SetColumn(int col, const Vector4& v);

	//Set a column of the matrix (index between 0 and 3).
	void SetColumn(int col, float x, float y, float z, float w);

	//TODO Remove or make it print to log
	void Print() const;


	~Matrix4();
};