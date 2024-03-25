#include <algorithm>
#include <forward_list>
#include <iostream>
#include <map>
#include <set>
#include <type_traits>

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

template <typename T> void ovSet3(T, T *) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// simple SFINAE
template <typename T> void print(const T &t, typename T::iterator itr = {}) {
  using namespace std;
  for (auto itr{begin(t)}; itr != end(t); ++itr) {
    cout << *itr << endl;
  }
}

// advanced SFINAE
template <typename T, bool HaveFind, bool HaveLimits> struct SpecializedFind;

template <typename T>
auto haveFind(const T &) -> decltype(T{}.find({}), std::true_type{}) {}
template <typename... Args> auto haveFind(Args...) -> std::false_type {}

template <typename T>
auto haveLimits(const T &)
    -> decltype(T{}.cbegin(), T{}.cend(), std::true_type{}) {}
template <typename... Args> auto haveLimits(Args...) -> std::false_type {}

template <typename T> struct SpecializedFind<T, true, false> {
  static const auto find(const T &t, const typename T::key_type &k) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return t.find(k);
  }
};
template <typename T> struct SpecializedFind<T, false, true> {
  static const auto find(const T &t, const typename T::value_type &v) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::find(t.cbegin(), t.cend(), v);
  }
};
template <typename T>
struct SpecializedFind<T, true, true> : public SpecializedFind<T, true, false> {
};
template <typename T> struct SpecializedFind<T, false, false> {
  template <typename V> static const auto find(const T &t, const V &v) {
    static_assert(sizeof(T) < 0, "Operation not supported");
  }
};

template <typename T, typename V>
const auto no_if_find(const T &t, const V &v) {
  return SpecializedFind<T, decltype(haveFind(t))::value,
                         decltype(haveLimits(t))::value>::find(t, v);
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
}
