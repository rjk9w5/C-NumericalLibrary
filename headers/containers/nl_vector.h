/*
 * vector.h
 *
 *  Created on: Feb 5, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Declarations of vector template class and associated
 *              friend functions
 */

/*
 *       class: vector
 *       brief: Template class of an array with automatic memory management.
 */

/*
 *    function: vector()
 *       brief: Default constructor.
 *         pre: None
 *        post: Construct an vector object.
 *      return: None
 */

/*
 *    function: vector(const size_t size)
 *       brief: Constructs an vector of input size.
 *         pre: size must be greater than or equal to 0
 *        post: Constructs an vector of input size.
 *       param: size is an size_t type.
 *      return: None
 */

/*
 *    function: vector(const size_t size, const T& value)
 *       brief: Size and value constructor.
 *         pre: size must be greater than or equal to 0
 *        post: Constructs an vector of input size with all cells of input
 *              value.
 *       param: size is an size_t type.
 *       param: value is a T type.
 *      return: None
 */

/*
 *    function: vector(const vector<T>& src)
 *       brief: Copy constructor
 *         pre: None
 *        post: Constructs an vector object with same values
 *              found in input.
 *       param: vector object to be copied size_to new vector.
 *      return:
 */

/*
 *    function: vector(vector<T>&& other)
 *       brief: Move constructor
 *         pre: None
 *        post: Moves memory for a new vector object from input.
 *       param: vector object to be moved size_to new vector.
 *      return: None
 */

/*
 *    function: operator=(const vector<T>& src)
 *       brief: Copy assignment operator.
 *         pre: none
 *        post: Copies data from src to calling object.
 *       param: src is an vector type.
 *      return: calling object.
 */

/*
 *    function: operator=(vector<T>&& other)
 *       brief: Move assignment operator.
 *         pre: None
 *        post: Moves data from other to calling object.
 *       param: other is an vector type.
 *      return: calling object.
 */

/*
 *    function: ~vector()
 *       brief: Destructor
 *         pre: None
 *        post: Destroys vector object.
 */

/*
 *    function: resize(const size_t size)
 *       brief: Resizes vector while only destroying data in cells with
 *              indices greater than the new size.
 *         pre: size must be greater than or equal to 0
 *        post: Resizes vector but saves data.
 *       param: size to resize to, default=0. (size_t)
 *      return: none
 */

/*
 *    function: reuse(const size_t size)
 *       brief: destroys all existing data and applies a new size.
 *         pre: size must be greater than or equal to 0
 *        post: destroys all existing data and applies a new size.
 *       param: size to resize to, default=0. (size_t)
 *      return: none
 */

/*
 *    function: set_size(const size_t size)
 *       brief: destroys all existing data and sets new size.
 *         pre: size must be greater than or equal to 0
 *        post: destroys all existing data and sets new size.
 *       param: size to resize to. (size_t)
 *      return: none
 */

/*
 *    function: get_size()
 *       brief: returns size.
 *         pre: none
 *        post: returns size.
 *      return: size of vector calling object. (size_t)
 */

/*
 *    function: remove(const size_t i)
 *       brief: removes value at index i if it exists.
 *         pre: size must be greater than or equal to 0 and i must be less than
 *              the size of the calling vector object.
 *        post: value at index i is removed and data is shifted.
 *       param: index i to be removed.
 *      return: none
 */

/*
 *    function: operator[](const size_t i) const
 *       brief: read only access element at index i
 *         pre: size must be greater than or equal to 0 and i must be less than
 *              the size of the calling vector object.
 *        post: returns element value at index i
 *       param: index i to be accessed
 *      return: returns element value at index i
 */

/*
 *    function: operator[](const size_t i)
 *       brief: read-write access element at index i
 *         pre: size must be greater than or equal to 0 and i must be less than
 *              the size of the calling vector object.
 *        post: returns element value at index i
 *       param: index i to be accessed
 *      return: returns element value at index i
 */

/*
 *    function: sort()
 *       brief: Sorts vector calling object
 *         pre: Requires template type T to have < operator implemented for use
 *              of std::sort
 *        post: Sorts vector
 *      return: none
 */

/*
 *    function: cat()
 *       brief: concatenates two vectors
 *         pre: Both vectors must be of the same element type
 *        post: <Vector1, Vector2> is returned
 *       param: Vector on left side of concatenation
 *       param: Vector on right side of concatenation
 *      return: The concatenated vector
 */

