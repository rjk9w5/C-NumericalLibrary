//////////////////////////////////////////////////////////////////////
/// @file nl_exception.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef NL_EXCEPTION_HPP_
#define NL_EXCEPTION_HPP_

#include <exception>

class divide_by_zero: public std::exception
{
  public:
    const char* what() const noexcept
    {
      return "Attempt to divide by zero: Abort\n";
    }
};

class out_of_bounds: public std::exception
{
  const char* what() const noexcept
  {
    return "Solution is not bounded: Abort\n";
  }
};

class input_error: public std::exception
{
  const char* what() const noexcept
  {
    return "Improper input argument: Abort\n";
  }
};




#endif /* NL_EXCEPTION_HPP_ */
