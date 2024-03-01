#include <cmath>
#include <concepts>
#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../type_inference/typename.h"

// template <typename ContainerType>
// concept BackPushable =
//     requires(ContainerType ct, typename ContainerType::value_type vt) {
//       ct.push_back(vt);
//     };
// template <typename ContainerType>
// concept FrontPushable =
//     requires(ContainerType ct, typename ContainerType::value_type vt) {
//       ct.push_front(vt);
//     };
// template <typename ContainerType>
// concept DoubleEnded =
//     BackPushable<ContainerType> && FrontPushable<ContainerType>;

// requires(sizeof(int) == 4)

// requires DoubleEnded<Container<Element>>

//  requires requires(Container<Element> ct, Element et) {
//    ct.push_back(et);
//    ct.push_front(et);
//  }

template <typename Element,
          template <typename T, typename Allocator = std::allocator<T>>
          class Container = std::deque>
class Wrapper final {
public:
  void include(Element &&t) { container.push_back(std::forward<Element>(t)); }
  void includeFront(const Element &t) { container.push_front(t); }

private:
  Container<Element> container{};
};

template <typename T> struct Decorator final {
  Decorator(T t) {}
};
// user defined class template argument deduction
// Decorator(const char *) -> Decorator<std::string>;

template <typename T> struct Countable;
template <typename T>
Countable<T> operator+(const Countable<T> &lhs, const Countable<T> &rhs) {
  return Countable{lhs.t + rhs.t};
}
template <typename T> struct Countable final {
  T t{};
  friend Countable operator+(const Countable &lhs, const Countable &rhs);
};

template <std::floating_point T> bool isEqual(const T &lhs, const T &rhs) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return std::fabs(lhs - rhs) < std::numeric_limits<T>::min();
}
template <std::integral T> bool isEqual(const T &lhs, const T &rhs) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return lhs == rhs;
}

int main() {
  using namespace std;
  Wrapper<int, vector> wrapper;

  // selective instantiation
  wrapper.include(10);

  // CTAD
  Decorator decorator{"Hello"};
  cout << type_name<decltype(decorator)>() << endl;

  Countable c1{1}, c2{2};
  // cout << (c1 + c2).t << endl;

  isEqual(3.14, 3.14);
  isEqual(3, 3);
}
// explicit template instantiations
template class Wrapper<int, std::deque>;
// template class Wrapper<int, std::vector>;
