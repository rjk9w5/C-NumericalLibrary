/*
 * nl_LU_decompostion.h
 *
 *  Created on: Feb 15, 2016
 *      Author: ryan
 */

#ifndef HEADERS_NL_LU_DECOMPOSTION_H_
#define HEADERS_NL_LU_DECOMPOSTION_H_

#include "nl_sq_matrix.h"
#include "nl_l_matrix.h"
#include "nl_u_matrix.h"

template<class T>
base_matrix<T>* crt_lu_decomp(const sq_matrix<T>& inp, l_matrix<T> L, u_matrix<T> U);

template<class T>
void dltl_lu_decomp(const sq_matrix<T>& inp, l_matrix<T> L, u_matrix<T> U);

template<class T>
void chksy_lu_decomp(const sq_matrix<T>& inp, l_matrix<T> L, u_matrix<T> U);



#endif /* HEADERS_NL_LU_DECOMPOSTION_H_ */
