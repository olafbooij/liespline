/** written by olaf booij
 *  public domain */

#include<iostream>

#include"se3.hpp"
#include"liespline.hpp"

#undef NDEBUG
#include<cassert>
#define NDEBUG

namespace liespline {

  struct se3
  {
    static auto log(const auto& a){ return logse3(a); }
    static auto exp(const auto& a){ return expse3(a); }
    static auto place(const auto& a, const auto& b){ return (a.inverse() * b); }
    static auto prod(const auto& a){ return a; }
    static auto prod(const auto& a, const auto& b, const auto&... t){ return (a * prod(b, t...)); }
  };

}

int main()
{
  using namespace liespline;

  {
    Isometryd3 A(Eigen::Translation3d(Eigen::Vector3d{.1, .2, .3}) * Eigen::AngleAxisd(.2, Eigen::Vector3d{.2, .3, .5}.normalized()));

    assert(((A * A).matrix() - expse3(2 * logse3(A)).matrix()).norm() < 1e-7);
    assert(((A * expse3(-logse3(A))).matrix() - Eigen::Matrix4d::Identity()).norm() < 1e-7);
  }

  {
    std::vector<Isometryd3> T(6);
    for(auto& T_i: T)
      T_i = expse3(Eigen::Matrix<double, 6, 1>::Random());

    assert((logse3(interpolate<se3>(T.begin() + 0, 1)) -
            logse3(interpolate<se3>(T.begin() + 1, 0))).norm() < 1e-7);
    assert((logse3(interpolate<se3>(T.begin() + 1, 1)) -
            logse3(interpolate<se3>(T.begin() + 2, 0))).norm() < 1e-7);
  }

  return 0;
}