/*
 *    function: dot()
 *       brief: Computes the inner product (dot product) of two input vectors
 *         pre: Both vectors must be of the same size.
 *        post: Scalar value of dot product is computed
 *       param: A vector of size 'n'
 *       param: A vector of size 'n'
 *      return: The scalar dot product of two vectors
 */

/*
 *    function: operator == ()
 *       brief: Check equality of two vectors
 *         pre: Both vectors must be of the same size.
 *        post: Returns true if the two vectors are equal.
 *       param: A vector of size 'n'
 *       param: A vector of size 'n'
 *      return: Returns true if the two vectors are equal.
 */

/*
 *    function: operator != (vector, vector)
 *       brief: Check inequality of two vectors
 *         pre: Both vectors must be of the same size.
 *        post: Returns true if the two vectors are not equal.
 *       param: A vector of size 'n'
 *       param: A vector of size 'n'
 *      return: Returns true if the two vectors are not equal.
 */

/*
 *    function: operator - (vector - vector)
 *       brief: Difference between two vectors
 *         pre: Vectors must be of same size.
 *        post: Computes difference between two vectors
 *       param: A vector of size 'n'
 *       param: A vector of size 'n'
 *      return: The vector that is the difference between input vectors
 */

/*
 *    function: operator - (vector -= vector)
 *       brief: Difference between two vectors
 *         pre: Vectors must be of same size.
 *        post: Computes difference between two vectors
 *       param: A vector of size 'n'
 *      return: The difference between vectors as the calling vector
 */

/*
 *    function: operator - (-vector)
 *       brief: Negation of the input vector
 *         pre: None
 *        post: Computes the negation of the vector
 *       param: A vector
 *      return: The negation of the vector
 */

/*
 *    function: operator += (vector += vector)
 *       brief: Sums two vectors, puts result in calling vector object
 *         pre: Vectors must be of same size
 *        post: Computes vector sum
 *       param: Vector of size 'n'
 *      return: Vector sum
 */

/*
 *    function: operator + (vector + vector)
 *       brief: Sums two vectors
 *         pre: Vectors must be of same size
 *        post: Comutes vector sum
 *       param: Vector of size 'n'
 *       param: Vector of size 'n'
 *      return: Vector sum
 */

/*
 *    function: operator * (scalar * vector)
 *       brief: multiplies a scaler to a vector (if the scalar comes first)
 *         pre: Scalar must me the same type as the elements of the vector and
 *              have the '+' operator functionality.
 *        post: Computes element-wise product of scalar and vector.
 *       param: A scalar value (same type as vector elements)
 *       param: A vector
 *      return: Vector of element-wise product of scalar and vector.
 */

/*
 *    function: operator * (vector * scalar)
 *       brief: multiplies a scaler to a vector (if the scalar comes first)
 *         pre: Scalar must me the same type as the elements of the vector and
 *              have the '+' operator functionality.
 *        post: Computes element-wise product of scalar and vector.
 *       param: A scalar value (same type as vector elements)
 *       param: A vector
 *      return: Vector of element-wise product of scalar and vector.
 */

/*
 *    function: operator * (vector * vector)
 *       brief: Computes the inner product of two vectors
 *         pre: Vectors must be of same size
 *        post: Computes the inner product of two vectors
 *       param: Vector of size 'n'
 *       param: Vector of size 'n'
 *      return: inner product
 */

/*
 *    function: operator / (vector / vector)
 *       brief: Computes the element-wise division of two vectors
 *         pre: Vectors must be of same size
 *        post: Computes the element-wise division of two vectors
 *       param: Vector of size 'n'
 *       param: Vector of size 'n'
 *      return: element-wise division vector of size 'n'
 */

/*
 *    function: operator <<
 *       brief: Outputs a vector to screen
 *         pre: none
 *        post: Outputs a vector to screen
 *       param: ostream (such as cout or ofstream)
 *       param: vector
 *      return: input ostream
 */

/*
 *    function: operator >>
 *       brief: Reads in a vector
 *         pre: The vector being read in must have the same number of elements
 *              as the vector being read into.
 *        post: Assigns read values to vector
 *       param: istream (such as cin or ifstream)
 *      return: input istream
 */

/*
 *    function: sum (vector)
 *       brief: Sums elements of a vector
 *         pre: Elements must have '+=' opertor functional
 *        post: Returns sum of vector elements.
 *       param: Vector to have elements summed
 *      return: Sum of vector elements
 */

/*
 *    function: sum()
 *       brief: Sums elements of a vector
 *         pre: Elements must have '+=' opertor functional
 *        post: Returns sum of vector elements.
 *      return: Sum of vector elements
 */

