#ifndef NL_FUNCTION_TYPES_HPP_
#define NL_FUNCTION_TYPES_HPP_

#include <functional>

namespace numlib
{

typedef long double ldouble;

typedef std::function<ldouble(ldouble)> functionX;
typedef std::function<ldouble(ldouble,ldouble)> functionXY;
typedef std::function<ldouble(ldouble,ldouble,ldouble)> functionXYZ;

}

#endif
