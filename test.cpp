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
#include <iomanip>
#include "nl_l_matrix.hpp"
using namespace nl;

//#include "../headers/rFunction.hpp"
using std::cout;

double tFunc(const double x);
double tdFunc(const double x);
double tddFunc(const double x);


int main(int argc, char* argv[])
{
  functionX myFunc = tFunc;
  std::unique_ptr<int[]> x(new int[5]);
  int row=4, col=4;
  std::unique_ptr<std::unique_ptr<long double[]>[]> mat;


  mat.reset(new std::unique_ptr<long double[]>[row]);
  for(int i=0; i<row; ++i)
    mat[i].reset(new long double[col]);

  for(int i=0; i<row; ++i)
  {
    for(int j=0; j<col; ++j)
      mat[i][j] = static_cast<long double>(1)/((i+1)+(j+1)-1);
  }
  std::cout << "Made matrix\n\n\n";
  for(int i=0; i<row; ++i)
  {
    for(int j=0; j<col; ++j)
      std::cout << std::setprecision(12) << mat[i][j] << ' ';
    std::cout << '\n';
  }

  std::cout << mat[0][0] << '\n';

  std::cout << TOLERANCE << '\n';
  for(int i=0; i<5; ++i)
  {
    cout << x[i];
  }
  cout << "\n\n";
  cout << df(myFunc, 4.0) << '\n';
  cout << tdFunc(4) << '\n';
//  cout << "FPI: " << fpi(myFunc,1.0,(short)-1) << '\n';
  cout << "Newton Method: " << nr_method(myFunc, tdFunc, 2.4) << '\n';
//  cout << "Modified Newton Method: " << mod_nr_method(myFunc, tdFunc, tddFunc, 1) << '\n';
//  cout << "Modified Newton Method (Numerical Derivatives): " << mod_nr_method(myFunc, 1) << '\n';
//  cout << "Secant Method: " << secant_method(myFunc, 1, 2) << '\n';
//  cout << "Bisection Method: " << bisection_method(myFunc, 0, 2) << '\n';
//  cout << "Regula-Falsi Method: " << rf_method(myFunc, 0, 4) << '\n';

  return 0;
}

double tFunc(const double x)
{
  //return 2*x*cos(x*x)*(1 + x);
  double S = sin(x*x);
  return 2*S - 3*x*S + x*x*S;
}

double tdFunc(const double x)
{
  //return (2*cos(x*x) - 4*x*x*sin(x*x))*(x+1) + tFunc(x)/(1+x);
  double S = sin(x*x);
  double C = cos(x*x);
  return 2*x*C*(x*x - 3*x + 2) + S*(2*x - 3);
}

double tddFunc(const double x)
{
  return 2;
}

