//////////////////////////////////////////////////////////////////////
/// @file RootFind.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

#include "../headers/rFunction.hpp"

double rFunction::TOLERANCE = 0.000000000001;
int rFunction::MAX_IT = 1000000;

rFunction::rFunction():
    ctype(check_type::RELATIVE),
    outputOptions((int)RF_Options::NOOPTION)
{}

rFunction::rFunction(function func):
    Function(func),
    ctype(check_type::RELATIVE),
    outputOptions((int)RF_Options::NOOPTION)
{}

rFunction::rFunction(function func, const double dx):
    Function(func,dx),
    ctype(check_type::RELATIVE),
    outputOptions((int)RF_Options::NOOPTION)
{}

rFunction::rFunction(const Function& func):
    Function(func),
    ctype(check_type::RELATIVE),
    outputOptions((int)RF_Options::NOOPTION)
{}

void rFunction::setOptions(const RF_Options* opt, const int nopts)
{
  if(opt == NULL) return;

  outputOptions = new bool[5];
  for(int i=0; i<5; ++i)
    outputOptions[i] = 0;

  try
  {
    for(int i=0; i < nopts; ++i)
    {
      if(opt[i] == RF_Options::SHOW_ERROR)
      {
        outputOptions[4] = 1;
      }
      else if(opt[i] == RF_Options::SHOW_FX)
      {
        outputOptions[3] = 1;
      }
      else if(opt[i] == RF_Options::SHOW_DX)
      {
        outputOptions[2] = 1;
      }
      else if(opt[i] == RF_Options::SHOW_X2)
      {
        outputOptions[1] = 1;
      }
      else if(opt[i] == RF_Options::SHOW_X1)
      {
        outputOptions[0] = 1;
      }
      else
      {
        throw ErrorMsg::INVALID_OPTION;
      }
    }
  }
  catch(ErrorMsg& err)
  {
    errObj.printerror(err);
  }
  return;
}

// General
double rFunction::fpi(const double x0, const short cc)
{
  double c = cc * 1 / df(x0);
  double* x = new double[3];
  int counter = 0;
  auto g = [=](const double x){
    return x + f(x)*c;
  };

  x[1] = x0;
  x[0] = x0 + 1;
  while(check(ctype,x) && ++counter < MAX_IT)
  {
    x[2] = g(x[1]);
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }
    x[0] = x[1];
    x[1] = x[2];
  }
  return x[2];
}

// Slope
double rFunction::nr_method(function dfin, const double x_0)
{
  double* x = new double[3];
  int counter = 0;
  x[0] = x_0 + 1;
  x[1] = x_0;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = x[1] - f(x[1])/dfin(x[1]);
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }
    x[0] = x[1];
    x[1] = x[2];
  }

  return x[2];
}

double rFunction::mod_newton(function dfin, function ddfin, const double x0) const
{
  double* x = new double[3];
  int counter = 0;
  x[0] = x0 + 1;
  x[1] = x0;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = x[1] - (f(x[1])*dfin(x[1])) /
           ((dfin(x[1])*dfin(x[1])) - f(x[1])*ddfin(x[1]));

    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }
    x[0] = x[1];
    x[1] = x[2];
  }

  return x[2];
}

double rFunction::mod_newton(const double x0) const
{
  double* x = new double[3];
  int counter = 0;
  x[0] = x0 + 1;
  x[1] = x0;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = x[1] - (f(x[1])*df(x[1])) /
           ((df(x[1])*df(x[1])) - f(x[1])*ddf(x[1]));
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }
    x[0] = x[1];
    x[1] = x[2];
  }

  return x[2];
}

double rFunction::secant_method(const double x0, const double x1)
{
  double* x = new double[3];
  int counter = 0;
  x[0] = x0;
  x[1] = x1;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = x[1] - f(x[1])/df(x[1], x[0]);
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }

    x[0] = x[1];
    x[1] = x[2];
  }

  return x[2];
}

// Bracketing
double rFunction::bisection_method(const double xa, const double xb)
{
  int counter = 0;
  double* x = new double[3];
  x[0] = xa;
  x[1] = xb;
  try{
  if(mFunc(xa)*mFunc(xb) > 0) throw ErrorMsg::ROOT_NOT_IN_BOUNDS;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = (x[1] + x[0]) / 2;
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }
    if(f(x[2]) * f(x[1]) > 0)
    {
      x[1] = x[2];
    }
    else if(f(x[2]) * f(x[1]) < 0)
    {
      x[0] = x[2];
    }
  }
  }catch(const ErrorMsg& err){
    errObj.printerror(err);
    throw err;
  }

  return x[2];
}

