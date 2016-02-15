/*
 * vector.tpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Declarations of vector template class and associated
 *              friend functions
 */

template <class T>
vector<T>::vector()
{
  m_size = 0;
  m_max = 0;
  m_data.reset(nullptr);
}

template <class T>
vector<T>::vector(const size_t size)
{
  resize(size);
}

template <class T>
vector<T>::vector(const size_t size, const T& value)
{
  resize(size);
  for(size_t i=0; i < m_size; ++i)
  {
    m_data[i] = value;
  }
}

template <class T>
vector<T>& vector<T>::operator=(const vector<T>& src)
{
  if(this != &src)
  {
    m_size = src.m_size;
    m_max = src.m_max;

    m_data.reset(new T[m_size]);

    for(size_t i = 0; i < m_size; ++i)
    {
      m_data[i] = src.m_data[i];
    }
  }

  return *this;
}

template <class T>
vector<T>::vector(const vector<T>& src)
{
  *this = src;
}

template <class T>
vector<T>& vector<T>::operator=(vector<T> &&other)
{
  std::cout << "MOVED!!\n";
  if(this != &other)
  {
    m_size = other.m_size;
    m_max = other.m_max;

    m_data = std::move(other.m_data);
    other.m_data.reset(nullptr);
  }

  return *this;
}

template <class T>
vector<T>::vector(vector<T> &&other)
{
  *this = std::move(other);
}

template <class T>
vector<T>::~vector()
{
}

template <class T>
void vector<T>::resize(const size_t size)
{
  std::unique_ptr<T[]> tmp;
  size_t nit = (size > m_size?m_size:size);
  if(size < 0) std::exception();

  if(m_data != nullptr && m_size > 0 && size)
  {
    tmp.reset(new T[m_size]);
    for(size_t i=0; i < m_size; ++i)
    {
      tmp[i] = m_data[i];
    }
  }
  m_data.reset(new T[size]);
  if(tmp != nullptr)
  {
    for(size_t i=0; i < nit; ++i)
    {
      m_data[i] = tmp[i];
    }
  }
  m_size = size;
  m_max = size;

  return;
}

template <class T>
void vector<T>::reuse(const size_t size)
{
  if(size=0)
  {
    m_data.reset(nullptr);
    m_size = 0;
    m_max = 0;
  }
  else
  {
    this -> reuse();
    this -> resize(size);
  }
    return;
}

template <class T>
void vector<T>::set_size(const size_t size)
{
  this->resize(size);
  return;
}

template <class T>
void vector<T>::remove(const size_t i)
{
  if(i < m_size && m_size > 0 && i >=0)
  {
    for(size_t j = i; j < m_size - 1; ++j)
      m_data[j] = m_data[j+1];

    m_size--;
  }
  else
  {
    throw std::range_error("auto_array: remove: index 'i' is out of range\n");
  }

  return;
}

template <class T>
const T& vector<T>::operator[](const size_t i) const
{
  if(i > m_size || i < 0)
  {
    throw std::range_error("auto_array: subscript []: "\
        "index 'i' is out of range");
  }

  return m_data[i];
}

template <class T>
T& vector<T>::operator[](const size_t i)
{
  if(i > m_size || i < 0)
  {
    throw std::range_error("auto_array: subscript []: "\
        "index 'i' is out of range");
  }

  return m_data[i];
}

// Must have < operator implemented
template <class T>
void vector<T>::sort()
{
  if(!std::is_sorted(m_data.get(), m_data.get()+m_size))
    std::sort(m_data.get(), m_data.get()+m_size);
  //else
    //std::cout << "No need to sort!\n";

  return;
}

template <class T>
T* vector<T>::begin()
{
  return m_data.get();
}

template <class T>
T* vector<T>::end()
{
  return m_data.get() + m_size;
}

template <class T>
vector<T> vector<T>::slice(const T* start, const T* stop, const size_t step)
{
  size_t slice_size = m_size/step +
                      ((m_size%step||step>m_size)&&m_size!=step?1:0);

  if(slice_size <= 0) throw std::exception();

  vector<T> ret(slice_size);
  size_t i=-1;
  const T* it = start;
  for(; it<stop; it+=step)
    ret[++i] = *it;

  return ret;
}

// MATH
template <class T>
vector<T> dot(const vector<T>& v1, const vector<T>& v2)
{
  if(v1.get_size() != v2.get_size()) throw std::exception();

  vector<T> ret(v1.get_size());
  size_t it=-1;
  for(auto val: v1)
  {
    ret[++it] += (val*v2[it]);
  }

  return ret;
}

template <class T>
vector<T> operator * (const vector<T>& v1, const vector<T>& v2)
{
  return dot(v1,v2);
}

template <class T>
vector<T> operator * (const T& C, const vector<T>& v2)
{
  vector<T> ret(v2.get_size());
  size_t it=-1;
  for(auto val: v2)
    ret[++it] = val*C;

  return  ret;
}

template <class T>
vector<T> operator * (const vector<T>& v1, const T& C)
{
  return C*v1;
}

template <class T>
const vector<T>& vector<T>::operator += (const vector<T>& vec)
{
  if(vec.get_size() != get_size()) throw std::exception();

  size_t it=-1;
  for(auto val: *this)
    *this[++it] += vec[it];

  return *this;
}

template <class T>
vector<T> operator + (const vector<T>& v1, const vector<T>& v2)
{
  vector<T> ret(v1);
  ret+=v2;

  return ret;
}

template <class T>
vector<T> operator - (const vector<T>& v1, const vector<T>& v2)
{
  if(v1.get_size() != v2.get_size()) throw std::exception();

  vector<T> ret(v1.get_size());
  size_t it=-1;
  for(auto val: v1)
    ret[++it] = val-v2[it];

  return ret;
}

template <class T>
vector<T> operator - (const vector<T>& vec)
{
  vector<T> ret(vec);
  size_t it=-1;
  for(auto val: vec)
    ret[++it] = -val;

  return ret;
}

template <class T>
bool operator == (const vector<T>& lhs, const vector<T>& rhs)
{
  size_t i = 0;
  if(lhs.m_size == rhs.m_size)
  {
    while(i < lhs.m_size && rhs.m_data[i] == lhs.m_data[i])
    {
      ++i;
    }
  }

  return (i==rhs.m_size && i==lhs.m_size)?true:false;
}

template <class T>
bool operator != (const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs==rhs);
}

template <class T>
std::ostream& operator<<(std::ostream& out, const vector<T>& vec)
{
  for(int i=0; i<vec.m_size; ++i)
  {
    out << vec[i] << ' ';
  }

  return out;
}

template <class T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
  for(int i=0; i<vec.m_size; ++i)
  {
    in >> vec[i];
  }

  return in;
}

template <class T>
vector<T> cat(const vector<T>& a1, const vector<T>& a2)
{
  vector<T> ret(a1.get_size() + a2.get_size());
  int i=-1;
  for(auto val: a1)
    ret[++i] = val;

  for(auto val: a2)
    ret[++i] = val;

   return ret;
}
