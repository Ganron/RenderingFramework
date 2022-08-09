#pragma once
#include"VectorBase.h"
#include<assert.h>

// A vector of arbitrary size N. The interface that is common for all vector sizes is derived from VectorBase.
// The specialised interface for vectors of size 2, 3, and 4 is achieved through template specialization.
template <int N>
class Vector : public VectorBase<N, Vector<N>>
{
  //inherits the 'float elements[N]' data member
  
public:
    //--------------//
   // CONSTRUCTORS //
  //--------------//

  //Default constructor. Initialise all elements to zero.
  Vector() {};
  
  //Static array constructor. Initialise the vector elements from a static array of floating point numbers.
  Vector(float arr[N]) : VectorBase<N,Vector<N>>(arr) {}

  //Copy constructor. Initialise all elements to be equal to the elements of the input vector 'v'.
  Vector(const Vector& v) : VectorBase<N,Vector<N>>(v) {}

  //Generic constructor for constructing the vector out of two smaller vectors.
  //Requirement: the dimension of 'v1' + the dimension of 'v2' must be equal to N.
  //e.g. Vector<5>(Vector<2> v1, Vector<3> v2) - here a vector of size 5 is initialised out of
  //a 2-size and 3-size vector. The elements of v1 come before the elements of v2.
  template<int M>
  Vector(const Vector<M>& v1, const Vector<N - M>& v2);
};

//Definition
template<int N>
template<int M>
Vector<N>::Vector(const Vector<M>& v1, const Vector<N - M>& v2)
{
  assert(M < N);
  //First M elements come from v1.
  for (int i = 0; i < M; i++)
  {
    this->elements[i] = v1[i];
  }

  //The rest of the elements come from v2.
  for (int i = 0; i < N - M; i++)
  {
    this->elements[i + M] = v2[i];
  }
}

//Non-member operator for scalar * vector multiplication
template<int N>
Vector<N> operator*(float scalar, const Vector<N>& v)
{
  return v * scalar;
}


// Specialised interface for a vector of size 1, i.e. a scalar.
template<>
class Vector<1> : public VectorBase<1, Vector<1>>
{
  //inherits a 'float elements[1]' data member

public:
  //Default constructor. Initialise to 0.
  Vector<1>() {}

  //Initialise to a scalar.
  Vector<1>(float scalar) {}

  //Copy constructor.
  Vector<1>(const Vector<1>& v) : VectorBase<1,Vector<1>>(v) {}

  //Conversion to float.
  operator float() const { return this->elements[0]; }
};



// Specialised interface for a vector of size 2.
// Here we call the two vector elements 'x' and 'y'.
template<>
class Vector<2> : public VectorBase<2, Vector<2>>
{
  //inherits a 'float elements[2]' data member

public:
    //--------------//
   // CONSTRUCTORS //
  //--------------//

  //Default constructor. Initialise all elements to zero.
  Vector<2>() {}

  //Static array constructor. Initialise the vector elements from a static array of 2 floating point numbers.
  Vector<2>(float arr[2]) : VectorBase<2,Vector<2>>(arr) {}

  //Initialise all the 'x' and 'y' vector elements separately.
  Vector<2>(float inX, float inY)
  {
    this->elements[0] = inX;
    this->elements[1] = inY;
  }

  //Copy constructor. Initialise all elements to be equal to the elements of the input vector 'v'.
  Vector<2>(const Vector<2>& v) : VectorBase<2,Vector<2>>(v) {}


    //---------------//
   // MEMBER ACCESS //
  //---------------//

  float x() const { return this->elements[0]; }
  float y() const { return this->elements[1]; }
};


 // Specialised interface for a vector of size 3.
 // Here we call the three vector elements 'x', 'y', and 'z'.
template<>
class Vector<3> : public VectorBase<3, Vector<3>>
{
  //inherits a 'float elements[3]' data member

public:
    //--------------//
   // CONSTRUCTORS //
  //--------------//

  //Default constructor. Initialise all elements to zero.
  Vector<3>() {}

  //Static array constructor. Initialise the vector elements from a static array of 2 floating point numbers.
  Vector<3>(float arr[3]) : VectorBase<3,Vector<3>>(arr) {}

  //Initialise all the 'x', 'y', and 'z' vector elements separately.
  Vector<3>(float inX, float inY, float inZ)
  {
    this->elements[0] = inX;
    this->elements[1] = inY;
    this->elements[2] = inZ;
  }

  //Initialize the components of the vector to an x value and a 2D vector.
  //Vector initialized to: <inX, inYZ> = <inX, inYZ.x(), inYZ.y()>
  Vector<3>(float inX, const Vector<2>& inYZ)
  {
    this->elements[0] = inX;
    this->elements[1] = inYZ[0];
    this->elements[2] = inYZ[1];
  }

  //Initialize the components of the vector to a 2D vector and a z value.
  //Vector initialized to: <inXY, inZ> = <inXY.x(), inXY.y(), inZ>
  Vector<3>(const Vector<2>& inXY, float inZ)
  {
    this->elements[0] = inXY[0];
    this->elements[1] = inXY[1];
    this->elements[2] = inZ;
  }

  //Copy constructor. Initialise all elements to be equal to the elements of the input vector 'v'.
  Vector<3>(const Vector<3>& v) : VectorBase<3,Vector<3>>(v) {}

    //---------------//
   // MEMBER ACCESS //
  //---------------//

