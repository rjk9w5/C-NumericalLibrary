/*
 * base_matrix.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */
#ifndef BASE_MATRIX_H_
#define BASE_MATRIX_H_

#include <iostream>

namespace nl
{
  template <class Form_T, class Ele_T>
  class Matrix;

  template <class Form_T, class Ele_T>
  std::ostream& operator << (std::ostream& out,
                             const Matrix<Form_T, Ele_T>& mat);

  template <class Form_T, class Ele_T>
  class Matrix
  {
    public:
      Matrix();
      Matrix(const size_t n, const size_t m);
      Matrix(const size_t n, const size_t m, const Ele_T& default_val);
      Matrix(const Matrix<Form_T, Ele_T>& src);
      Matrix(Matrix<Form_T, Ele_T>&& other);
      ~Matrix();

      friend std::ostream& operator << (std::ostream& out,
                                        const Matrix<Form_T, Ele_T>& mat);
    private:
      oonm::Vector<Ele_T> data_;
      size_t rows_, cols_;
  };

}



#endif /* BASE_MATRIX_H_ */
