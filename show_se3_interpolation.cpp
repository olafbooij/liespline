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
    static auto place(const auto& a, const auto& b){ return (a.inverse() * b).eval(); }
    static auto prod(const auto& a){ return a; }
    static auto prod(const auto& a, const auto& b, const auto&... t){ return (a * prod(b, t...)).eval(); }
  };

}

int main()
{
  using namespace liespline;
  using se3vec = Eigen::Matrix<double, 6, 1>;
  se3vec T0vec; T0vec << .1, .3, .5, 0., 0., 0.;
  auto T0 = expse3(T0vec);
	plot_se3(T0, std::cout);

  return 0;
}

