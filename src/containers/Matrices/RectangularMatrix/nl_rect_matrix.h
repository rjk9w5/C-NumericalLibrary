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
  class MatrixRECT;

  template <class T>
  MatrixRECT<T>&& transpose(const MatrixRECT<T>& mat);

  template <class T>
  std::ostream& operator << (std::ostream out, const MatrixRECT<T>& mat);

  template <class T>
  std::istream& operator << (std::istream in, MatrixRECT<T>& mat);

  template <class T>
  class MatrixRECT: Matrix<MatrixRECT<T>, T>
  {
    public:
      MatrixRECT();
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
  };
} // namespace nl



#endif /* NL_RECT_MATRIX_H_ */
