/*
 * norms.hpp
 *
 *  Created on: Feb 24, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Norm definitions
 */

template <class Obj_T, class Return_T>
Return_T Norm2<Obj_T, Return_T>::operator()(const Obj_T& set)
{
  Return_T innerp = set*set;
  return sqrt(innerp);
}

