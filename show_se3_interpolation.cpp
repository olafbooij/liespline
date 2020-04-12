/** written by olaf booij
 *  public domain */

#include<iostream>

#include"se3.hpp"
#include"se3_plot.hpp"
#include"liespline.hpp"

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

  auto make_SE3 = [](Eigen::Vector3d t, Eigen::Vector3d r){return Isometryd3(Eigen::Translation3d(t) * Eigen::AngleAxisd(r.norm(), r.normalized()));};

  std::array T{make_SE3({0., 0., 0.}, {0., 0., 0.}),
               make_SE3({0., 3., 0.}, {0., 0., 0.}),
               make_SE3({1., 4., 0.}, {0., 0., -M_PI/2.}),
               make_SE3({4., 4., 0.}, {0., 0., -M_PI/2.})};

  for(auto T_i: T)
    plot_se3(T_i, std::cout);

  for(double u = 0; u < 1; u += .1)
    plot_se3(interpolate<se3>(T, u), std::cout, .5);

  {
    std::array T{make_SE3({0., 0., 0.}, {0., 0., 0.}),
                 make_SE3({0., 3., 0.}, {0., 0., 0.}),
                 make_SE3({1., 4., 3.}, {2., 8., -M_PI/2.}),
                 make_SE3({4., 4., 0.}, {0., 0., -M_PI/2.}),
                 make_SE3({5., 6., 0.}, {0., 0., -M_PI/2.})};
    std::cout << logse3(interpolate<se3>(T.begin() + 0, 1)).transpose() << std::endl;
    std::cout << logse3(interpolate<se3>(T.begin() + 1, 0)).transpose() << std::endl;
  }


  return 0;
}

