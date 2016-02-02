//////////////////////////////////////////////////////////////////////
/// @file test1.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

#include "Function.hpp"
#include <iostream>

#include "../headers/rFunction.hpp"
using std::cout;

double tFunc(const double x);
double tdFunc(const double x);
double tddFunc(const double x);

int main()
{
  rFunction rt(tFunc, 0.001);
  int nopts = 4;
  int input;
  RF_Options* opts = new RF_Options[nopts];
  opts[0] = RF_Options::SHOW_X1;
  opts[1] = RF_Options::SHOW_X2;
  opts[2] = RF_Options::SHOW_FX;
  //opts[3] = RF_Options::SHOW_ERROR;
  std::cin >> input;
  opts[3] = (RF_Options)input;

  rt.setOptions(opts, nopts);
  cout << "Secant: " << rt.secant_method(.7, .5) << '\n'<< '\n'<< '\n';
  cout << "Newton: " << rt.nr_method(tdFunc, .7) << '\n'<< '\n'<< '\n';
  cout << "Modified Newton 1: " << rt.mod_newton(.8) << '\n'<< '\n'<< '\n';
  cout << "Modified Newton 2: " << rt.mod_newton(tdFunc, tddFunc, .8) << '\n'<< '\n'<< '\n';
  cout << "Regula-Falsi: " << rt.rf_method(-1, .7) << '\n'<< '\n'<< '\n';
  cout << "Bisection: " << rt.bisection_method(0, 1) << '\n'<< '\n'<< '\n';
  cout << "FPI: " << rt.fpi(.5, -1) << '\n';

  return 0;
}

double tFunc(const double x)
{
  return x*x + x - 1;
}

double tdFunc(const double x)
{
  return 2*x + 1;
}

double tddFunc(const double x)
{
  return 2;
}

