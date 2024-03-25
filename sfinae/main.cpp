#include <algorithm>
#include <forward_list>
#include <iostream>
#include <map>
#include <set>

#include "sfinae.h"

void ovSet1(int, double) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void ovSet1(double, int) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template <typename T> void ovSet2(T *) /*= delete*/ {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}
template <typename T> void ovSet2(T) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}
template <typename... Args> void ovSet2(Args...) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void ovSet2(...) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template <typename T> void ovSet3(T, T *) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() {
  using namespace std;

  ovSet1(1, 1.0);
  ovSet1(1.0, 1);
  // ovSet1(1, 1);

  int var1{};
  ovSet2(&var1);

  short var2{};
  // ovSet3(var2, &var1);

  forward_list list1{1, 2, 3};
  print(list1);
  // print(var1);

  {
    set container{1, 2, 3};
    auto itr{no_if_find(container, 2)};
    cout << *itr << endl;
  }
  {
    multimap container{pair{1, '1'}, {2, '2'}, {1, '1'}, {2, '2'}};
    auto itr{no_if_find(container, 2)};
    cout << itr->first << endl;
  }
  {
    auto container{1};
    // auto itr{no_if_find(container, 2)};
  }
  {
    set vartiable{1, 2, 3};

    auto isDereferenceable{isValidExp([](auto &&type) -> decltype(*type) {})};
    auto canCallFind{isValidExp([](auto &&type) -> decltype(type.find({})) {})};

    static_assert(decltype(canCallFind(vartiable))::value,
                  "Container does not support find");
    static_assert(decltype(isDereferenceable(vartiable.cbegin()))::value,
                  "Variable is not dereferenceable");
    if (!decltype(isDereferenceable(vartiable))::value) {
      cout << "Variable is not dereferenceable" << endl;
    }
  }
}
