/*
 * norms.h
 *
 *  Created on: Feb 24, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Norm definitions
 */

/*
 *       class: Norm
 *       brief: virtual Functor classes for L-norm calculation
 */

/*
 *    function: virtual operator()
 *       brief: virtual norm evaluation function
 *         pre: None
 *        post: None
 *      return: None
 */

/*
 *       class: Norm2
 *       brief: Functor classes for L2-norm calculation
 */

/*
 *    function: virtual operator()
 *       brief: L2-norm evaluation function
 *         pre: Obj_T type must have * operator that returns a Return_T and
 *              Return_T must have sqrt() available and should also return a
 *              Return_T
 *        post: returns the L2-norm of input Obj_T as a Return_T
 *      return: the L2-norm of input Obj_T as a Return_T
 */

#ifndef NORMS_H_
#define NORMS_H_

#include <cmath>
#include <iostream>
#include "vector.h"

template <class Obj_T, class Return_T=double>
class Norm
{
  public:
    virtual Return_T operator () (const Obj_T& set) = 0;
};

template <class Obj_T, class Return_T=double>
class Norm2
{
  public:
    virtual Return_T operator () (const Obj_T& set);
};

#include "norms.hpp"

#endif /* NORMS_H_ */
