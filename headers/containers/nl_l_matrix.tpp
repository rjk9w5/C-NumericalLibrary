//////////////////////////////////////////////////////////////////////
/// @file nl_l_matrix.tpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

template <class T>
l_matrix<T>::l_matrix(): m_n(0), m_mat(), empty(0)
{}

template <class T>
l_matrix<T>& l_matrix<T>::operator = (l_matrix<T>&& other)

{
  m_n = other.m_n;
  m_mat = std::move(other.m_mat);

  return *this;
}

template <class T>
l_matrix<T>::l_matrix(l_matrix<T>&& other)
{
  *this=std::move(other);
}

template <class T>
l_matrix<T>& l_matrix<T>::operator = (const l_matrix<T>& src)
{
  m_n = src.m_n;
  m_mat = src.m_mat;

  return *this;
}

template <class T>
l_matrix<T>::l_matrix(const l_matrix<T>& src)
{
  *this=src;
}

template <class T>
l_matrix<T>::l_matrix(const size_t n):empty(0)
{
  size_t vecsize;
  m_n = n;
  vecsize = (n*(n+1))/2;
  m_mat.set_size(vecsize);
}

template <class T>
const T& l_matrix<T>::operator [] (const size_t i) const
{
  size_t r(0),c(0);
  while((r+1)*m_n < i)
    ++r;

  c = i - r*m_n;

  if(r < c) return empty;

  return m_mat(r,c);
}

template <class T>
T& l_matrix<T>::operator [] (const size_t i)
{
  size_t r(0),c(0);
  while((r+1)*m_n < i)
    ++r;

  c = i - r*m_n;

  if(r < c) return empty;

  return m_mat(r,c);
}

template <class T>
const T& l_matrix<T>::operator() (const size_t r, const size_t c) const
{
  if(r < c) return empty;
  size_t index;
  index = (r*(r+1))/2 + c;
  return m_mat[index];
}

template <class T>
T& l_matrix<T>::operator() (const size_t r, const size_t c)
{
  if(r < c) return empty;
  size_t index;
  index = (r*(r+1))/2 + c;
  return m_mat[index];
}

// FRIENDS
template <class T>
std::ostream& operator << (std::ostream& out, const l_matrix<T>& lmat)
{
  size_t field_width = 7;
  for(size_t r=0; r<lmat.m_n; ++r)
  {
    for(size_t c=0; c<=r; ++c)
    {
      //std::cout << r << ' ' << c << std::endl;
      std::cout << std::setprecision(field_width/2) << std::setw(field_width) << std::left << lmat(r,c) << ' ';
    }
    std::cout << std::endl;
  }
  return out;
}
