/*
 * nl_derivatives.tpp
 *
 *  Created on: Feb 10, 2016
 *      Author: ryan
 */
template<class F, class X>
X df(const F &func,
     const X x,
     const X dx)
{
  if(dx == 0) throw divide_by_zero();

  return (func(x) - func(x - dx)) / dx;
}

template<class F, class X>
X ddf(const F &func,
      const X x0,
      const X x1,
      const X x2)
{
  X dx1 = x2 - x1;
  X dx2 = x1 - x0;
  return (func(x0) - 2 * func(x1) + func(x2)) / (dx1*dx2);
}

template<class F, class X>
X ddf(const F &func,
      const X x,
      const X dx)
{
    if(dx == 0) throw divide_by_zero();

  return (func(x - dx) - (2*func(x)) + func(x + dx)) / (dx*dx);
}


