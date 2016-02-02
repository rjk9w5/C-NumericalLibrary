//////////////////////////////////////////////////////////////////////
/// @file Function.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief class that contains function wrapper with derivatives.
//////////////////////////////////////////////////////////////////////
#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include "Error.hpp"

typedef double (*function)(const double);
typedef long double ldouble;

// Class: Function
//

class Function
{
  public:
    Function() {};
    Function(function func);
    Function(function func, const double dx);
    Function(const Function& func);

    double f(const double) const;
    double df(const double, const double) const;
    double df(const double) const;
    double ddf(const double, const double, const double) const;
    double ddf(const double) const;

    double getdx() const {return mdx;};
    void setdx(const double dx) {mdx = dx; return;};

    const Function& operator=(const Function& func);
    const Function& operator=(const function func);

  protected:
    double mdx;
    function mFunc;
    Error errObj;
};

#endif /* FUNCTION_HPP_ */