/*
 *    function: sqrt (vector)
 *       brief: Calculates the square root of the elements of a vector
 *         pre: Elements must have sqrt function available
 *        post: Returns vector square roots of elements.
 *       param: Vector to have elements evaluated on
 *      return: vector square roots of elements.
 */

/*
 *    function: abs (vector)
 *       brief: Calculates the absolute value of the elements of a vector
 *         pre: Elements must have abs() function available
 *        post: Returns vector with absolute values of elements.
 *       param: Vector to have elements evaluated on
 *      return: vector with absolute values of elements
 */

// TODO: Figure out how to comment about type-traits. Not used in assignment so
//       not commented here.

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "nl_exceptions.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>
#include <cmath>
#include <fstream>

namespace oonm
{
  // VECTOR DECLARATION
  template <class T>
  class Vector;

  // GLOBAL FUNCTION DECLARATIONS
  template <class T>
  bool operator == (const Vector<T>& lhs, const Vector<T>& rhs);

  template <class T>
  bool operator != (const Vector<T>& lhs, const Vector<T>& rhs);

  template <class T>
  Vector<T> cat(const Vector<T>& a1, const Vector<T>& a2);

  template <class T>
  std::ostream& operator << (std::ostream& out, const Vector<T>& vec);

  template <class T>
  std::istream& operator >> (std::istream& in, Vector<T>& vec);

  template <class T>
  Vector<T> operator * (const T& C, const Vector<T>& v2);

  template <class T>
  Vector<T> operator + (const Vector<T>& v1, const Vector<T>& v2);

  template <class T>
  Vector<T> operator - (const Vector<T>& v1, const Vector<T>& v2);

  template <class T>
  Vector<T> operator - (const Vector<T>& vec);

  template <class T>
  T sum(const Vector<T>& vec);

  template <class T>
  T dot(const Vector<T>& v1, const Vector<T>& v2);

  // VECTOR CLASS
  template <class T>
  class Vector
  {
    public:

      Vector();
      Vector(const size_t size);
      Vector(const size_t size, const T& value);
      Vector<T>& operator=(const Vector<T>& src);
      Vector<T>& operator=(Vector<T> &&other);
      Vector(const Vector<T>& src);
      Vector(Vector<T> &&other);
      ~Vector();

      // UTILITIES
      void resize(const size_t size=0);
      void reuse(const size_t size=0);
      void clear();
      void set_size(const size_t size);
      size_t get_size() const {return size_;}
      void remove(const size_t i);
      const T& operator[](const size_t i) const;
      T& operator[](const size_t i);
      Vector<T>& sort();
      T* begin() const;
      T* end() const;
      //Vector<T> slice(const T* start=begin(), const T* stop=end(), const size_t step=1) const;
      int find(const T& val);

      // MATH
      T sum() const;
      T dot(const Vector<T>& vec) const;
      Vector<T>& operator += (const Vector<T>& vec);
      Vector<T>& operator -= (const Vector<T>& vec);
      Vector<T> operator * (const T& C) const;
      T operator * (const Vector<T>& v2) const;
      Vector<T> operator / (const T& C) const;
      Vector<T> operator / (const Vector<T>& v2) const;

      friend Vector<T> operator+ <> (const Vector<T>& v1, const Vector<T>& v2);
      friend Vector<T> operator- <> (const Vector<T>& v1, const Vector<T>& v2);
      friend Vector<T> operator- <> (const Vector<T>& vec);

      // FRIENDS
      friend Vector<T> cat <> (const Vector<T>& a1, const Vector<T>& a2);
      friend bool operator == <> (const Vector<T>& lhs, const Vector<T>& rhs);
      friend bool operator != <> (const Vector<T>& lhs, const Vector<T>& rhs);
      friend std::ostream& operator << <> (std::ostream& out, const Vector<T>& vec);
      friend std::istream& operator >> <> (std::istream& in, Vector<T>& vec);

    private:
      size_t size_;
      T* data_;
  };

} // oonm namespace

// MICELANIOUS (No comments because not used!)
template <class T>
struct isVector
{
  static const bool value = false;
};

template <class T>
struct isVector<oonm::Vector<T>>
{
  static const bool value = true;
};

// TODO: Overload additional math functions from <cmath>. Also move to a
//       different file because this thing is crazy!
template <class T>
oonm::Vector<T> sqrt(const oonm::Vector<T>& vec);

template <class T>
oonm::Vector<T> abs(const oonm::Vector<T>& vec);

#include "vector.hpp"

#endif /* VECTOR_HPP_ */
