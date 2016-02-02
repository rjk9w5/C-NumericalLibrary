//////////////////////////////////////////////////////////////////////
/// @file Error.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <iostream>

enum class ErrorMsg: int
{
  INPUT_ERROR, INVALID_OPTION, ROOT_NOT_IN_BOUNDS, DIVIDE_BY_ZERO
};

class Error
{
  public:
    Error() {};
    void printerror(const ErrorMsg& errorType) const;

  private:

};

#endif /* ERROR_HPP_ */
