#include"VectorBase.h"
#include"Math.h"
#include<assert.h>

template<int N, class VectorDerived>
VectorBase<N, VectorDerived>::VectorBase()
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = 0.0f;
  }
}

template<int N, class VectorDerived>
VectorBase<N, VectorDerived>::VectorBase(const VectorBase& v)
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = v.elements[i];
  }
}

template<int N, class VectorDerived>
VectorBase<N, VectorDerived>::VectorBase(float arr[N])
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = arr[i];
  }
}

template<int N, class VectorDerived>
VectorDerived& VectorBase<N, VectorDerived>::operator=(const VectorDerived& v)
{
  for (int i = 0; i < N; i++)
  {
    this->elements[i] = v.elements[i];
  }

  return static_cast<Derived&>(*this));
}

template<int N, class VectorDerived>
float& VectorBase<N, VectorDerived>::operator[](int n)
{
  assert(n >= 0 && n < N);

  return elements[n];
}

template<int N, class VectorDerived>
const float& VectorBase<N, VectorDerived>::operator[](int n) const
{
  assert(n >= 0 && n < N);

  return elements[n];
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::operator-() const
{
  //copy ctor
  VectorDerived v(*this);

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    //Negate every element.
    v.elements[i] = -v.elements[i];
  }

  return v;
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::operator+(const VectorDerived& v) const
{
  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] + v.elements[i];
  }
  return result;
}

template<int N, class VectorDerived>
VectorDerived& VectorBase<N, VectorDerived>::operator+=(const VectorDerived& v)
{
  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    this->elements[i] += v.elements[i];
  }
  return static_cast<VectorDerived&>(*this);
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::operator-(const VectorDerived& v) const
{
  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] - v.elements[i];
  }
  return result;
}

template<int N, class VectorDerived>
VectorDerived& VectorBase<N, VectorDerived>::operator-=(const VectorDerived& v)
{
  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    this->elements[i] += v.elements[i];
  }
  return static_cast<VectorDerived&>(*this);
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::operator*(float scalar) const
{
  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] * scalar;
  }
  return result;
}

template<int N, class VectorDerived>
VectorDerived& VectorBase<N, VectorDerived>::operator*=(float scalar)
{
  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    this->elements[i] *= scalar;
  }
  return static_cast<VectorDerived&>(*this);
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::operator/(float scalar) const
{
  assert(!NearlyZero(scalar));

  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] / scalar;
  }
  return result;
}

template<int N, class VectorDerived>
VectorDerived& VectorBase<N, VectorDerived>::operator/=(float scalar)
{
  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    this->elements[i] /= scalar;
  }
  return static_cast<VectorDerived&>(*this);
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::dot(const VectorDerived& v) const
{
  float dotProduct = 0.0;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    dotProduct += this->elements[i] * v.elements[i];
  }

  return dotProduct;
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::compMult(const VectorDerived& v) const
{
  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] * v.elements[i];
  }
  return result;
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::compDiv(const VectorDerived& v) const
{
  //Check for zero elements in v.
  for (int i = 0; i < N; i++)
  {
    assert(!NearlyZero(v.elements[i]));
  }

  //Default ctor
  VectorDerived result;

  //Interface of VectorDerived implicitly declared
  for (int i = 0; i < N; i++)
  {
    result.elements[i] = this->elements[i] / v.elements[i];
  }
  return result;
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getLength() const
{
  return Sqrt(this->getLength());
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getLengthSquared() const
{
  return this->dot(*this);
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::getNormalized() const
{
  float length = getLength();
  assert(!NearlyZero(length));
  return *this / length;
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getDistanceTo(const VectorDerived& v) const
{
  return (v - static_cast<VectorDerived&>(*this)).getLength();
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getDistanceSquaredTo(const VectorDerived& v) const
{
  return (v - static_cast<VectorDerived&>(*this)).getLengthSquared();
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getAngleTo(const VectorDerived& v) const
{
  //By properties of the dot product:
  //	a dot b = len(a) * len(b) * cos(angle)
  //Ensuring normal vectors, we have:
  //	angle = acos(a dot b)

  VectorDerived a = this->getNormalized();
  VectorDerived b = v.getNormalized();

  return Acos(a.dot(b));
}

template<int N, class VectorDerived>
float VectorBase<N, VectorDerived>::getAngleToUnit(const VectorDerived& v) const
{
  //In case of unit vectors, we can avoid calculating the length (eq to 1.0).
  return Acos(this->dot(v));
}

template<int N, class VectorDerived>
bool VectorBase<N, VectorDerived>::isUnit(float tolerance) const
{
  //Here we use the squared length to avoid costly sqrt operation.
  //The difference in the result is negligible, but to nevertheless account for the change,
  //we use double tolerance (encoded in the constant itself).
  return NearlyZero(getLengthSquared() - 1.0f, tolerance);
}

template<int N, class VectorDerived>
bool VectorBase<N, VectorDerived>::isEqualTo(const VectorDerived& v, float tolerance) const
{
  for (int i = 0; i < N; i++)
  {
    if (!NearlyZero(elements[i] - v.elements[i])) //The i-th element of *this and of 'v' are different.
      return false;
  }
  return true;
}

template<int N, class VectorDerived>
bool VectorBase<N, VectorDerived>::isOrthogonalTo(const VectorDerived& v, float tolerance) const
{
  //The two vectors are orthogonal if their dot prouct is zero.
  //We perform the comparison with some tolerance to account for floating point error.
  float dotProd = this->dot(v);
  return NearlyZero(dotProd, tolerance);
}

template<int N, class VectorDerived>
bool VectorBase<N, VectorDerived>::isOrthonormalTo(const VectorDerived& v, float tolerance)
{
  //Two vectors are orthonormal if they are orthogonal and they are both unit vectors.
  return (this->isOrthogonalTo(v, tolerance) && this->isUnit() && v.isUnit());
}

template<int N, class VectorDerived>
bool VectorBase<N, VectorDerived>::isParallelTo(const VectorDerived& v, float tolerance)
{
  //Assuming the angle between the two vectors is 'alpha', then the two vectors are parallel when cos(alpha)=1.
  //Therefore, |a dot b| = len(a) * len (b)
  //We perform the comparison with some tolerance to account for floating point error.
  float absDotProd = Abs(this->dot(v));
  float lengthProd = this->getLength() * v.getLength();
  return NearlyZero(absDotProd - lengthProd, tolerance);
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::projectOnToUnit(const VectorDerived& v) const
{
  //Assuming unit length vectors, projection formula becomes:
  //proj_a_onto_b = proj_length * b = a.dot(b) * b
  return v * (this->dot(v));
}

template<int N, class VectorDerived>
VectorDerived VectorBase<N, VectorDerived>::projectOnTo(const VectorDerived& v) const
{
  //Projection formula:
  //proj_a_onto_b = proj_length * b_unit = a.dot(b/len(b)) * b/len(b) = a.dot(b) * b/(len(b)^2)

  float lengthSq = v.getLengthSquared();
  //In case of zero vector, an assertion is raised.
  //Note the use of the appropriate constant for comparison with length squared.
  assert(!NearlyZero(lengthSq, EPSILON_NEAR_ZERO_SQUARED));

  return v * (this->dot(v) / (lengthSq));
}

template<int N, class VectorDerived>
void VectorBase<N, VectorDerived>::normalize()
{
  *this = this->getNormalized();
}

