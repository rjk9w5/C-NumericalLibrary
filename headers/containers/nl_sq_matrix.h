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
#include "nl_vector.h";

namespace nl
{

template <class T>
class sq_matrix;

template <class T>
sq_matrix<T>&& transpose(const sq_matrix<T>& mat);

template <class T>
std::ostream& operator << (std::ostream out, const sq_matrix<T>& mat);

template <class T>
std::istream& operator << (std::istream in, sq_matrix<T>& mat);

template <class T>
class sq_matrix
{
public:
  sq_matrix(): m_row(0), m_col(0), m_mat(nullptr){}
  sq_matrix(const sq_matrix<T>& src);
  sq_matrix(sq_matrix<T>&& other);
  sq_matrix(const size_t rc);
  sq_matrix(const size_t r, const size_t  c);

  // todo
  void transpose();
  friend sq_matrix<T>&& transpose<>(const sq_matrix<T>& mat);
  void row_swap(const size_t r1, const size_t r2);
  void col_swap(const size_t c1, const size_t c2);
  void swap(sq_matrix<T>& inp);

  const T& operator ()(const size_t r, const size_t c) const;
  T& operator ()(const size_t r, const size_t c);

  friend std::ostream& operator << <>(std::ostream out, const sq_matrix<T>& mat);
  friend std::istream& operator >> <>(std::istream in, sq_matrix<T>& mat);

private:
  vector m_mat;
  size_t m_row, m_col;
};


} // namespace nl


#endif /* HEADERS_NL_DENSE_MATRIX_HPP_ */
