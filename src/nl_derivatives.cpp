//////////////////////////////////////////////////////////////////////
/// @file derivatives.tpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief Take numerical derivatives: Implementation
//////////////////////////////////////////////////////////////////////


/*
#include "nl_derivatives.hpp"

namespace numlib
{

ldouble df(const functionX &func,
     const ldouble x,
     const ldouble dx)
{
  if(dx == 0) throw divide_by_zero();

  return (func(x) - func(x - dx)) / dx;
}

ldouble ddf(const functionX &func,
      const ldouble x0,
      const ldouble x1,
      const ldouble x2)
{
  ldouble dx1 = x2 - x1;
  ldouble dx2 = x1 - x0;
  return (func(x0) - 2 * func(x1) + func(x2)) / (dx1*dx2);
}

ldouble ddf(const functionX &func,
      const ldouble x,
      const ldouble dx)
{
    if(dx == 0) throw divide_by_zero();

  return (func(x - dx) - (2*func(x)) + func(x + dx)) / (dx*dx);
}

} // namespace numlib
*/
