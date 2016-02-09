//////////////////////////////////////////////////////////////////////
/// @file test1.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

//#include "Function.hpp"
#include <iostream>
#include <functional>
#include "nl_derivatives.hpp"
#include "nl_roots.hpp"
#include <memory>
#include <cmath>
using namespace numlib;

//#include "../headers/rFunction.hpp"
using std::cout;

double tFunc(const double x);
double tdFunc(const double x);
double tddFunc(const double x);


int main()
{
  functionX myFunc = tFunc;
  std::unique_ptr<int[]> x(new int[5]);

  std::cout << numlib::TOLERANCE << '\n';
  for(int i=0; i<5; ++i)
  {
    cout << x[i];
  }
  cout << "\n\n";
  cout << df(myFunc, 4) << '\n';
  cout << tdFunc(4) << '\n';
//  cout << "FPI: " << fpi(myFunc,1.0,(short)-1) << '\n';
  cout << "Newton Method: " << nr_method(myFunc, tdFunc, 1) << '\n';
//  cout << "Modified Newton Method: " << mod_nr_method(myFunc, tdFunc, tddFunc, 1) << '\n';
//  cout << "Modified Newton Method (Numerical Derivatives): " << mod_nr_method(myFunc, 1) << '\n';
//  cout << "Secant Method: " << secant_method(myFunc, 1, 2) << '\n';
//  cout << "Bisection Method: " << bisection_method(myFunc, 0, 2) << '\n';
//  cout << "Regula-Falsi Method: " << rf_method(myFunc, 0, 4) << '\n';

  return 0;
}

double tFunc(const double x)
{
  return 2*x*cos(x*x)*(1 + x);
}

double tdFunc(const double x)
{
  return (2*cos(x*x) - 4*x*x*sin(x*x))*(x+1) + tFunc(x)/(1+x);
}

double tddFunc(const double x)
{
  return 2;
}

