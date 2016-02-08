//////////////////////////////////////////////////////////////////////
/// @file options.hpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief Options object for use by solvers to control functionality
//////////////////////////////////////////////////////////////////////

// TODO: Priority=LOW; Design and Implement options functionality.
#ifndef NL_OPTIONS_HPP_
#define NL_OPTIONS_HPP_
//*
#include <memory>

enum class nl_root_display
{
  SHOW_X1, SHOW_X2, SHOW_DX, SHOW_FX, SHOW_ERROR, NOPTS
};

enum class nl_root_method
{
  FPI, NEWTON, MODNEWTON, SECANT, BISECTION, REGULAFALSI, NOPTS=-1
};

enum class nl_root_error: int
{
  ZERO, RELATIVE, ABSOLUTE
};
/*
template <class OPT_TYPE>
class option_list
{
  public:
    option_list()
    {
      if(OPT_TYPE::NOPTS < 0)
      {
        m_nopts = 1;
      }
      else
      {
        m_nopts = OPT_TYPE::NOPTS;
      }

      if(m_opts != nullptr)
        options.reset(new OPT_TYPE[m_nopts]);

      options = new OPT_TYPE[m_nopts];
      for(int i=0; i<m_nopts; ++i)
      {
        options[i] = false;
      }
    }

    option_list(const option_list<OPT_TYPE> opt)
    {
      *this = opt;
    }

    option_list<OPT_TYPE>& operator=(const option_list<OPT_TYPE> opt)
    {
      if(this != &opt)
      {
        if(OPT_TYPE::NOPTS < 0)
        {
          m_nopts = 1;
        }
        else
        {
          m_nopts = OPT_TYPE::NOPTS;
        }

        if(m_opts != nullptr)
          options.reset(new OPT_TYPE[m_nopts]);

        options = new OPT_TYPE[m_nopts];

        for(int i=0; i<m_nopts; ++i)
        {
          options[i] = opt.options[i];
        }
      }

      return *this;
    }

    virtual void set_options(const std::unique_ptr<OPT_TYPE> opt, size_t nopts) =0;

  private:
    std::unique_ptr<bool[]> options;
    size_t m_nopts;
};

class root_display: option_list<nl_root_display_options>
{
  root_display(const nl_root_display_options* opts, size_t nopts);
  void set_options(const std::unique_ptr<nl_root_display_options[]> opt, size_t nopts)
  {

    return;
  }
};

*/
#endif /* NL_OPTIONS_HPP_ */
