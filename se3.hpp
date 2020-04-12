/** written by olaf booij
 *  public domain */

#pragma once

#include<Eigen/Core>
#include<Eigen/Geometry>

namespace liespline {

  using Isometryd3 = Eigen::Transform<double, 3, Eigen::Isometry, Eigen::ColMajor>;

  auto crossMat(const Eigen::Vector3d& vec)
  {
    Eigen::Matrix3d mat; 
    mat <<       0, -vec(2),  vec(1),
            vec(2),       0, -vec(0),
           -vec(1),  vec(0),       0;
    return mat;
  }

  // F.C.Park "Distance Metrics on the Rigid-Body Motions with Applications to Mechanism Design"
  // with some rewrite
  auto explie(const Eigen::Matrix<double, 6, 1>& se3)
  {
    auto se3_trans = se3.head<3>();
    auto so3 = se3.tail<3>();
    auto angle = so3.norm();
    auto axis = so3.normalized();
    Eigen::Matrix3d A;
    if(fabs(angle) < std::numeric_limits< double >::epsilon())
      A = Eigen::Matrix3d::Identity() + .5 * angle * crossMat(axis);
    else
      A = (sin(angle) * Eigen::Matrix3d::Identity() + (1 - cos(angle)) * crossMat(axis) + (angle - sin(angle)) * axis * axis.transpose()) / angle;
    return Isometryd3(Eigen::Translation3d(A * se3_trans) * Eigen::AngleAxisd(angle, axis));
  }

  auto loglie(const Isometryd3& SE3)
  {
    auto SE3_trans = SE3.translation();
    auto so3_aa = Eigen::AngleAxisd(SE3.rotation());
    auto axis = so3_aa.axis();
    auto angle = so3_aa.angle();
    double b;
    if(fabs(angle) < std::numeric_limits< double >::epsilon())
      b = 1.;
    else
      b = angle / (2 * tan(angle / 2));
    Eigen::Matrix3d Ainv = b * Eigen::Matrix3d::Identity() + (1 - b) * axis * axis.transpose() - angle / 2 * crossMat(axis);
    Eigen::Matrix<double, 6, 1> se3;
    se3.head<3>() = Ainv * SE3_trans;
    se3.tail<3>() = angle * axis;
    return se3;
  }

}

