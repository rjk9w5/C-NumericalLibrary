/*
 * base_matrix.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */
#ifndef BASE_MATRIX_H_
#define BASE_MATRIX_H_

#include "nl_exception.h"
// IO includes
#include <istream>
#include <ostream>
#include <iomanip>
// Functionality includes
#include <utility> // std::move
#include <cmath> // std::pow, std::sqrt, std::abs, etc.

namespace nl
{
  template <class Form_T, class Ele_T>
  class Matrix;

  template <class Form_T, class Ele_T>
  std::ostream& operator << (std::ostream& out,
                             const Matrix<Form_T, Ele_T>& mat);

  template <class Form_T, class Ele_T>
  std::istream& operator >> (std::istream& out,
                             const Matrix<Form_T, Ele_T>& mat);

  template <class Form_T, class Ele_T>
  nl::Matrix<Form_T, Ele_T> operator * (const Matrix<Form_T, Ele_T>& m1,
                            const Matrix<Form_T, Ele_T>& m2);

  template <class Form_T, class Ele_T>
  nl::Matrix<Form_T, Ele_T> operator + (const Matrix<Form_T, Ele_T>& m1,
                            const Matrix<Form_T, Ele_T>& m2);

  template <class Form_T, class Ele_T>
  nl::Matrix<Form_T, Ele_T> operator - (const Matrix<Form_T, Ele_T>& m1,
                            const Matrix<Form_T, Ele_T>& m2);

  template <class Form_T, class Ele_T>
  nl::Vector<Ele_T> operator * (const Matrix<Form_T, Ele_T>& m1,
                                        const nl::Vector<Ele_T>& vec);

  template <class Form_T, class Ele_T>
  nl::Matrix<Form_T, Ele_T> operator / (const Matrix<Form_T, Ele_T>& m1,
                            const Matrix<Form_T, Ele_T>& m2);


  template <class Form_T, class Ele_T>
  class Matrix
  {
    public:
      Matrix();
      Matrix(const size_t n, const size_t m);
      Matrix(const size_t n, const size_t m, const Ele_T& default_val);
      Matrix& operator =(const Matrix& src);
      Matrix(const Matrix<Form_T, Ele_T>& src);
      Matrix& operator =(const Matrix&& other);
      Matrix(Matrix<Form_T, Ele_T>&& other);
      ~Matrix();

      Ele_T& operator()(const size_t i, const size_t j);
      Ele_T& operator()(const size_t i, const size_t j) const;
      Ele_T& operator[](const size_t i);
      Ele_T& operator[](const size_t i) const;

      Matrix& operator += (const Matrix& mat);
      Matrix& operator -= (const Matrix& mat);
      Matrix& operator *= (const Matrix& mat);


      friend std::ostream& operator << <> (std::ostream& out,
                                        const Matrix<Form_T, Ele_T>& mat);

      friend std::istream& operator >> <> (std::istream& out,
                                 const Matrix<Form_T, Ele_T>& mat);
    private:
      nl::Vector<Ele_T> data_;
      size_t rows_, cols_;
  };

}

#include "nl_base_matrix.hpp"
#include "nl_base_matrix_global.hpp"

#endif /* BASE_MATRIX_H_ */
