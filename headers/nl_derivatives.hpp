//////////////////////////////////////////////////////////////////////
/// @file derivatives.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief Take numerical derivatives: Definitions
//////////////////////////////////////////////////////////////////////
#ifndef NL_DERIVATIVES_HPP_
#define NL_DERIVATIVES_HPP_


#include <functional>
#include "nl_exception.hpp"
#include "nl_function_types.hpp"

namespace numlib
{
const ldouble DX_DEFAULT = 0.00001;

ldouble df(const functionX &func,
           const ldouble x,
           const ldouble dx=DX_DEFAULT);

ldouble ddf(const functionX &func,
            const ldouble x0,
            const ldouble x1,
            const ldouble x2);

ldouble ddf(const functionX &func,
            const ldouble x,
            const ldouble dx=DX_DEFAULT);
}

#endif /* NL_DERIVATIVES_HPP_ */
