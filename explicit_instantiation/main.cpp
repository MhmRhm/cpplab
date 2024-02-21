#include <deque>
#include <iostream>
#include <string>
#include <vector>

template <typename T> constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

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
}
// explicit template instantiations
template class Wrapper<int, std::deque>;
// template class Wrapper<int, std::vector>;
