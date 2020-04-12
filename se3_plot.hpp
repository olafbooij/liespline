#pragma once

#include"se3.hpp"

namespace liespline {

  template<typename Out_stream>
  void plot_se3(const Isometryd3& transform, Out_stream&& out_stream, const double size = 1.)
  {
    auto origin = transform * Eigen::Vector3d::Zero();
    auto unit_x = transform * (Eigen::Vector3d::UnitX() * size);
    auto unit_y = transform * (Eigen::Vector3d::UnitY() * size);
    auto unit_z = transform * (Eigen::Vector3d::UnitZ() * size);
    out_stream << origin.transpose()  << " 0xFF0000" << std::endl
               << unit_x.transpose() << " 0xFF0000" << std::endl
               << std::endl
               << std::endl;
    out_stream << origin.transpose()  << " 0x00FF00" << std::endl
               << unit_y.transpose()   << " 0x00FF00" << std::endl
               << std::endl
               << std::endl;
    out_stream << origin.transpose()  << " 0x0000FF" << std::endl
               << unit_z.transpose()       << " 0x0000FF" << std::endl
               << std::endl
               << std::endl;
  }

  /*
  set view equal xyz
  set view ,,1.0
  set xlabel "x"
  set ylabel "y"
  set zlabel "z"
  splot "<./a.out" with lines lc rgb variable
  */


}

