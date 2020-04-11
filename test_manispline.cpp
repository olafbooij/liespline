/** written by olaf booij
 *  public domain */

#include<iostream>
#include<random>
#include<array>
#undef NDEBUG
#include<cassert>
#define NDEBUG

namespace manispline {
  auto interpolate(const std::array<auto, 4>& v, const double u1)
  {
    const auto v_cummel_0 = 0.;
    const auto v_cummel_1 = v[1] - v[0];
    const auto v_cummel_2 = v[2] - v[1];
    const auto v_cummel_3 = v[3] - v[2];
    const auto u0 = 1;
    const auto u2 = u1 * u1;
    const auto u3 = u2 * u1;
    return v[0] + (6 * u0 + 0 * u1 + 0 * u2 + 0 * u3) / 6. * v_cummel_0 +
                  (5 * u0 + 3 * u1 - 3 * u2 + 1 * u3) / 6. * v_cummel_1 +
                  (1 * u0 + 3 * u1 + 3 * u2 - 2 * u3) / 6. * v_cummel_2 +
                  (0 * u0 + 0 * u1 + 0 * u2 + 1 * u3) / 6. * v_cummel_3;
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
  {
    assert(eu::log(1.2) == 1.2);
    assert(eu::exp(1.2) == 1.2);
    assert(eu::prod(1.2, 1.3) == 2.5);
    assert(eu::prod(1.2, 1.3, 0.3) == 2.8);
  }
  {
    std::array v{1., 1., 1., 1.};
    assert(interpolate(v, 1.2) == 1.);
  }
  {
    std::array v{0., 1., 2., 3.};
    assert(interpolate(v, .3) == 1.3);
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

