
#include <iostream>
#include "./src/containers/Matrices/RectangularMatrix/nl_rect_matrix.h"

int main(int argc, char* args[])
{
  // Default, single input, to input, two input same size, three input
  nl::MatrixRect<double> m1, m2(3), m3(3,4), m4(2,2), m5(3,5,1);
  // Copy constructor
  nl::MatrixRect<double> m6(m5);
  // Move constructor
  nl::MatrixRect<double> m7(m5 + m6);

  std::cout << "Success" << std::endl;

  return 0;
}