double rFunction::rf_method(const double x0, const double x1)
{
  double* x = new double[3];
  int counter = 0;
  x[0] = x0;
  x[1] = x1;
  x[2] = x0;
  try{
  if(Function::mFunc(x[0]) * Function::mFunc(x[1]) > 0)
    throw ErrorMsg::ROOT_NOT_IN_BOUNDS;

  while(check(ctype, x) && ++counter < MAX_IT)
  {
    x[2] = x[1] - f(x[1])/df(x[1], x[0]);
    if(outputOptions != NULL)
    {
      outputStep(x, counter);
    }

    // To improve stability adding bisection
    if(x[2] - x[1] == 0 || x[2] - x[0] == 0)
    {
      x[2] = (x[1] + x[0])/2;
    }

    if(f(x[2]) * f(x[1]) > 0)
    {
      x[1] = x[2];
    }
    else if(f(x[2]) * f(x[1]) < 0)
    {
      x[0] = x[2];
    }
  }
  }catch(const ErrorMsg& err){
    errObj.printerror(err);
    throw err;
  }

  return x[2];

}

bool rFunction::checkabs(const double x1, const double x2) const
{
  return absErr(x1,x2) > TOLERANCE;
}
bool rFunction::checkrel(const double x1, const double x2) const
{
  return relErr(x1,x2) > TOLERANCE;
}
bool rFunction::checkzero(const double fx) const
{
  return zeroErr(fx) > TOLERANCE;
}
bool rFunction::check(const check_type ct, const double* inp) const
{
  switch(ct)
  {
    case check_type::ABSOLUTE:
      return checkabs(inp[0], inp[1]);
      break;
    case check_type::RELATIVE:
      return checkrel(inp[0], inp[1]);
      break;
    case check_type::ZERO:
      return checkzero(*inp);
      break;
    default:
      throw ErrorMsg::INVALID_OPTION;
  }
  return true;
}

double rFunction::absErr(const double x1, const double x2) const
{
  return std::abs(x1 - x2);
}
double rFunction::relErr(const double x1, const double x2) const
{
  return checkabs(x1,x2)/std::abs(x1);
}
double rFunction::zeroErr(const double fx) const
{
  return std::abs(fx);
}
double rFunction::getError(const check_type ct, const double* inp) const
{
  switch(ct)
  {
    case check_type::ABSOLUTE:
      return absErr(inp[0], inp[1]);
      break;
    case check_type::RELATIVE:
      return relErr(inp[0], inp[1]);
      break;
    case check_type::ZERO:
      return zeroErr(*inp);
      break;
    default:
      throw ErrorMsg::INVALID_OPTION;
  }
  return true;
}

void rFunction::outputStep(const double *stepData, const int step) const
{
  int width = 12;
  int prec = 6;
  if(outputOptions != NULL)
  {
    if(step%10 == 1)
      outputHeader();

    std::cout << std::setw(5) << std::setfill(' ') << std::left << step << ": ";
    for(int i=0; i < 5; ++i)
    {
      if(outputOptions[i])
      {
        switch((RF_Options)(i+1))
        {
          case RF_Options::SHOW_X2:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << stepData[2] << " ";
            break;
          case RF_Options::SHOW_X1:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << stepData[1] << " ";
            break;
          case RF_Options::SHOW_DX:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << std::abs(stepData[2] - stepData[1]) << " ";
            break;
          case RF_Options::SHOW_FX:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << f(stepData[1]) << " ";
            break;
          case RF_Options::SHOW_ERROR:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << getError(ctype, stepData+1) << " ";
            break;
          default:
            std::cout << "Error in outputStep...How did this happen?...\n";
        }
      }
    }
    std::cout << '\n';
  }
  return;
}

void rFunction::outputHeader() const
{
  int width = 12;
  int prec = 6;
  if(outputOptions != NULL)
  {
    std::cout << std::setw(5) << std::setfill(' ') << std::left << "Step" << ": ";
    for(int i=0; i < 5; ++i)
    {
      if(outputOptions[i])
      {
        switch((RF_Options)(i+1))
        {
          case RF_Options::SHOW_X2:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << "     X2     " << " ";
            break;
          case RF_Options::SHOW_X1:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << "     X1" << " ";
            break;
          case RF_Options::SHOW_DX:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << "  X2 - X1" << " ";
            break;
          case RF_Options::SHOW_FX:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << "   f(X1)" << " ";
            break;
          case RF_Options::SHOW_ERROR:
            std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                      << "   Error" << " ";
            break;
          default:
            std::cout << "Error in outputStep...How did this happen?...\n";
        }
      }
    }
    std::cout << '\n';
  }
  return;
}
