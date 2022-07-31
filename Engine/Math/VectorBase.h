#pragma once

/*
* This is the base class for an N-space Vector. This base class
* contains the vector interface/implementation that is common for all N (all vector sizes).
* The size-specific interface is specified through specializing the derived Vector<N> class.
* 
* To realize this design, we use CRTP (Cursiously Recurring Template Pattern):
* https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
* 
* NOTE: 
* This class cannot be instantiated - use the derived Vector class instead! 
* The sole purpose of this class is to gather the common vector code in one place to allow for generality 
* (the same code works for all vector sizes) and ease of maintenance (code must be changed in one place only). 
* It is not intended to be used for direct manipulation!
*/
template<int N, class VectorDerived>
class VectorBase
{
protected:
  //A static array of N vector elements. It must be visible to derived classes only.
  //Users can access these elements only through a dedicated interface.
  float elements[N];

protected:
    /****************/
   /* CONSTRUCTORS */
  /****************/

  //All base class constructors are defined 'protected' with the following purpose:
  // - to explicitly forbid base class object instantiation;
  // - to make the vector constructor code available to derived classes and at the same time to ensure 
  //that the code exists in one place only.
  // 
  //However, as a consequence of the protected modifier, all custom constructors will be hidden for the users. Thus, derived classes 
  //MUST redeclare EACH of these custom constructors publicly - and explicitly call the hidden base class version from there.
  // 
  //As regards the default and copy constructors, this will probably be done automatically by the compiler but
  //no harm done writing it manually as well.

  //Default constructor. Initialise all elements to zero.
  //NOTE: This base class constructor must be called from the corresponding derived class constructor.
  VectorBase();

  //Copy constructor. Initialise all elements to be equal to the elements of the input vector 'v'.
  //NOTE: This base class constructor must be called from the corresponding derived class constructor.
  VectorBase(const VectorBase& v);

  //Static array constructor. Initialise vector element values from a static array of floating point numbers.
  //NOTE: This base class constructor must be explicitly called from the corresponding derived class constructor.
  //Since this is a custom constructor, its derived-class version MUST be manually declared and made public.
  VectorBase(float arr[N]);


public:
    /************************/
   /* ASSIGNMENT OPERATORS */
  /************************/

  VectorDerived& operator = (const VectorDerived& v);


    /*******************/
   /* UNARY OPERATORS */
  /*******************/

  //Return the n-th vector component, counting from 0.
  //NOTE: Index must be between 0 and N. If index is out of bounds, an assertion is raised.
  float& operator[](int n);

  //Return the n-th vector component of a const vector, counting from 0.
  //NOTE: Index must be between 0 and N. If index is out of bounds, an assertion is raised.
  const float& operator[](int n) const;

  //Negates all vector components.
  //Note that the operator does not modify the existing object, but
  //returns vew Vector object with negated components.
  VectorDerived operator-() const;


    /************************/
   /* ARITHMETIC OPERATORS */
  /************************/

  VectorDerived operator+ (const VectorDerived& v) const;

  //NOTE: The operator modifies the current object.
  VectorDerived& operator+= (const VectorDerived& v);

  VectorDerived operator- (const VectorDerived& v) const;

  //NOTE: The operator modifies the current object.
  VectorDerived& operator-= (const VectorDerived& v);

  VectorDerived operator* (float scalar) const; //Opposite direction, i.e scalar*vector, is handled by a non-member operator.

  //NOTE: The operator modifies the current object.
  VectorDerived& operator*= (float scalar);

  //'scalar' must be different from zero. An assertion is raised otherwise.
  VectorDerived operator/ (float scalar) const;

  //'scalar' must be different from zero. An assertion is raised otherwise.
  //NOTE: The operator modifies the current object.
  VectorDerived& operator/= (float scalar);


    /*********************************/
   /* ADDITIONAL VECTOR ARITHMETICS */
  /*********************************/

  //Calculate the dot product of the current vector and the input vector 'v'.
  float dot(const VectorDerived& v) const;

  //Multiply the current vector by the input vector 'v' componentwise, i.e.
  //x = this.x * x, etc.
  VectorDerived compMult(const VectorDerived& v) const;

  //Divide the current vector by the input vector 'v' componentwise, i.e.
  //x = this.x / x, etc.
  //NOTE: In case any of the components of 'v' are zero, an assertion is raised.
  VectorDerived compDiv(const VectorDerived& v) const;


    /***********/
   /* GETTERS */
  /***********/

  //Calculate the magnitude of the vector.
  float getLength() const;

  //Calculate the squared magnitude of the vector.
  float getLengthSquared() const;

  //Get a vector with unit length pointing in the same direction.
  //NOTE: Vector must be non-zero, otherwise an assertion is raised.
  VectorDerived getNormalized() const;

  //Calculate the distance from the current vector to the input vector 'v'.
  float getDistanceTo(const VectorDerived& v) const;

  //Calculate the squared distance from the current vector to the input vector 'v'.
  float getDistanceSquaredTo(const VectorDerived& v) const;

  //Calculate the angle (in radians) between the current vector and the input vector 'v'.
  float getAngleTo(const VectorDerived& v) const;

  //Calculate the angle (in radians) between the current unit vector and the input unit vector 'v'.
  //ASSUMPTION: Both vectors must be unit vectors, otherwise the results will be incorrect.
  float getAngleToUnit(const VectorDerived& v) const;


    /**************/
   /* PROPERTIES */
  /**************/

  //Check whether the vector is a unit vector (i.e., has a magnitude of 1).
  //NOTE: Compares to length squared. Take in mind when choosing tolerance.
  bool isUnit(float tolerance = EPSILON_NEAR_ZERO_SQUARED) const;

  //Check wheter the vector is equal to another vector (within a given tolerance).
  bool isEqualTo(const VectorDerived& v, float tolerance = EPSILON_EQUAL) const;

  //Check whether the current vector is orthogonal to the input vector 'v'.
  bool isOrthogonalTo(const VectorDerived& v, float tolerance = EPSILON_NEAR_ZERO) const;

  //Check whether the current vector is orthonormal to the input vector 'v', i.e. the two vectors are orthogonal and 
  //are both unit vectors.
  bool isOrthonormalTo(const VectorDerived& v, float tolerance = EPSILON_NEAR_ZERO);

  //Check whether the current vector is parallel to the input vector 'v'.
  bool isParallelTo(const VectorDerived& v, float tolerance = EPSILON_NEAR_ZERO);


    /*************************/
   /* ADDITIONAL OPERATIONS */
  /*************************/

  //Get the projection of this vector onto the unit vector 'v'.
  //Quicker than the ordinary projection function.
  //ASSUMPTION: 'v' must be a unit vector, otherwise the result will be incorrect.
  VectorDerived projectOnToUnit(const VectorDerived& v) const;

  //Get the projection of this vector onto v.
  //NOTE: 'v' must be non-zero vector, otherwise an assertion is raised.
  VectorDerived projectOnTo(const VectorDerived& v) const;

  //Normalize the vector (resize it to a magnitude of 1.0 without changing its direction).
  //NOTE: Function modifies the current vector.
  void normalize();
};

//TODO non-member scalar*vector operator. To be put after Vector<N> declaration.