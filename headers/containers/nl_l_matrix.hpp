//////////////////////////////////////////////////////////////////////
/// @file nl_l_matrix.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef NL_L_MATRIX_HPP_
#define NL_L_MATRIX_HPP_

#include "nl_vector.hpp"
#include <utility>
#include <ostream>
#include <iomanip>

namespace nl
{
template <class T>
class l_matrix;

template <class T>
std::ostream& operator << (std::ostream& out, const l_matrix<T>& lmat);

template <class T>
class l_matrix//: matrix<l_matrix, T>
{
  public:
    l_matrix();
    l_matrix<T>& operator = (l_matrix<T>&& other);
    l_matrix(l_matrix<T>&& other);
    l_matrix<T>& operator = (const l_matrix<T>& src);
    l_matrix(const l_matrix<T>& src);
    l_matrix(const size_t n);

    const T& operator[] (const size_t i)const;
    T& operator[] (const size_t i);
    const T& operator() (const size_t r, const size_t c)const;
    T& operator() (const size_t r, const size_t c);

    friend std::ostream& operator << <> (std::ostream& out, const l_matrix<T>& lmat);
  private:
    vector<T> m_mat;
    size_t m_n;
    T empty;
};

#include "nl_l_matrix.tpp"
}


#endif /* NL_L_MATRIX_HPP_ */
