/*
 * vector.hpp
 *
 *  Created on: Feb 5, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: Declarations of vector template class and associated
 *              friend functions
 */

template <class T>
oonm::Vector<T>::Vector()
{
  size_ = 0;
  data_ = nullptr;
}

template <class T>
oonm::Vector<T>::Vector(const size_t size)
{
  size_ = 0;
  data_ = new T[size];
}

template <class T>
oonm::Vector<T>::Vector(const size_t size, const T& value)
{
  size_ = 0;
  data_ = new T[size];
  for(size_t i=0; i < size_; ++i)
  {
    data_[i] = value;
  }
}

template <class T>
oonm::Vector<T>& oonm::Vector<T>::operator=(const oonm::Vector<T>& src)
{
  //std::cerr << "Okay Here\n";
  if(this != &src)
  {
    //this -> clear();
    // TODO: Figure out how to make copy and swap technique work.
    size_ = src.size_;

    data_ = new T[size_];

    for(size_t i = 0; i < size_; ++i)
    {
      data_[i] = src.data_[i];
    }
  }

  return *this;
}

template <class T>
oonm::Vector<T>::Vector(const oonm::Vector<T>& src)
{
  *this = src;
}

template <class T>
oonm::Vector<T>& oonm::Vector<T>::operator=(oonm::Vector<T> &&other)
{
  if(this != &other)
  {
    clear();
    size_ = other.size_;

    data_ = other.data_;
    other.data_ = nullptr;
  }

  return *this;
}

template <class T>
oonm::Vector<T>::Vector(oonm::Vector<T> &&other)
{
  *this = std::move(other);
}

template <class T>
oonm::Vector<T>::~Vector()
{
  clear();
}

