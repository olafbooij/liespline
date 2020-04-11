/** written by olaf booij
 *  public domain */

#include<iostream>
#include<random>
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
  double interpolate(const std::array<auto, 4>& v, const double delta_time)
  {
    const auto v_cummel_1 = v[1] - v[0];
    const auto v_cummel_2 = v[2] - v[1];
    const auto v_cummel_3 = v[3] - v[2];
    auto weights = compute_weights(delta_time);
    return v[0] + weights(0) * v_cummel_1 + weights(1) * v_cummel_2 + weights(2) * v_cummel_3;
  }

};

struct eu
{
  static auto log(const auto& a){ return a; }
  static auto exp(const auto& a){ return a; }
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
    std::array v{1., 1., 1., 1.};
    assert(close(interpolate(v, 1.2), 1.));
  }
  {
    std::array v{0., 1., 2., 3.};
    assert(close(interpolate(v, .3), 1.3));
  }
  {
    std::array v{0., 0., 0., 10.};
    assert(interpolate(v, .1) > 0.);
  }
  {
    std::array v{10., 0., 0., 0.};
    assert(interpolate(v, .1) > 0.);
    assert(interpolate(v, .6) > 0.);
  }

  return 0;
}

