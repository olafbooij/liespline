/** written by olaf booij
 *  public domain */

#include<iostream>
#include<random>
#include<array>
#undef NDEBUG
#include<cassert>
#define NDEBUG

namespace manispline {
  template<typename V> // array of 4 thingies
  auto interpolate(const V& v, double u)
  {
    // TODO
    return v.at(0);
  }

};

struct eu
{
  template<typename A>
  static auto log(const A& a){ return a; }
  template<typename A>
  static auto exp(const A& a){ return a; }
  template<typename A, typename B>
  static auto prod(const A& a, const B& b){ return a + b; }
};


int main()
{
  using namespace manispline;
  {
    std::array a{1.0, 2.0, 4.0, 5.0};
    std::cout << interpolate(a, 1.2) << std::endl;
  }

  return 0;
}

