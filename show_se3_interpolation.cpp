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

  srand((unsigned int) time(0));

  if(0)
  {
  // wobbly path
  std::vector<Isometryd3> T(6);
  auto cur = Isometryd3::Identity();
  for(auto& T_i: T)
    T_i = cur = cur * Eigen::Translation3d(Eigen::Vector3d::UnitY()) * expse3(.3 * Eigen::Matrix<double, 6, 1>::Random());
  }

  if(0)
  {
  // spiral
  std::vector<Isometryd3> T(32);
  auto cur = Isometryd3::Identity();
  auto step = expse3(Eigen::Matrix<double, 6, 1>::Random());
  for(auto& T_i: T)
    T_i = cur = cur * step;
  }

  // downward curve
  auto make_SE3 = [](Eigen::Vector3d t, Eigen::Vector3d r){return Isometryd3(Eigen::Translation3d(t) * Eigen::AngleAxisd(r.norm(), r.normalized()));};
  std::vector<Isometryd3> T;
  for(int i=4; --i;)
    T.emplace_back(make_SE3({0., double(i), 0.}, {0., 0., 0.}));
  for(int i=4; --i;)
    T.emplace_back(make_SE3({4-double(i), 0., 1.}, {0., 0., M_PI/2}));

  for(int i=T.size()-1; --i;)
    plot_se3(T[i], std::cout, .2);
  for(int t = 0; t < T.size() - 3; ++t)
    for(double u = 0; u < 1; u += .2)
      plot_se3(interpolate<se3>(T.begin() + t, u), std::cout, .1);


  return 0;
}

