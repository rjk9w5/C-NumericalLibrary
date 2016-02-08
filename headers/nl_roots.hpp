//////////////////////////////////////////////////////////////////////
/// @file nl_roots.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef NL_ROOTS_HPP_
#define NL_ROOTS_HPP_

#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include "nl_derivatives.hpp"
#include "nl_exception.hpp"
#include "nl_function_types.hpp"
#include "nl_options.hpp"

// @fn:   fpi(functionX f, const double x0, const short cc)
// @desc: Fixed Point Iteration with for g(x) = x - cc*c*f(x)

// @fn:   fpi(functionX g, const double x0)
// @desc: Fixed Point Iteration with user defined input g(x)

namespace numlib
{

  const ldouble TOLERANCE = pow(10L,-8L); // 1e-12
  const size_t MAX_IT = pow(10,3);

//   TODO: write fpi for a given g(x) function
  ldouble fpi(const functionX &gfunc,
              const ldouble x0);

  ldouble fpi(const functionX &func,
              const ldouble x0,
              const short cc);

//  Slope
  ldouble nr_method(const functionX &func,
                    const functionX &dfunc,
                    const ldouble x0);
  ldouble mod_nr_method(const functionX &func,
                     const functionX &dfunc,
                     const functionX &ddfunc,
                     const ldouble x0);
  ldouble mod_nr_method(const functionX &func,
                     const ldouble x0);
  ldouble secant_method(const functionX &func,
                        const ldouble x0,
                        const ldouble x1);
//
//  Bracketing
  ldouble bisection_method(const functionX &func,
                           const ldouble xa,
                           const ldouble xb);
  ldouble rf_method(const functionX &func,
                    const ldouble x0,
                    const ldouble x1);

  void outputHeader(const std::unique_ptr<nl_root_display[]> &opts, const int n_opts);
  void outputStep(const ldouble *stepData, const int step);

  bool check(const ldouble* x);

  ldouble absErr(const ldouble x0, const ldouble x1);
  ldouble relErr(const ldouble x0, const ldouble x1);
  ldouble zeroErr(const ldouble fx);
  ldouble getError(const nl_root_error, const ldouble* x);
} // namespace numlib

#endif /* NL_ROOTS_HPP_ */
