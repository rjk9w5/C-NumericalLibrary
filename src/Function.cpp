//////////////////////////////////////////////////////////////////////
/// @file Function.tpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief implementation of function wrapper
//////////////////////////////////////////////////////////////////////

#include "Function.hpp"

Function::Function(function func): mdx(0)
{
  mFunc = func;
}
Function::Function(function func, const double dx): mdx(dx)
{
  mFunc = func;
}
Function::Function(const Function& func)
{
  mdx = func.mdx;
  mFunc = func.mFunc;
}

double Function::f(const double x) const
{
  return mFunc(x);
}


double Function::df( const double x1, const double x2 ) const
{
  double dx = x1 - x2;
  return (mFunc(x1) - mFunc(x2)) / dx;
}

double Function::df( const double x1 ) const
{
  try
  {
    if(!(mdx > static_cast<double>(0))) throw ErrorMsg::DIVIDE_BY_ZERO;
  }
  catch(const ErrorMsg& err)
  {
    errObj.printerror(err);
    throw err;
  }

  return (mFunc(x1) - mFunc(x1 - mdx)) / mdx;
}

double Function::ddf(const double x0, const double x1, const double x2) const
{
  double dx1 = x2 - x1;
  double dx2 = x1 - x0;
  return (mFunc(x0) - 2 * mFunc(x1) + mFunc(x2)) / (dx1*dx2);
}

double Function::ddf( const double x1 ) const
{
  try
  {
    if(mdx == 0) throw ErrorMsg::DIVIDE_BY_ZERO;
  }
  catch(const ErrorMsg& err)
  {
    errObj.printerror(err);
    throw err;
  }

  return (mFunc(x1 - mdx) - (2*mFunc(x1)) + mFunc(x1 + mdx)) / (mdx*mdx);
}

const Function& Function::operator=(const Function& func)
{
  mdx = func.mdx;
  mFunc = func.mFunc;
  return *this;
}
const Function& Function::operator=(const function func)
{
  mFunc = func;
  return *this;
}