  float x() const { return this->elements[0]; }
  float y() const { return this->elements[1]; }
  float z() const { return this->elements[2]; }
  //Get a 2D vector, composed of the x and y components of the current vector.
  Vector<2> xy() const { return Vector<2>{x(), y()}; }
  //Get a 2D vector, composed of the y and z coponents of the current vector.
  Vector<2> yz() const { return Vector<2>{y(), z()}; }


    //------------//
   // ADDITIONAL //
  //------------//

  //Calculate the cross product of the current vector and the input vector 'v'.
  Vector<3> cross(const Vector<3>& v) const
  {
    return Vector<3>(
      y() * v.z() - z() * v.y(),
      z() * v.x() - x() * v.z(),
      x() * v.y() - y() * v.x());
  }
};


 // Specialised interface for a vector of size 4.
 // Here we call the three vector elements 'x', 'y', 'z', and 'w'.
template<>
class Vector<4> : public VectorBase<4, Vector<4>>
{
  //inherits a 'float elements[4]' data member

public:
    //--------------//
   // CONSTRUCTORS //
  //--------------//

  //Default constructor. Initialise all elements to zero.
  Vector<4>() {}

  //Static array constructor. Initialise the vector elements from a static array of 2 floating point numbers.
  Vector<4>(float arr[4]) : VectorBase<4,Vector<4>>(arr) {}

  //Initialise all the 'x', 'y', 'z', and 'w' vector elements separately.
  Vector<4>(float inX, float inY, float inZ, float inW = 1.0f)
  {
    this->elements[0] = inX;
    this->elements[1] = inY;
    this->elements[2] = inZ;
    this->elements[3] = inW;
  }

  //Copy constructor. Initialise all elements to be equal to the elements of the input vector 'v'.
  Vector<4>(const Vector<4>& v) : VectorBase<4,Vector<4>>(v) {}

  //Initialize the components of the vector to a 3D vector and a w value.
  //Vector initialized to: <inXYZ, inW> = <inXYZ.x(), inXYZ.y(), inXYZ.z(), inW>
  explicit Vector<4>(const Vector<3>& inXYZ, float inW = 1.0f)
  {
    this->elements[0] = inXYZ[0];
    this->elements[1] = inXYZ[1];
    this->elements[2] = inXYZ[2];
    this->elements[3] = inW;
  }

  //Initialize the components of the vector to an x value and a 3D vector.
  //Vector initialized to: <inX, inYZW> = <inX, inYZW.x(), inYZW.y(), inYZW.z()>
  Vector<4>(float inX, const Vector<3>& inYZW)
  {
    this->elements[0] = inX;
    this->elements[1] = inYZW[0];
    this->elements[2] = inYZW[1];
    this->elements[3] = inYZW[2];
  }

  //Initialize the components of the vector to two 2D vectors.
  //Vector initialized to: <inXY, inZW> = <inXY.x(), inXY.y(), inZW.x(), inZW.y()>
  Vector<4>(const Vector<2>& inXY, const Vector<2>& inZW)
  {
    this->elements[0] = inXY[0];
    this->elements[1] = inXY[1];
    this->elements[2] = inZW[0];
    this->elements[3] = inZW[1];
  }

  //Initialize the components of the vector to a 2D vector, a z value, and a w value.
  //Vector initialized to: <inXY, inZ, inW> = <inXY.x(), inXY.y(), inZ, inW>
  Vector<4>(const Vector<2>& inXY, float inZ, float inW)
  {
    this->elements[0] = inXY[0];
    this->elements[1] = inXY[1];
    this->elements[2] = inZ;
    this->elements[3] = inW;
  }

  //Initialize the components of the vector to an x value, a 2D vector, and a w value.
  //Vector initialized to: <inX, inYZ, inW> = <inX, inYZ.x(), inYZ.y(), inW>
  Vector<4>(float inX, const Vector<2>& inYZ, float inW)
  {
    this->elements[0] = inX;
    this->elements[1] = inYZ[0];
    this->elements[2] = inYZ[1];
    this->elements[3] = inW;
  }

  //Initialize the components of the vector to an x value, a y value, and a 2D vector.
  //Vector initialized to: <inX, inY, inZW> = <inX, inY, inZW.x(), inZW.y()>
  Vector<4>(float inX, float inY, const Vector<2>& inZW)
  {
    this->elements[0] = inX;
    this->elements[1] = inY;
    this->elements[2] = inZW[0];
    this->elements[3] = inZW[1];
  }


    //---------------//
   // MEMBER ACCESS //
  //---------------//

  float x() const { return this->elements[0]; }
  float y() const { return this->elements[1]; }
  float z() const { return this->elements[2]; }
  float w() const { return this->elements[3]; }

  //Get a 2D vector, composed of the x and y components of the current vector.
  Vector<2> xy() const { return Vector<2>{x(), y()}; }

  //Get a 2D vector, composed of the y and z components of the current vector.
  Vector<2> yz() const { return Vector<2>{y(), z()}; }

  //Get a 2D vector, composed of the z and w components of the current vector.
  Vector<2> zw() const { return Vector<2>{z(), w()}; }

  //Get a 3D vector, composed of the x, y, and z components of the current vector.
  Vector<3> xyz() const { return Vector<3>{x(), y(), z()}; }

  //Get a 3D vector, composed of the y, z, and w components of the current vector.
  Vector<3> yzw() const { return Vector<3>{y(), z(), w()}; }

};

//TYPEDEFS
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;