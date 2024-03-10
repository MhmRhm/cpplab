#include <chrono>
#include <cmath>
#include <concepts>
#include <format>
#include <functional>
#include <iostream>
#include <numeric>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "../vocal/inner_outer.h"

namespace {
int num0{10};
}

int *f1(int *) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return nullptr;
};

struct C1 final {
  int const *const m1(int const *const) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return nullptr;
  }
  void m2() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main() {
  using namespace std;

  using F1Type = int *(*)(int *);
  F1Type f1p{&f1};
  f1p(nullptr);

  using M1Type = int const *const (C1::*)(int const *const) const;
  M1Type m1p{&C1::m1};
  (C1{}.*m1p)(nullptr);

  using ConstM1Type = int const *const (C1::*const)(int const *const) const;
  ConstM1Type cm1p{&C1::m1};
  // cm1p = &C1::m1;

  function<int const *const(const C1 &, int const *const)> m1fp = &C1::m1;
  // function<void(const C1 &)> m2fp = &C1::m2;
  m1fp(C1{}, nullptr);

  invoke(&f1, nullptr);
  invoke(&C1::m2, C1{});
  invoke(m1fp, C1{}, nullptr);

  struct Comparator {
    bool operator()(int lhs, int rhs) { return lhs < rhs; }
    bool operator()(float lhs, float rhs) { return lhs < rhs; }
  };
  bool (Comparator::*compare)(int, int){&Comparator::operator()};
  // auto opptr{&Comparator::operator()};
  auto opptr{
      static_cast<bool (Comparator::*)(int, int)>(&Comparator::operator())};

  cout << negate<>{}(100) << endl;
  cout << logical_not<>{}(100) << endl;
  cout << bit_not<>{}(0b0011) << endl;

  // https://en.cppreference.com/w/cpp/utility/functional#Transparent_function_objects
  static_assert(requires(modulus<>::is_transparent T) { true; });

  // inaccurate result
  vector nums{1, 1, 1};
  auto arithmeticAverage{
      accumulate(cbegin(nums), cend(nums), 0.99, plus<int>{}) / nums.size()};
  auto geometricAverage{
      pow(accumulate(cbegin(nums), cend(nums), 0.99, multiplies<int>{}),
          1.0 / nums.size())};
  cout << format("arithmetic average = {}, geometric average = {}",
                 arithmeticAverage, geometricAverage)
       << endl;

  // unnecessary copying
  // Cpp 20 heterogeneous lookups
  struct HetroHash final {
    using is_transparent = void;
    size_t operator()(string_view sv) const { return hash<string_view>{}(sv); }
  };
  unordered_map<string, chrono::years, HetroHash, equal_to<>> ages{
      pair{"Alisyn Camerota", chrono::years{57}}};
  auto it{ages.find("John King")};

  auto isOld{bind(greater<>{}, placeholders::_1, chrono::years{57})};
  cout << isOld(chrono::years{90}) << endl;

  auto f{mem_fn(&vector<int>::size)};
  for (vector<int> &v : vector<vector<int>>{{1, 2, 3}, {1, 2}, {1}}) {
    cout << f(v) << endl;
  }

  int num1{100}, num2{1'000};
  auto l1{[num1] mutable noexcept -> void { num1 *= 2; }};
  l1();
  cout << num1 << endl;

  // Cpp 20
  // [=] does not capture `this`. Instead use [=, this].
  auto l2{[=, &num1] mutable {
    num1 *= 2;
    num2 *= 2;
  }};
  l2();
  cout << num1 << " " << num2 << endl;

  auto l3{[=] { num0 *= 2; }};
  l3();
  cout << num0 << endl;

  // lambda capture expressions
  Inner inner{};
  auto l4{[p = std::move(inner)] { cout << "inner.id = " << p.id << endl; }};
  l4();
  // decltype(l4) l41;
  decltype(l4) l41{l4};
  l41();

  auto l5{[](int a, int b) { return a < b; }};
  // Cpp 20 stateless lambda expressions default constructor and assignment
  // operator
  decltype(l5) l51;
  l51 = l5;

  // Cpp 20
  auto l6{[]<typename T>(const vector<T> &v)
            requires floating_point<T>
          {
            for (auto &&i : v) {
              cout << format("{:5.3f}", i) << endl;
            }
          }};
  vector<float> v1{.1, .2, .3};
  vector<double> v2{.1, .2, .3};
  vector<int> v3{1, 2, 3};
  l6(v1);
  l6(v2);
  // l6(v3);
}
