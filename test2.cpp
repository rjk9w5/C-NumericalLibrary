//////////////////////////////////////////////////////////////////////
/// @file test2.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

#include "nl_l_matrix.h"
#include "nl_u_matrix.h"
#include "nl_vector.h"
#include <iostream>
using namespace nl;

int main(int argc, char* argv[])
{
  std::cout << argc << argv[0] << std::endl;
  l_matrix<double> L(5);
  u_matrix<double> U(5);
  vector<double> v(15);

  for(int r=0; r<5; ++r)
  {
    for(int c=0; c<=r; ++c)
    {
      L(r,c) = static_cast<double>(1)/(r+c+1);
    }
  }

  for(int i=0; i<15; ++i)
    v[i] = i;

  std::cout << v.find(2) << std::endl;

  for(int r=0; r<5; ++r)
  {
    for(int c=0; c<5; ++c)
    {
      U(r,c) = static_cast<double>(1)/(r+c+1);
    }
  }

  std::cout << v*v << std::endl;


  std::cout << L << std::endl;
  std::cout << U << std::endl;
  return 0;
}
