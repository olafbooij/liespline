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
    const auto u0 = 0;
    const auto u2 = u1 * u1;
    const auto u3 = u2 * u1;
    return 6 * u0 * v[0] + 0 * u1 * v[0] + 0 * u2 * v[0] + 0 * u3 * v[0] + // TODO coefficients
           6 * u0 * v[1] + 0 * u1 * v[1] + 0 * u2 * v[1] + 0 * u3 * v[1] +
           6 * u0 * v[2] + 0 * u1 * v[2] + 0 * u2 * v[2] + 0 * u3 * v[2] +
           6 * u0 * v[3] + 0 * u1 * v[3] + 0 * u2 * v[3] + 0 * u3 * v[3];
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
  }
  {
    std::array a{1.0, 1.0, 1.0, 1.0};
    assert(interpolate(a, 1.2) == 1.0);
  }
  {
    std::array a{0.0, 1.0, 2.0, 3.0};
    assert(interpolate(a, 0.2) == 0.2);
  }

  return 0;
}

