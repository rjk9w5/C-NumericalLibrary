/*
 * nl_rect_matrix.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */
#ifndef NL_RECT_MATRIX_H_
#define NL_RECT_MATRIX_H_

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
class MatrixRECT
{
  public:
    MatrixRECT(): m_row(0), m_col(0), m_mat(nullptr){}
    MatrixRECT(const MatrixRECT<T>& src);
    MatrixRECT(MatrixRECT<T>&& other);
    MatrixRECT(const size_t rc);
    MatrixRECT(const size_t r, const size_t  c);

  // todo
  void transpose();
  friend MatrixRECT<T>&& transpose<>(const MatrixRECT<T>& mat);
  void row_swap(const size_t r1, const size_t r2);
  void col_swap(const size_t c1, const size_t c2);
  void swap(MatrixRECT<T>& inp);

  const T& operator ()(const size_t r, const size_t c) const;
  T& operator ()(const size_t r, const size_t c);

  friend std::ostream& operator << <>(std::ostream out, const MatrixRECT<T>& mat);
  friend std::istream& operator >> <>(std::istream in, MatrixRECT<T>& mat);

private:
  Vector m_mat;
  size_t m_row, m_col;
};


} // namespace nl



#endif /* NL_RECT_MATRIX_H_ */
