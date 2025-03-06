#pragma once

#include <source_location>
#include <type_traits>

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
  virtual ~SpecializedFind() = default;
  static const auto find(const T &t, const typename T::key_type &k) {
    std::cout << std::source_location::current().function_name() << std::endl;
    return t.find(k);
  }
};
template <typename T> struct SpecializedFind<T, false, true> {
  virtual ~SpecializedFind() = default;
  static const auto find(const T &t, const typename T::value_type &v) {
    std::cout << std::source_location::current().function_name() << std::endl;
    return std::find(t.cbegin(), t.cend(), v);
  }
};
template <typename T>
struct SpecializedFind<T, true, true> : public SpecializedFind<T, true, false> {
  virtual ~SpecializedFind() override = default;
};
template <typename T> struct SpecializedFind<T, false, false> {
  virtual ~SpecializedFind() = default;
  template <typename V> static const auto find(const T &t, const V &v) {
    static_assert(sizeof(T) < 0, "Operation not supported");
  }
};

template <typename T, typename V>
const auto no_if_find(const T &t, const V &v) {
  return SpecializedFind<T, decltype(haveFind(t))::value,
                         decltype(haveLimits(t))::value>::find(t, v);
}

// exotic SFINAE
template <typename LambdaExp> struct OverloadSet final {
  template <typename... LambdaArgs>
  constexpr auto overload(int)
      -> decltype(std::declval<LambdaExp>()(std::declval<LambdaArgs>()...),
                  std::true_type{}) {
    return std::true_type{};
  }
  template <typename... Args> constexpr auto overload(...) {
    return std::false_type{};
  }
  template <typename... LambdaArgs>
  constexpr auto operator()(const LambdaArgs &...args) {
    return this->overload<LambdaArgs...>(0);
  }
};

template <typename LambdaExp> constexpr auto isValidExp(const LambdaExp &) {
  return OverloadSet<LambdaExp>{};
}
