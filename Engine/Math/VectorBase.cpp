#include"VectorBase.h"

template<int N, class Derived>
VectorBase<N, Derived>::VectorBase()
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = 0.0f;
  }
}

template<int N, class Derived>
VectorBase<N, Derived>::VectorBase(const VectorBase& v)
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = v.elements[i];
  }
}

template<int N, class Derived>
VectorBase<N, Derived>::VectorBase(float arr[N])
{
  for (int i = 0; i < N; i++)
  {
    elements[i] = arr[i];
  }
}
