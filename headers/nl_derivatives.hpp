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

namespace nl
{
const ldouble DX_DEFAULT = 0.00001;

template<class F, class X>
X df(const F &func,
           const X x,
           const X dx=DX_DEFAULT);
//ldouble df(const functionX &func,
//           const ldouble x,
//           const ldouble dx=DX_DEFAULT);

template<class F, class X>
X ddf(const F &func,
            const X x0,
            const X x1,
            const X x2);
//ldouble ddf(const functionX &func,
//            const ldouble x0,
//            const ldouble x1,
//            const ldouble x2);

template<class F, class X>
X ddf(const F &func,
            const X x,
            const X dx=DX_DEFAULT);
//ldouble ddf(const functionX &func,
//            const ldouble x,
//            const ldouble dx=DX_DEFAULT);

#include "nl_derivatives.tpp"
}

#endif /* NL_DERIVATIVES_HPP_ */
