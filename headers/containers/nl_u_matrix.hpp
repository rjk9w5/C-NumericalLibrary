//////////////////////////////////////////////////////////////////////
/// @file nl_u_matrix.tpp
/// @author Ryan J. Krattiger (rjk9w5) 
/// @brief BRIEF_DESCRIPTION_HERE
//////////////////////////////////////////////////////////////////////

template <class T>
u_matrix<T>::u_matrix(): m_n(0), m_mat(), empty(0)
{}

template <class T>
u_matrix<T>& u_matrix<T>::operator = (u_matrix<T>&& other)

{
  m_n = other.m_n;
  m_mat = std::move(other.m_mat);

  return *this;
}

template <class T>
u_matrix<T>::u_matrix(u_matrix<T>&& other)
{
  *this=std::move(other);
}

template <class T>
u_matrix<T>& u_matrix<T>::operator = (const u_matrix<T>& src)
{
  m_n = src.m_n;
  m_mat = src.m_mat;

  return *this;
}

template <class T>
u_matrix<T>::u_matrix(const u_matrix<T>& src)
{
  *this=src;
}

template <class T>
u_matrix<T>::u_matrix(const size_t n):empty(0)
{
  size_t vecsize;
  m_n = n;
  vecsize = (n*(n+1))/2;
  m_mat.set_size(vecsize);
}

template <class T>
const T& u_matrix<T>::operator [] (const size_t i) const
{
  size_t r(0),c(0);
  while((r+1)*m_n < i)
    ++r;

  c = i - r*m_n;

  if(r > c) return empty;


  return m_mat(r,c);
}

template <class T>
T& u_matrix<T>::operator [] (const size_t i)
{
  size_t r(0),c(0);
  while((r+1)*m_n < i)
    ++r;

  c = i - r*m_n;

  if(r > c) return empty;

  return m_mat(r,c);
}

template <class T>
const T& u_matrix<T>::operator() (const size_t r, const size_t c) const
{
  if(r > c) return empty;
  size_t index;
  index = ((m_n-1-r)*((m_n-1-r)+1))/2 + c - r;
  return m_mat[index];
}

template <class T>
T& u_matrix<T>::operator() (const size_t r, const size_t c)
{
  if(r > c) return empty;
  size_t index;
  index = ((m_n-1-r)*((m_n-1-r)+1))/2 + c - r;
  return m_mat[index];
}

// FRIENDS
template <class T>
std::ostream& operator << (std::ostream& out, const u_matrix<T>& lmat)
{
  size_t field_width = 7;
  for(size_t r=0; r<lmat.m_n; ++r)
  {
    std::cout << std::setw((field_width+1)*r) << "";

    for(size_t c=r; c<lmat.m_n; ++c)
    {
      std::cout << std::setprecision(field_width/2) << std::setw(field_width) << std::left << lmat(r,c) << ' ';
    }
    std::cout << std::endl;
  }
  return out;
}

