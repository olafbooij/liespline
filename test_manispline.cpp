/** written by olaf booij
 *  public domain */

#include<iostream>
#include<array>
#include<Eigen/Core>
#undef NDEBUG
#include<cassert>
#define NDEBUG

namespace manispline {
  static Eigen::Matrix<double, 3, 4> cumulative_cubic_B_spline_coefficients()
  {
    Eigen::Matrix<double, 3, 4> B;
    B <<  5,  3, -3,  1,
          1,  3,  3, -2,
          0,  0,  0,  1;
    B /= 6;
    return B;
  }
  Eigen::Vector3d compute_weights(const double delta_time)
  {
    Eigen::Vector4d time_power{1, delta_time, delta_time*delta_time, delta_time*delta_time*delta_time};
    return cumulative_cubic_B_spline_coefficients() * time_power;
  }
  template<typename manifold>
  double interpolate(const std::array<auto, 4>& T, const double delta_time)
  {
    auto weights = compute_weights(delta_time);
    auto T_delta = T[0];
    for(int j = 0; j < 3; ++j) // no one-based counting
    {
      const auto Omega = manifold::log(manifold::place(T[j], T[j + 1]));
      T_delta = manifold::prod(T_delta, manifold::exp(weights(j) * Omega));
    }
    return T_delta;
  }

};

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

  return 0;
}

