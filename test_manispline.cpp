/** written by olaf booij
 *  public domain */

#include<iostream>
#include<array>
#include<Eigen/Core>
#undef NDEBUG
#include<cassert>
#define NDEBUG

#include"manispline.hpp"

struct eu
{
  static auto log(const auto& a){ return a; }
  static auto exp(const auto& a){ return a; }
  static auto place(const auto& a, const auto& b){ return b - a; }
  static auto prod(const auto& a){ return a; }
  static auto prod(const auto& a, const auto& b, const auto&... t){ return a + prod(b, t...); }
};

int main()
{
  using namespace manispline;
  auto close = [](auto a, auto b){return fabs(a - b) < 1e-7;};
  {
    assert(close(eu::log(1.2), 1.2));
    assert(close(eu::exp(1.2), 1.2));
    assert(close(eu::prod(1.2, 1.3), 2.5));
    assert(close(eu::prod(1.2, 1.3, 0.3), 2.8));
  }
  {
    std::array T{1., 1., 1., 1.};
    assert(close(interpolate<eu>(T, 1.2), 1.));
  }
  {
    std::array T{0., 1., 2., 3.};
    assert(close(interpolate<eu>(T, .3), 1.3));
  }
  {
    std::array T{0., 0., 0., 10.};
    assert(interpolate<eu>(T, .1) > 0.);
  }
  {
    std::array T{10., 0., 0., 0.};
    assert(interpolate<eu>(T, .1) > 0.);
    assert(interpolate<eu>(T, .6) > 0.);
  }

  {
    std::array<Eigen::Vector2d, 4> T{{{1., 1}, {1., -1.}, {-1., -1.}, {-1., 1.}}};
    for(double u = 0; u < 1; u += .1)
    {
      const auto T_u = interpolate<eu>(T, u);
      assert(T_u(0) <  1.);
      assert(T_u(0) > -1.);
      assert(T_u(1) < 0);
      assert(T_u(1) > -1.);
    }
  }

  return 0;
}

