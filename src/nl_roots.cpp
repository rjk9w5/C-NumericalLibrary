//////////////////////////////////////////////////////////////////////
/// @file nl_roots.cpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////
//*
#include "nl_roots.hpp"

// General
namespace numlib
{

  ldouble fpi(const functionX &gfunc,
              const ldouble x0)
  {
    ldouble* x = new ldouble[3];
    size_t counter = 0;

    x[1] = x0 + 1;
    x[2] = x0;
    x[0] = gfunc(x[2]) - x[2];
    std::cout << "this far: " << std::abs(df(gfunc,x[2])) << "\n";
    while(!check(x)
        && ++counter < MAX_IT
        && std::abs(df(gfunc,x[2])) <= 10)
    {
      x[1] = x[2];
      x[2] = gfunc(x[1]);
      x[0] = gfunc(x[2]) - x[2];
      outputStep(x, counter);
    }
    return x[2];
  }

  ldouble fpi(const functionX &func,
              const ldouble x0,
              const short cc)
  {
    ldouble c;
    if(cc==0)
      c = 1 / df(func,x0);
    else if(cc==2)
      c = -1 / df(func,x0);
    else
      c = cc;
    functionX tmpFunc = [=](const double x){
      return x - func(x)*c;
    };
    return fpi(tmpFunc, x0);
  }

  // Slope
  ldouble nr_method(const functionX &func,
                    const  functionX &dfunc,
                    const ldouble x0)
  {
    functionX tmpFunc = [&](const ldouble x)
        {return func(x)/dfunc(x);};

    return fpi(tmpFunc, x0,-1);
  }

  ldouble mod_nr_method(const functionX &func,
                     const functionX &dfunc,
                     const functionX &ddfunc,
                     const ldouble x0)
  {
    functionX tmpFunc = [&](const ldouble x)
        {return (func(x)*dfunc(x)) / (dfunc(x)*dfunc(x) - func(x)*ddfunc(x));};

    return fpi(tmpFunc, x0, 1);
  }

  ldouble mod_nr_method(const functionX &func,
                     const ldouble x0)
  {
    functionX tmpFunc = [&](const ldouble x)
        {return (func(x)*df(func,x)) / (df(func,x)*df(func,x) - func(x)*ddf(func,x));};

    return fpi(tmpFunc, x0, 1);
  }

  ldouble secant_method(const functionX &func,
                        const ldouble x0,
                        const ldouble x1)
  {
    ldouble* x = new ldouble[3];
    size_t counter = 0;
    x[0] = func(x1);
    x[1] = x0;
    x[2] = x1;
    while(!check(x) && ++counter < MAX_IT)
    {
      x[0] = x[1];
      x[1] = x[2];

      x[2] = x[1] - func(x[1])/df(func,x[1], x[1] - x[0]);

      x[0] = func(x[2]);

      outputStep(x, counter);
    }

    return x[2];
  }

  // Bracketing
  ldouble bisection_method(const functionX &func,
                           const ldouble xa,
                           const ldouble xb)
  {
    size_t counter = 0;
    ldouble* x = new ldouble[3];
    ldouble opsign=0;
    ldouble holdOld;
    x[0] = xa;
    x[1] = xb;

    if(func(xa)*func(xb) > 0) throw out_of_bounds();

    while(!check(x)
        && ++counter < MAX_IT)
    {
      if(opsign > 0)
      {
        x[0] = holdOld;
        x[1] = x[2];
      }
      else if(opsign < 0)
      {
        x[0] = x[2];
      }
      x[2] = (x[1] + x[0]) / 2;

      holdOld = x[0];
      x[0] = func(x[2]);

      opsign = func(x[2]) * func(x[1]);

      outputStep(x, counter);
    }

    return x[2];
  }

  ldouble rf_method(const functionX &func,
                    const ldouble x0,
                    const ldouble x1)
  {
    ldouble* x = new ldouble[3];
    ldouble tmp;
    ldouble opsign=0;
    ldouble holdOld;
    size_t counter = 0;
    x[0] = x0;
    x[1] = x1;
    x[2] = x0;

    if(func(x[0]) * func(x[1]) > 0)
      throw out_of_bounds();

    while(!check(x)
        && ++counter < MAX_IT)
    {
      if(opsign > 0)
      {
        x[0] = holdOld;
        x[1] = x[2];
      }
      else if(opsign < 0)
      {
        x[0] = x[2];
      }
      x[2] = x[1] - func(x[1])/df(func,x[1], x[1] - x[0]);

      // To improve stability, swap if it gets stuck
      if(x[2] - x[1] < TOLERANCE)
      {
        tmp = x[1];
        x[1] = x[0];
        x[0] = tmp;
        //std::cout << "\n\n\nSwapped!\n\n\n";
      }

      holdOld = x[0];
      x[0] = func(x[2]);

      opsign = func(x[2]) * func(x[1]);

      outputStep(x, counter);
    }

    return x[2];

  }

