//////////////////////////////////////////////////////////////////////
/// @file nl_u_matrix.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef NL_U_MATRIX_HPP_
#define NL_U_MATRIX_HPP_

#include "nl_vector.h"
#include <utility>
#include <ostream>
#include <iomanip>

namespace nl
{
template <class T>
class u_matrix;

template <class T>
std::ostream& operator << (std::ostream& out, const u_matrix<T>& lmat);

template <class T>
class u_matrix//: matrix<l_matrix, T>
{
  public:
    u_matrix();
    u_matrix<T>& operator = (u_matrix<T>&& other);
    u_matrix(u_matrix<T>&& other);
    u_matrix<T>& operator = (const u_matrix<T>& src);
    u_matrix(const u_matrix<T>& src);
    u_matrix(const size_t n);

    const T& operator[] (const size_t i)const;
    T& operator[] (const size_t i);
    const T& operator() (const size_t r, const size_t c)const;
    T& operator() (const size_t r, const size_t c);

    friend std::ostream& operator << <> (std::ostream& out, const u_matrix<T>& lmat);
  private:
    vector<T> m_mat;
    size_t m_n;
    T empty;
};

#include "nl_u_matrix.hpp"
}





#endif /* NL_U_MATRIX_HPP_ */
