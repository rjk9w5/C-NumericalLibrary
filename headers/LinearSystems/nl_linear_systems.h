/*
 * nl_linear_system_solvers.hpp
 *
 *  Created on: Feb 15, 2016
 *      Author: ryan
 */

#ifndef HEADERS_NL_LINEAR_SYSTEM_SOLVERS_HPP_
#define HEADERS_NL_LINEAR_SYSTEM_SOLVERS_HPP_

#include "nl_sq_matrix.h"
#include "nl_l_matrix.h"
#include "nl_u_matrix.h"
#include "nl_vector.h"

namespace linear_solvers
{

template <class T>
nl::vector<T> gs_elim(const nl::sq_matrix<T>& Amat,
               const nl::vector<T>& bvec);

template <class T>
nl::vector<T> gsj_elim(const nl::sq_matrix<T>& Amat,
                      const nl::vector<T>& bvec);

template <class T>
nl::vector<T> solve(const nl::l_matrix<T>& Lmat,
           const nl::u_matrix<T>& Lmat,
           const nl::vector<T>& bvec);

template <class T>
nl::vector<T> solve(const nl::l_matrix<T>& Lmat,
           const nl::u_matrix<T>& Lmat,
           const nl::sq_matrix<T> Pmat,
           const nl::vector<T>& bvec);
}
#endif /* HEADERS_NL_LINEAR_SYSTEM_SOLVERS_HPP_ */