  void outputStep(const ldouble *stepData, const int step)
  {
    int width = 12;
    int prec = width/2;
    int n_opts;
    n_opts = 5;
    std::unique_ptr<nl_root_display[]> opts(new nl_root_display[n_opts]);
    nl_root_error errType;


    // Set Options by hand TODO: Abstract this
    errType = nl_root_error::RELATIVE;

    opts[0] = nl_root_display::SHOW_X1;
    opts[1] = nl_root_display::SHOW_X2;
    opts[2] = nl_root_display::SHOW_DX;
    opts[3] = nl_root_display::SHOW_FX;
    opts[4] = nl_root_display::SHOW_ERROR;

    if(step == 1)
      outputHeader(opts,n_opts);

    std::cout << std::setw(5) << std::setfill(' ') << std::left << step << '|';
    for(auto i = 0; i < n_opts; ++i)
    {
      switch(opts[i])
      {
        case nl_root_display::SHOW_X2:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << stepData[2] << '|';
          break;
        case nl_root_display::SHOW_X1:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << stepData[1] << '|';
          break;
        case nl_root_display::SHOW_DX:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << std::abs(stepData[2] - stepData[1]) << '|';
          break;
        case nl_root_display::SHOW_FX:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << stepData[0] << '|';
          break;
        case nl_root_display::SHOW_ERROR:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << getError(errType, stepData+1) << '|';
          break;
        default:
          std::cout << "Error in outputStep...How did this happen?...\n";
      }
    }
    std::cout << '\n';

    return;
  }

  void outputHeader(const std::unique_ptr<nl_root_display[]> &opts, const int n_opts)
  {
    int width = 12;
    int prec = 6;

    std::cout << std::setw(5) << std::setfill(' ') << std::left << "Step" << '|';
    for(int i=0; i < n_opts; ++i)
    {
      switch(opts[i])
      {
        case nl_root_display::SHOW_X2:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << "    Xn+1    " << '|';
          break;
        case nl_root_display::SHOW_X1:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << "     Xn     " << '|';
          break;
        case nl_root_display::SHOW_DX:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << "  Xn+1 - Xn " << '|';
          break;
        case nl_root_display::SHOW_FX:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << "   f(Xn+1)  " << '|';
          break;
        case nl_root_display::SHOW_ERROR:
          std::cout << std::setprecision(prec) << std::setw(width) << std::left << std::setfill(' ')
                    << "    (en)r   " << '|';
          break;
        default:
          std::cout << "Error in outputStep...How did this happen?...\n";
      }
    }

    std::cout << '\n';
    std::cout << std::setw(5) << std::setfill('_') << std::left << "" << '|';
    for(int i=0; i < n_opts; ++i)
      std::cout << std::setw(width) << std::setfill('_') << std::left << "" << '|';
    std::cout << '\n';
    return;
  }

  bool check(const ldouble* inp)
  {
    nl_root_error ct;
    ct = nl_root_error::RELATIVE;
    switch(ct)
    {
      case nl_root_error::ABSOLUTE:
        return absErr(inp[1], inp[2]) < TOLERANCE;
        break;
      case nl_root_error::RELATIVE:
        return relErr(inp[1], inp[2]) < TOLERANCE;
        break;
      case nl_root_error::ZERO:
        return zeroErr(*inp) < TOLERANCE;
        break;
      default:
        throw input_error();
    }
    return true;
  }

  ldouble absErr(const ldouble x0, const ldouble x1)
  {
    return std::abs(x0 - x1);
  }

  ldouble relErr(const ldouble x0, const ldouble x1)
  {
    return (std::abs(x1) > TOLERANCE ? std::abs((x1 - x0)/x1) : absErr(x0,x1));
  }

  ldouble zeroErr(const ldouble fx)
  {
    return std::abs(fx);
  }

  ldouble getError(const nl_root_error ct, const ldouble* inp)
  {
    {
      switch(ct)
      {
        case nl_root_error::ABSOLUTE:
          return absErr(inp[0], inp[1]);
          break;
        case nl_root_error::RELATIVE:
          return relErr(inp[0], inp[1]);
          break;
        case nl_root_error::ZERO:
          return zeroErr(*inp);
          break;
        default:
          throw input_error();
      }
      return true;
    }
  }

} // End namespace numlib
