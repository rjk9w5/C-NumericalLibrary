/*
 * vector.hpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Declarations of vector template class and associated
 *              friend functions
 */

template <class T>
nl::Vector<T>::Vector()
{
  size_ = 0;
  vert_ = true;
  data_ = nullptr;
}

template <class T>
nl::Vector<T>::Vector(const size_t size)
{
  size_ = 0;
  vert_ = true;
  data_ = new T[size];
}

template <class T>
nl::Vector<T>::Vector(const size_t size, const T& value)
{
  size_ = 0;
  vert_ = true;
  data_ = new T[size];
  for(size_t i=0; i < size_; ++i)
  {
    data_[i] = value;
  }
}

template <class T>
nl::Vector<T>& nl::Vector<T>::operator=(const nl::Vector<T>& src)
{
  //std::cerr << "Okay Here\n";
  if(this != &src)
  {
    clear();
    // TODO: Figure out how to make copy and swap technique work.
    size_ = src.size_;
    vert_ = true;
    data_ = new T[size_];
    for(size_t i = 0; i < size_; ++i)
    {
      data_[i] = src.data_[i];
    }
  }

  return *this;
}

template <class T>
nl::Vector<T>::Vector(const nl::Vector<T>& src)
{
  *this = src;
}

template <class T>
nl::Vector<T>& nl::Vector<T>::operator=(nl::Vector<T> &&other)
{
  if(this != &other)
  {
    clear();
    size_ = other.size_;
    vert_ = other.vert_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  return *this;
}

template <class T>
nl::Vector<T>::Vector(nl::Vector<T> &&other)
{
  *this = std::move(other);
}

template <class T>
nl::Vector<T>::~Vector()
{
  clear();
}

template <class T>
void nl::Vector<T>::resize(const size_t size)
{
  T* tmp = nullptr;
  size_t nit = (size > size_?size_:size);
  if(size < 0) nl::FatalError("nl::Vector<T>::resize(const size_t size):" \
                              " Input size must be greater than or equal to"\
                              " zero!\n");

  if(data_ != nullptr && size_ && size)
  {
    tmp = new T[size_];
    for(size_t i=0; i < size_; ++i)
    {
      tmp[i] = data_[i];
    }
  }
  clear();
  data_ = new T[size];

  if(tmp != nullptr)
  {
    for(size_t i=0; i < nit; ++i)
    {
      data_[i] = tmp[i];
    }
  }
  size_ = size;

  return;
}

template <class T>
void nl::Vector<T>::reuse(const size_t size)
{
  clear();
  if(size > 0)
    data_ = new T[size];
  else
    data_ = nullptr;

  size_ = size;

  return;
}

template <class T>
void nl::Vector<T>::clear()
{
  if(data_ != nullptr)
    delete[] data_;

  data_ = nullptr;
  size_ = 0;

  return;
}

template <class T>
void nl::Vector<T>::set_size(const size_t size, const size_t vert)
{
  if(vert == 1)
  {
    vert_ = true;
    reuse(size);
  }
  else if(size == 1 && vert != 1)
  {
    vert_ = false;
    reuse(vert);
  }
  else if(size != 1 && vert != 1)
  {
    throw nl::FatalError("nl::Vector: set_size: A vector cannot handle this!");
  }

  return;
}

template <class T>
void nl::Vector<T>::remove(const size_t i)
{
  if(i < size_ && i >=0)
  {
    for(size_t j = i; j < size_ - 1; ++j)
      data_[j] = data_[j+1];

    size_--;
  }
  else
  {
    throw nl::FatalError("nl::Vector<T>::remove(const size_t i): "\
                         "Index 'i' is out of range\n");
  }

  return;
}

template <class T>
const T& nl::Vector<T>::operator[](const size_t i) const
{
  if(i > size_ || i < 0)
  {
    throw nl::FatalError("nl::Vector<T>::operator[](const size_t i) const: "\
                         "Index 'i' is out of range\n");
  }

  return data_[i];
}

template <class T>
T& nl::Vector<T>::operator[](const size_t i)
{
  if(i > size_ || i < 0)
  {
    throw nl::FatalError("nl::Vector<T>::operator[](const size_t i): "\
                         "Index 'i' is out of range\n");
  }

  return data_[i];
}

// Must have < operator implemented
template <class T>
nl::Vector<T>& nl::Vector<T>::sort()
{
  if(!std::is_sorted(begin(), end()))
    std::sort(begin(), end());

  return *this;
}

template <class T>
T* nl::Vector<T>::begin() const
{
  return data_;
}

template <class T>
T* nl::Vector<T>::end() const
{
  return data_+ size_;
}

// TODO: Fix this someday
/*
template <class T>
nl::Vector<T>
  nl::Vector<T>::slice
      (const T* start, const T* stop, const size_t step) const
{
  size_t slice_size = size_/step +
                      ((size_%step||step>size_)&&size_!=step?1:0);

  if(step <= 0 && start > begin() && stop < end())
    throw nl::FatalError("nl::Vector<T>::slice(const T* start, const T* stop, "\
                         "const size_t step): Invalid inputs!\n");

  nl::Vector<T> ret(slice_size);
  size_t i=0;
  const T* it = start;
  for(; it<stop; it+=step)
    ret[i++] = *it;

  return ret;
}
*/

template <class T>
int nl::Vector<T>::find(const T& value)
{
  size_t i_left=0;
  size_t i_right = size_-1;
  size_t index = (i_right - i_left)/2;

  if(data_[i_right] == value) return i_right;
  if(data_[i_left] == value) return i_left;

  while(data_[index] != value)
  {
    if(data_[index] > value)
    {
      i_right = index;
      index = i_left + (i_right - i_left)/2;
    }
    else if(data_[index] < value)
    {
          i_left = index;
          index = i_left + (i_right - i_left)/2;
    }

    if(i_left == index) return -1;
  }

  return index;
}

// MATH
template <class T>
T nl::Vector<T>::dot(const nl::Vector<T>& vec) const
{
  if(vec.get_size() != get_size())
    throw nl::FatalError("nl::Vector<T>::dot(const nl::Vector<T>& vec): "\
                         "Vectors must be of same size!\n");

  T ret;
  size_t it = 0;
  for(auto& val: *this)
    ret += val*vec[it++];

  return ret;
}

template <class T>
T nl::dot(const nl::Vector<T>& v1, const nl::Vector<T>& v2)
{
  return v1.dot(v2);
}

template <class T>
T nl::Vector<T>::operator * (const nl::Vector<T>& vec) const
{
  return dot(vec);
}

template <class T>
nl::Vector<T> nl::Vector<T>::operator * (const T& C) const
{
  nl::Vector<T> ret(*this);
  size_t it=-1;
  for(auto& val: *this)
    ret[++it] = val*C;

  return  ret;
}

template <class T>
nl::Vector<T> nl::Vector<T>::operator / (const nl::Vector<T>& v2) const
{
  if(v2.get_size() != get_size())
    throw nl::FatalError("nl::Vector<T>::operator / " \
                         "(const nl::Vector<T>& v2): "\
                         "Vectors must be of same size!\n");

  nl::Vector<T> ret(*this);
  size_t it =0;
  for(auto& val: v2)
  {
    ret[it++] /= val;
  }
  return ret;
}

template <class T>
nl::Vector<T> nl::Vector<T>::operator / (const T& C) const
{
  nl::Vector<T> ret(*this);
  size_t it =0;
  for(auto& val: ret)
  {
    ret[it++] /= C;
  }
  return ret;
}

template <class T>
nl::Vector<T> nl::operator * (const T& C, const nl::Vector<T>& v2)
{
    return v2*C;
}

template <class T>
nl::Vector<T>& nl::Vector<T>::operator += (const nl::Vector<T>& vec)
{
  if(vec.get_size() != get_size())
    throw nl::FatalError("nl::Vector<T>::operator += " \
                             "(const nl::Vector<T>& vec): "\
                             "Vectors must be of same size!\n");

  size_t it=0;
  for(auto& val: vec)
    this -> operator[](it++) += val;

  return *this;
}

template <class T>
nl::Vector<T> nl::operator + (const nl::Vector<T>& v1,
                                  const nl::Vector<T>& v2)
{
  nl::Vector<T> ret(v1);

  return ret += v2;
}

template <class T>
nl::Vector<T>& nl::Vector<T>::operator -= (const nl::Vector<T>& vec)
{
  if(get_size() != vec.get_size())
    throw nl::FatalError("nl::operator - (const nl::Vector<T>& v1," \
                         "const nl::Vector<T>& v2): "                 \
                         "Vectors must be of same size!\n");
  size_t it=-1;
  for(auto& val: vec)
    this -> operator[](++it) -= val;

  return *this;
}

template <class T>
nl::Vector<T> nl::operator - (const nl::Vector<T>& v1,
                            const nl::Vector<T>& v2)
{
  nl::Vector<T> ret(v1);

  return ret-=v2;
}

template <class T>
nl::Vector<T> nl::operator - (const nl::Vector<T>& vec)
{
  nl::Vector<T> ret(vec);
  size_t it=-1;
  for(auto& val: vec)
    ret[++it] = -val;

  return ret;
}

template <class T>
bool nl::operator == (const nl::Vector<T>& lhs,
                  const nl::Vector<T>& rhs)
{
  size_t i = 0;
  if(lhs.size_ == rhs.size_)
  {
    while(i < lhs.size_ && rhs.data_[i] == lhs.data_[i])
    {
      ++i;
    }
  }

  return (i==rhs.size_ && i==lhs.size_)?true:false;
}

template <class T>
bool nl::operator != (const nl::Vector<T>& lhs, const nl::Vector<T>& rhs)
{
    return !(lhs==rhs);
}

template <class T>
std::ostream& nl::operator<<(std::ostream& out, const nl::Vector<T>& vec)
{
  for(size_t i=0; i<vec.size_; ++i)
  {
    out << std::setprecision(5)
        << std::setw(10)
        << std::left
        << std::setfill(' ')
        << vec[i];
  }
  out << '\n';
  return out;
}

template <class T>
std::istream& nl::operator>>(std::istream& in, nl::Vector<T>& vec)
{
  for(size_t i=0; i<vec.size_ && in.good(); ++i)
  {
    in >> vec[i];
  }

  //std::cout << (!in.good()?"Sees eof":"Sees happiness") << '\n';
  return in;
}

template <class T>
nl::Vector<T> cat(const nl::Vector<T>& a1, const nl::Vector<T>& a2)
{
  nl::Vector<T> ret(a1.get_size() + a2.get_size());
  int i=-1;
  for(auto& val: a1)
    ret[++i] = val;

  for(auto& val: a2)
    ret[++i] = val;

   return ret;
}

template <class T>
T nl::Vector<T>::sum() const
{
  T sm=0;
  for(auto& val: *this)
  {
    sm += val;
  }
  return sm;
}

template <class T>
T nl::sum(const nl::Vector<T>& vec)
{
  return vec.sum();
}

template <class T>
nl::Vector<T> sqrt(const nl::Vector<T>& vec)
{
  nl::Vector<T> ret(vec.get_size());
  size_t it = 0;

  for(auto& val: vec)
  {
    ret[it++] = sqrt(val);
  }

  return ret;
}

template <class T>
nl::Vector<T> abs(const nl::Vector<T>& vec)
{
  nl::Vector<T> ret(vec.get_size());
  size_t it = 0;

  for(auto& val: vec)
  {
    ret[it++] = abs(val);
  }

  return ret;
}
