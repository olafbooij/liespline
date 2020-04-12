/** written by olaf booij
 *  public domain */

#include<iostream>
#undef NDEBUG
#include<cassert>
#define NDEBUG

#include<se3.hpp>

int main()
{
  using namespace liespline;

  Isometryd3 A(Eigen::Translation3d(Eigen::Vector3d{.1, .2, .3}) * Eigen::AngleAxisd(.2, Eigen::Vector3d{.2, .3, .5}.normalized()));

  assert(((A * A).matrix() - explie(2 * loglie(A)).matrix()).norm() < 1e-7);
  assert((A * explie(-loglie(A))).matrix().norm() < 1e-7);

  return 0;
}

