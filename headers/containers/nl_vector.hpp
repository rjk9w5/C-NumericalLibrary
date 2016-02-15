/*
 * vector.hpp
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
 *        post: Construct an vector object.
 */

/*
 *    function: vector(const size_t size)
 *       brief: Constructs an vector of input size.
 *        post: Constructs an vector of input size.
 *       param: size is an size_t type.
 */

/*
 *    function: vector(const size_t size, const T& value)
 *       brief: Size and value constructor.
 *        post: Constructs an vector of input size with all cells of input
 *              value.
 *       param: size is an size_t type.
 *       param: value is a T type.
 */

/*
 *    function: vector(const vector<T>& src)
 *       brief: Copy constructor
 *        post: Constructs an vector object with same values
 *              found in input.
 *       param: vector object to be copied size_to new vector.
 */

/*
 *    function: vector(vector<T>&& other)
 *       brief: Move constructor
 *        post: Moves memory for a new vector object from input.
 *       param: vector object to be moved size_to new vector.
 */

/*
 *    function: operator=(const vector<T>& src)
 *       brief: Copy assignment operator.
 *        post: Copies data from src to calling object.
 *       param: src is an vector type.
 *      return: calling object.
 */

/*
 *    function: operator=(vector<T>&& other)
 *       brief: Move assignment operator.
 *        post: Moves data from other to calling object.
 *       param: other is an vector type.
 *      return: calling object.
 */

/*
 *    function: ~vector()
 *       brief: Destructor
 *        post: Destroys vector object.
 */

/*
 *    function: resize(const size_t size)
 *       brief: Resizes vector while only destroying data in cells with
 *              indices greater than the new size.
 *        post: Resizes vector but saves data.
 *       param: size to resize to, default=0. (size_t)
 *      return: none
 */

/*
 *    function: reuse(const size_t size)
 *       brief: destroys all existing data and applies a new size.
 *        post: destroys all existing data and applies a new size.
 *       param: size to resize to, default=0. (size_t)
 *      return: none
 */

/*
 *    function: set_size(const size_t size)
 *       brief: destroys all existing data and sets new size.
 *        post: destroys all existing data and sets new size.
 *       param: size to resize to. (size_t)
 *      return: none
 */

/*
 *    function: get_size()
 *       brief: returns size.
 *        post: returns size.
 *      return: size of vector calling object. (size_t)
 */

/*
 *    function: remove(const size_t i)
 *       brief: removes value at index i if it exists.
 *        post: value at index i is removed and data is shifted.
 *       param: index i to be removed.
 *      return: none
 */

/*
 *    function: operator[](const size_t i) const
 *       brief: read only access element at index i
 *        post: returns element value at index i
 *       param: index i to be accessed
 *      return: returns element value at index i
 */

/*
 *    function: operator[](const size_t i)
 *       brief: read-write access element at index i
 *        post: returns element value at index i
 *       param: index i to be accessed
 *      return: returns element value at index i
 */

/*
 *    function: sort()
 *       brief: Sorts vector calling object
 *         pre: Requires template type T to have < operator implemented
 *        post: Sorts vector
 *      return: none
 */

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <exception>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

namespace nl
{
// VECTOR DECLARATION
template <class T>
class vector;

// FRIEND DECLARATIONS
template <class T>
bool operator == (const vector<T>& lhs, const vector<T>& rhs);
template <class T>
bool operator != (const vector<T>& lhs, const vector<T>& rhs);
template <class T>
vector<T>& cat(const vector<T>& a1, const vector<T>& a2);
template <class T>
std::ostream& operator << (std::ostream& out, const vector<T>& vec);
template <class T>
std::istream& operator >> (std::istream& in, vector<T>& vec);

template <class T>
vector<T> dot(const vector<T>& v1, const vector<T>& v2);
template <class T>
vector<T> operator * (const vector<T>& v1, const vector<T>& v2);
template <class T>
vector<T> operator * (const T& C, const vector<T>& v2);
template <class T>
vector<T> operator * (const vector<T>& v1, const T& C);
template <class T>
vector<T> operator + (const vector<T>& v1, const vector<T>& v2);
template <class T>
vector<T> operator - (const vector<T>& v1, const vector<T>& v2);
template <class T>
vector<T> operator - (const vector<T>& vec);

// VECTOR CLASS
template<class T>
class vector
{
  public:

    vector();
    vector(const size_t size);
    vector(const size_t size, const T& value);
    vector<T>& operator=(const vector<T>& src);
    vector<T>& operator=(vector<T> &&other);
    vector(const vector<T>& src);
    vector(vector<T> &&other);
    ~vector();

    // UTILITIES
    void resize(const size_t size=0);
    void reuse(const size_t size=0);
    void set_size(const size_t size);
    size_t get_size() const {return m_size;}
    void remove(const size_t i);
    const T& operator[](const size_t i) const;
    T& operator[](const size_t i);
    void sort();
    T* begin();
    T* end();
    vector<T> slice(const T* start=begin(), const T* stop=end(), const size_t step=1);

    // MATH
    friend vector<T> dot <> (const vector<T>& v1, const vector<T>& v2);
    friend vector<T> operator * <> (const vector<T>& v1, const vector<T>& v2);
    friend vector<T> operator * <> (const T& C, const vector<T>& v2);
    friend vector<T> operator * <> (const vector<T>& v1, const T& C);
    const vector<T>& operator += (const vector<T>& vec);
    friend vector<T> operator + <> (const vector<T>& v1, const vector<T>& v2);
    friend vector<T> operator - <> (const vector<T>& v1, const vector<T>& v2);
    friend vector<T> operator - <> (const vector<T>& vec);

    // FRIENDS
    friend vector<T>& cat<>(const vector<T>& a1, const vector<T>& a2);
    friend bool operator == <>(const vector<T>& lhs, const vector<T>& rhs);
    friend bool operator != <>(const vector<T>& lhs, const vector<T>& rhs);
    friend std::ostream& operator << <>(std::ostream& out, const vector<T>& vec);
    friend std::istream& operator >> <>(std::istream& in, vector<T>& vec);

  private:
    size_t m_size, m_max;
    std::unique_ptr<T[]> m_data;
};

#include "nl_vector.tpp"
} // nl namespace
#endif /* VECTOR_HPP_ */
