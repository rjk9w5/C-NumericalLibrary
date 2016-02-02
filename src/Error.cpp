//////////////////////////////////////////////////////////////////////
/// @file Error.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

#include "Error.hpp"

void Error::printerror(const ErrorMsg& errorType) const
{
  switch(errorType)
  {
    case ErrorMsg::INPUT_ERROR:
      std::cout << "Invalid input!\n";
      break;
    case ErrorMsg::INVALID_OPTION:
      std::cout << "Invalid option input!\n";
      break;
    case ErrorMsg::ROOT_NOT_IN_BOUNDS:
      std::cout << "There is no root in these bounds!\n";
      break;
    case ErrorMsg::DIVIDE_BY_ZERO:
      std::cout << "Attempting to divide by zero!\n";
      break;
    default:
      std::cout << "No known error\n";
      break;
  }

  return;
}
