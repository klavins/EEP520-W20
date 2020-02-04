#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cctype>

namespace {

  class Arith {

      public: 

      Arith() : _value(0) {}

      Arith &zero()          { _value  = 0; return *this; }
      Arith &add(int x)      { _value += x; return *this; }
      Arith &subtract(int x) { _value -= x; return *this; }
      Arith &multiply(int x) { _value *= x; return *this; }
      Arith &divide(int x)   { _value /= x; return *this; }

      int value() { return _value; }

      private:

      int _value;

  };

  TEST(Arith,Chaining) {
    Arith a;
    ASSERT_EQ(a.add(1).zero().subtract(2).divide(2).add(2).value(), 1);
  }

  std::vector<int> map(std::vector<int> v, std::function< int(int) > f) {
     std::vector<int> result;
     for ( auto x : v ) {
         result.push_back(f(x));
     }
     return result;
  }

  TEST(Lambda, Argument) {
    std::vector<int> v = { 1,2,3,4,5 };
    auto f = [](int x) { return x*x; };
    std::vector<int> u = map(v, f);
    for ( auto x : u ) {
      std::cout << x << " ";
    }
    std::cout << "\n";
  }

}