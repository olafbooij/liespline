/** written by olaf booij
 *  public domain */

#pragma once

#include<array>
#include<Eigen/Core>

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
  auto interpolate(const std::array<auto, 4>& T, const double delta_time)
  {
    auto weights = compute_weights(delta_time);
    auto T_delta = T[0];
    for(int j: {0, 1, 2}) // no one-based counting
    {
      const auto Omega = manifold::log(manifold::place(T[j], T[j + 1]));
      T_delta = manifold::prod(T_delta, manifold::exp(weights(j) * Omega));
    }
    return T_delta;
  }

}
