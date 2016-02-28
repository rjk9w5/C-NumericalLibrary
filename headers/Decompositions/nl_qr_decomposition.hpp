/*
 * qr_decomp.hpp
 *
 *  Created on: Feb 24, 2016
 *      Author: Ryan Krattiger (rjk9w5)
 *       Brief: 
 */

template <class T>
oonm::Vector<oonm::Vector<T>>* nl::qr_decomp<T>::operator() (const oonm::Vector<oonm::Vector<T>>& A)
{
  size_t n,m;
  Norm2<oonm::Vector<T>> l2_norm;
  oonm::Vector<oonm::Vector<T>>* QR = new oonm::Vector<oonm::Vector<T>>[2];

  n = A.get_size(); // Number of vectors in set
  if(n > 0)
  {
    m = A[0].get_size(); // number of elements in each vector

    for(auto& Ak: A)
    {
      // Check to make sure each vector in the set is of the same size
      if(Ak.get_size() != m)
        throw nl::FatalError("qr_decomp: Vectors not of same size!");
    }

    // Reset memory for Q and R vector sets
    QR[1].reuse(n);
    for(int i=0; i<n; ++i)
      QR[1][i].reuse(n);

    // Initialize Q as a copy of A
    QR[0] = A;

    for(size_t k=0; k<n; ++k)
    {
      // Normalize Current vector
      QR[1][k][k] = l2_norm(QR[0][k]);
      QR[0][k] = QR[0][k]/(QR[1][k][k]);

      // Update the rest of the vector set with normalized vector
      for(size_t j=k+1; j<n; ++j)
      {
        QR[1][k][j] = (QR[0][k]*A[j]);// / (QR[0][j]*QR[0][j]);
        QR[0][j] -= (QR[1][k][j] * QR[0][k]);
      }
    }
  }

  return QR;
}

