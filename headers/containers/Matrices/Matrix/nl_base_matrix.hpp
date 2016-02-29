/*
 * nl_base_matrix.hpp
 *
 *  Created on: Feb 28, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */


template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::Matrix()
{
  rows_ = 0;
  cols_ = 0;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::Matrix(const size_t n, const size_t m)
{
  rows_ = n;
  cols_ = m;
  data_.set_size(n*m);
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::Matrix(const size_t n, const size_t m, const Ele_T& default_val)
{
  rows_ = n;
  cols_ = m;
  data_.set_size(n*m, default_val);
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>&
  nl::Matrix<Form_T, Ele_T>::operator =
      (const nl::Matrix<Form_T, Ele_T>& src)
{
  if(this != &src)
  {
    rows_ = src.rows_;
    cols_ = src.cols_;
    data_ = src.data_;
  }

  return *this;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::Matrix(const nl::Matrix<Form_T, Ele_T>& src)
{
  *this = src;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>&
  nl::Matrix<Form_T, Ele_T>::operator =
      (const nl::Matrix<Form_T, Ele_T>&& other)
{
  if(this != &other)
  {
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = std::move(other.data_);
  }

  return *this;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::Matrix(nl::Matrix<Form_T, Ele_T>&& other)
{
  *this = std::move(other);
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>::~Matrix()
{
}

template <class Form_T, class Ele_T>
Ele_T& nl::Matrix<Form_T, Ele_T>::operator()(const size_t i, const size_t j)
{
  if(i>rows_ || j>cols_)
    throw nl::FatalError("");

  return data_[i*cols_ + j];
}

template <class Form_T, class Ele_T>
Ele_T& nl::Matrix<Form_T, Ele_T>::operator()(const size_t i, const size_t j) const
{
  if(i>rows_ || j>cols_)
    throw nl::FatalError("");

  return data_[i*cols_ + j];
}

template <class Form_T, class Ele_T>
Ele_T& nl::Matrix<Form_T, Ele_T>::operator[](const size_t i)
{
  if(i>(cols_*rows_-1))
    throw nl::FatalError("");

  return data_[i];
}

template <class Form_T, class Ele_T>
Ele_T& nl::Matrix<Form_T, Ele_T>::operator[](const size_t i) const
{
  if(i>(cols_*rows_-1))
    throw nl::FatalError("");

  return data_[i];
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>&
  nl::Matrix<Form_T, Ele_T>::operator +=
      (const nl::Matrix<Form_T, Ele_T>& mat)
{
  if(mat.cols_ == cols_ && mat.rows_ == rows_)
  {
    data_ += mat.data_;
  }
  else
  {
    throw nl::FatalError("nl::Matrix<Form_T, Ele_T>::operator +=: "\
        "Matrices must be of same size!\n");
  }

  return *this;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>&
  nl::Matrix<Form_T, Ele_T>::operator -=
      (const nl::Matrix<Form_T, Ele_T>& mat)
{
  if(mat.cols_ == cols_ && mat.rows_ == rows_)
  {
    data_ -= mat.data_;
  }
  else
  {
    throw nl::FatalError("nl::Matrix<Form_T, Ele_T>::operator +=: "\
        "Matrices must be of same size!\n");
  }

  return *this;
}

template <class Form_T, class Ele_T>
nl::Matrix<Form_T, Ele_T>&
  nl::Matrix<Form_T, Ele_T>::operator *=
      (const nl::Matrix<Form_T, Ele_T>& mat)
{
  nl::Matrix<Form_T, Ele_T> tmp_mat(rows_, mat.cols_);
  Ele_T element=0;
  if(mat.rows_ == cols_)
  {
    for(size_t i=0; i < mat.cols_; ++i)
    {
      for(size_t j=0; j < rows_; ++j)
      {
        for(size_t n=0; n<rows_; ++n)
        {
          element += data_[i*cols_ + n]*mat.data_[j + mat.rows_*n];
        }
        tmp_mat(i,j) = element;
        element = 0;
      }
    }
    *this = tmp_mat;
  }
  else
  {
    throw nl::FatalError("nl::Matrix<Form_T, Ele_T>::operator +=: "\
        "Matrices must be of same size!\n");
  }

  return *this;
}