template <class T>
void oonm::Vector<T>::resize(const size_t size)
{
  T* tmp = nullptr;
  size_t nit = (size > size_?size_:size);
  if(size < 0) nl::FatalError("oonm::Vector<T>::resize(const size_t size):" \
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
void oonm::Vector<T>::reuse(const size_t size)
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
void oonm::Vector<T>::clear()
{
  if(data_ != nullptr && size_ > 0)
    delete[] data_;

  size_ = 0;

  return;
}

template <class T>
void oonm::Vector<T>::set_size(const size_t size)
{
  this->reuse(size);
  return;
}

template <class T>
void oonm::Vector<T>::remove(const size_t i)
{
  if(i < size_ && i >=0)
  {
    for(size_t j = i; j < size_ - 1; ++j)
      data_[j] = data_[j+1];

    size_--;
  }
  else
  {
    throw nl::FatalError("oonm::Vector<T>::remove(const size_t i): "\
                         "Index 'i' is out of range\n");
  }

  return;
}

template <class T>
const T& oonm::Vector<T>::operator[](const size_t i) const
{
  if(i > size_ || i < 0)
  {
    throw nl::FatalError("oonm::Vector<T>::operator[](const size_t i) const: "\
                         "Index 'i' is out of range\n");
  }

  return data_[i];
}

template <class T>
T& oonm::Vector<T>::operator[](const size_t i)
{
  if(i > size_ || i < 0)
  {
    throw nl::FatalError("oonm::Vector<T>::operator[](const size_t i): "\
                         "Index 'i' is out of range\n");
  }

  return data_[i];
}

// Must have < operator implemented
template <class T>
oonm::Vector<T>& oonm::Vector<T>::sort()
{
  if(!std::is_sorted(begin(), end()))
    std::sort(begin(), end());

  return *this;
}

template <class T>
T* oonm::Vector<T>::begin() const
{
  return data_;
}

template <class T>
T* oonm::Vector<T>::end() const
{
  return data_+ size_;
}

// TODO: Fix this someday
//template <class T>
//oonm::Vector<T> oonm::Vector<T>::slice(const T* start, const T* stop, const size_t step) const
//{
//  size_t slice_size = size_/step +
//                      ((size_%step||step>size_)&&size_!=step?1:0);
//
//  if(step <= 0 && start > begin() && stop < end())
//    throw nl::FatalError("oonm::Vector<T>::slice(const T* " \
//                         "start, const T* stop, const "     \
//                         "size_t step): Invalid inputs!!\n");
//
//  oonm::Vector<T> ret(slice_size);
//  size_t i=0;
//  const T* it = start;
//  for(; it<stop; it+=step)
//    ret[i++] = *it;
//
//  return ret;
//}

template <class T>
int oonm::Vector<T>::find(const T& value)
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
T oonm::Vector<T>::dot(const oonm::Vector<T>& vec) const
{
  if(vec.get_size() != get_size())
    throw nl::FatalError("oonm::Vector<T>::dot(const oonm::Vector<T>& vec): "\
                         "Vectors must be of same size!\n");

  T ret;
  size_t it = 0;
  for(auto& val: *this)
    ret += val*vec[it++];

  return ret;
}

template <class T>
T oonm::dot(const oonm::Vector<T>& v1, const oonm::Vector<T>& v2)
{
  return v1.dot(v2);
}

template <class T>
T oonm::Vector<T>::operator * (const oonm::Vector<T>& vec) const
{
  return dot(vec);
}

template <class T>
oonm::Vector<T> oonm::Vector<T>::operator * (const T& C) const
{
  oonm::Vector<T> ret(*this);
  size_t it=-1;
  for(auto& val: *this)
    ret[++it] = val*C;

  return  ret;
}

template <class T>
oonm::Vector<T> oonm::Vector<T>::operator / (const oonm::Vector<T>& v2) const
{
  if(v2.get_size() != get_size())
    throw nl::FatalError("oonm::Vector<T>::operator / " \
                         "(const oonm::Vector<T>& v2): "\
                         "Vectors must be of same size!\n");

  oonm::Vector<T> ret(*this);
  size_t it =0;
  for(auto& val: v2)
  {
    ret[it++] /= val;
  }
  return ret;
}

template <class T>
oonm::Vector<T> oonm::Vector<T>::operator / (const T& C) const
{
  oonm::Vector<T> ret(*this);
  size_t it =0;
  for(auto& val: ret)
  {
    ret[it++] /= C;
  }
  return ret;
}

template <class T>
oonm::Vector<T> oonm::operator * (const T& C, const oonm::Vector<T>& v2)
{
    return v2*C;
}

template <class T>
oonm::Vector<T>& oonm::Vector<T>::operator += (const oonm::Vector<T>& vec)
{
  if(vec.get_size() != get_size())
    throw nl::FatalError("oonm::Vector<T>::operator += " \
                             "(const oonm::Vector<T>& vec): "\
                             "Vectors must be of same size!\n");

  size_t it=0;
  for(auto& val: vec)
    this -> operator[](it++) += val;

  return *this;
}

template <class T>
oonm::Vector<T> oonm::operator + (const oonm::Vector<T>& v1,
                                  const oonm::Vector<T>& v2)
{
  oonm::Vector<T> ret(v1);

  return ret += v2;
}

template <class T>
oonm::Vector<T>& oonm::Vector<T>::operator -= (const oonm::Vector<T>& vec)
{
  if(get_size() != vec.get_size())
    throw nl::FatalError("oonm::operator - (const oonm::Vector<T>& v1," \
                         "const oonm::Vector<T>& v2): "                 \
                         "Vectors must be of same size!\n");
  size_t it=-1;
  for(auto& val: vec)
    this -> operator[](++it) -= val;

  return *this;
}

template <class T>
oonm::Vector<T> oonm::operator - (const oonm::Vector<T>& v1,
                            const oonm::Vector<T>& v2)
{
  oonm::Vector<T> ret(v1);

  return ret-=v2;
}

template <class T>
oonm::Vector<T> oonm::operator - (const oonm::Vector<T>& vec)
{
  oonm::Vector<T> ret(vec);
  size_t it=-1;
  for(auto& val: vec)
    ret[++it] = -val;

  return ret;
}

template <class T>
bool oonm::operator == (const oonm::Vector<T>& lhs,
                  const oonm::Vector<T>& rhs)
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
bool oonm::operator != (const oonm::Vector<T>& lhs, const oonm::Vector<T>& rhs)
{
    return !(lhs==rhs);
}

template <class T>
std::ostream& oonm::operator<<(std::ostream& out, const oonm::Vector<T>& vec)
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
std::istream& oonm::operator>>(std::istream& in, oonm::Vector<T>& vec)
{
  for(size_t i=0; i<vec.size_ && in.good(); ++i)
  {
    in >> vec[i];
  }

  //std::cout << (!in.good()?"Sees eof":"Sees happiness") << '\n';
  return in;
}

template <class T>
oonm::Vector<T> cat(const oonm::Vector<T>& a1, const oonm::Vector<T>& a2)
{
  oonm::Vector<T> ret(a1.get_size() + a2.get_size());
  int i=-1;
  for(auto& val: a1)
    ret[++i] = val;

  for(auto& val: a2)
    ret[++i] = val;

   return ret;
}

template <class T>
T oonm::Vector<T>::sum() const
{
  T sm=0;
  for(auto& val: *this)
  {
    sm += val;
  }
  return sm;
}

template <class T>
T oonm::sum(const oonm::Vector<T>& vec)
{
  return vec.sum();
}

template <class T>
oonm::Vector<T> sqrt(const oonm::Vector<T>& vec)
{
  oonm::Vector<T> ret(vec.get_size());
  size_t it = 0;

  for(auto& val: vec)
  {
    ret[it++] = sqrt(val);
  }

  return ret;
}

template <class T>
oonm::Vector<T> abs(const oonm::Vector<T>& vec)
{
  oonm::Vector<T> ret(vec.get_size());
  size_t it = 0;

  for(auto& val: vec)
  {
    ret[it++] = abs(val);
  }

  return ret;
}
