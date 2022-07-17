#pragma once

/*
* This is the base class for an N-space Vector. This base class
* contains the vector interface/implementation that is common for all N (all vector sizes).
* The size-specific interface is specified through specializing the derived Vector class.
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
template<int N, class Derived>
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

  //All base class constructors are defined protected with the following purpose:
  // - to explicitly forbid base class object instantiation;
  // - to make the vector constructor code available to derived classes and at the same time to ensure 
  //that the code exists in one place only.
  // 
  //However, as a consequence of the protected modifier, all custom constructors will be hidden for the users. Thus, derived classes 
  //MUST redeclare EACH of these custom constructors publicly - and explicitly call the hidden base class version from there.
  // 
  //As regards the default and copy constructors, this will probably be done automatically by the compiler but
  //no harm done writing it manually as well.

  //Default constructor. Initialises all elements to zero.
  //NOTE: This base class constructor must be explicitly called from the corresponding derived class constructor.
  VectorBase();

  //Copy constructor. Initialises all elements to be equal to the elements of the input vector 'v'.
  //NOTE: This base class constructor must be explicitly called from the corresponding derived class constructor.
  VectorBase(const VectorBase& v);

  //Static array constructor. Takes all vector element values from a static array of floating point numbers.
  //NOTE: This base class constructor must be explicitly called from the corresponding derived class constructor.
  //Furthermore, this is a custom constructor, so its derived-class version MUST be manually declared inside the derived class.
  VectorBase(float arr[N]);


};
