/*
 * nl_dense_matrix.hpp
 *
 *  Created on: Feb 10, 2016
 *      Author: ryan
 */

#ifndef HEADERS_NL_DENSE_MATRIX_HPP_
#define HEADERS_NL_DENSE_MATRIX_HPP_

#include <utility>
#include <memory>
#include <exception>
#include "nl_vector.hpp";

template <class T>
class matrix_dense;

template <class T>
matrix_dense<T>&& transpose(const matrix_dense<T>& mat);

template <class T>
std::ostream& operator << (std::ostream out, const matrix_dense<T>& mat);

template <class T>
std::istream& operator << (std::istream in, matrix_dense<T>& mat);

template <class T>
class matrix_dense
{
public:
  matrix_dense(): m_row(0), m_col(0), m_mat(nullptr){}
  matrix_dense(const matrix_dense<T>& src);
  matrix_dense(matrix_dense<T>&& other);
  matrix_dense(const size_t rc);
  matrix_dense(const size_t r, const size_t  c);

  void transpose();
  friend matrix_dense<T>&& transpose<>(const matrix_dense<T>& mat);

  const T& operator ()(const size_t r, const size_t c) const;
  T& operator ()(const size_t r, const size_t c);

  friend std::ostream& operator << <>(std::ostream out, const matrix_dense<T>& mat);
  friend std::istream& operator >> <>(std::istream in, matrix_dense<T>& mat);

private:
  std::unique_ptr<std::unique_ptr<T[]>[]> m_mat;
  size_t m_row, m_col;
};





#endif /* HEADERS_NL_DENSE_MATRIX_HPP_ */
