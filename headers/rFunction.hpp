//////////////////////////////////////////////////////////////////////
/// @file RootFind.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef RFUNCTION_HPP_
#define RFUNCTION_HPP_

#include "Function.hpp"
#include "Error.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

enum class method: int
{
  FPI, NEWTON, MODNEWTON, SECANT, BISECTION, REGULAFALSI
};

enum class check_type: int
{
  ZERO, RELATIVE, ABSOLUTE
};

enum class RF_Options: int
{
  NOOPTION=NULL, SHOW_X1=1, SHOW_X2, SHOW_DX, SHOW_FX, SHOW_ERROR
};

class rFunction: private Function
{
  public:
    rFunction();
    rFunction(function func);
    rFunction(function func, const double dx);
    rFunction(const Function& func);

    void setCheckType(const check_type ct) {ctype = ct; return;};
    void setOptions(const RF_Options* opt, const int nopts);

    // General
    double fpi(const double x0, const short cc = -1);
    // TODO: write fpi for a given g(x) function
    // double fpi(function g, const double x0);

    // Slope
    double nr_method(function df, const double x0);
    double mod_newton(function df, function ddf, const double x0) const;
    double mod_newton(const double x0) const;
    double secant_method(const double x0, const double x1);

    // Bracketing
    double bisection_method(const double x0, const double x1);
    double rf_method(const double x0, const double x1);

    static double TOLERANCE; // 1e-12
    static int MAX_IT; // 1e6

  private:
    bool checkabs(const double x0, const double x1) const;
    bool checkrel(const double x0, const double x1) const;
    bool checkzero(const double fx) const;
    bool check(const check_type, const double* x) const;

    double absErr(const double x0, const double x1) const;
    double relErr(const double x0, const double x1) const;
    double zeroErr(const double fx) const;
    double getError(const check_type, const double* x) const;

    void outputStep(const double* data, const int step) const;
    void outputHeader() const;

    check_type ctype;
    bool* outputOptions;
    Error errObj;
};


#endif /* RFUNCTION_HPP_ */
