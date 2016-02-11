/*
 * nl_vector.hpp
 *
 *  Created on: Feb 10, 2016
 *      Author: ryan
 */

#ifndef HEADERS_NL_VECTOR_HPP_
#define HEADERS_NL_VECTOR_HPP_

#include <utility>
#include <memory>

namespace nl
{
  template <class T>
  class vector;

  template <class T>
  class vector
  {
  public:
    vector();
    vector(const size_t size);
    vector<T>& operator=(const vector<T>& src);
    vector(const vector<T>& src);
    vector<T>& operator=(vector<T>&& other);
    vector(vector<T>&& other);

    const T& operator[](const size_t i) const;
    T& operator[](const size_t i);

    const size_t get_size() const;
    vector<T>& subset(const size_t start,
                      const size_t stop,
                      const size_t step=1);


  private:
    std::unique_ptr<T[]> m_vec;
    size_t m_size;
    bool m_orientation; // true -> vertical
  };

#include "nl_vector.tpp"
}

#endif /* HEADERS_NL_VECTOR_HPP_ */
