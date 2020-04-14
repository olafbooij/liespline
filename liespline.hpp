/** written by olaf booij
 *  public domain */

#pragma once

#include<array>
#include<Eigen/Core>

// Elias Mueggler, Guillermo Gallego, Henri Rebecq, and Davide Scaramuzza
// "Continuous-Time Visual-Inertial Odometry for Event Cameras"
// only the se3 interpolation part


namespace liespline {

  Eigen::Matrix<double, 3, 4> cumulative_cubic_B_spline_coefficients()
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
  template<typename group, typename input_iterator_t>
  auto interpolate(input_iterator_t iter, const double delta_time)
  {
    auto weights = compute_weights(delta_time);
    auto T_delta = *iter;
    for(int j: {0, 1, 2})
    {
      const auto Omega = group::log(group::place(*(iter + j), *(iter + j + 1)));
      T_delta = group::prod(T_delta, group::exp(weights(j) * Omega));
    }
    return T_delta;
  }
  template<typename group>
  auto interpolate(const std::array<auto, 4>& T, const double delta_time)
  {
    return interpolate<group>(T.begin(), delta_time);
  }

}
