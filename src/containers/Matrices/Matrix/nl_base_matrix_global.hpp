/*
 * nl_base_matrix_global.hpp
 *
 *  Created on: Feb 28, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */

template <class Form_T, class Ele_T>
std::ostream& nl::operator << (std::ostream& out,
                               const nl::Matrix<Form_T, Ele_T>& mat)
{

}

template <class Form_T, class Ele_T>
std::istream& nl::operator >> (std::istream& out,
                               const nl::Matrix<Form_T, Ele_T>& mat)
{

}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T> nl::operator * (const nl::Matrix<Form_T, Ele_T>& m1,
                              const nl::Matrix<Form_T, Ele_T>& m2)
{
  nl::Matrix<Form_T, Ele_T> ret(m1);

  return ret*=m2;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T> nl::operator + (const nl::Matrix<Form_T, Ele_T>& m1,
                              const nl::Matrix<Form_T, Ele_T>& m2)
{
  nl::Matrix<Form_T, Ele_T> ret(m1);

  return ret+=m2;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T> nl::operator - (const nl::Matrix<Form_T, Ele_T>& m1,
                              const nl::Matrix<Form_T, Ele_T>& m2)
{
  nl::Matrix<Form_T, Ele_T> ret(m1);

  return ret-=m2;
}

template <class Form_T, class Ele_T>
nl::Vector<Ele_T> nl::operator * (const nl::Matrix<Form_T, Ele_T>& mat,
                              const nl::Vector<Ele_T>& vec)
{

}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T> nl::operator / (const nl::Matrix<Form_T, Ele_T>& m1,
                              const nl::Matrix<Form_T, Ele_T>& m2)
{
  nl::Matrix<Form_T, Ele_T> ret(m1.rows_, m1.cols_);
  if(m1.rows_ == m2.rows_ && m1.cols_ == m2.cols_)
  {
    for(size_t i=0; i<m1.rows_; ++i)
    {
      for(size_t j=0; j<m1.cols_; ++j)
      {
        ret(i,j) = m1(i,j)/m2(i,j);
      }
    }
  }
  else
  {
    throw nl::FatalError("");
  }

  return ret;
}

