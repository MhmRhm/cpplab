#include <format>
#include <iostream>

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

// Cpp 14 Auto Return Type
auto factorial(int num) {
  if (num <= 1)
    // first return
    return 1;
  else
    return num * factorial(num - 1);
}

// Cpp 14
template <typename T> auto func1(const T &param1, const T &param2) {
  return param1 + param2;
}

// Cpp 11
template <typename T>
auto func2(const T &param1, const T &param2) -> decltype(param1 + param2) {
  return param1 + param2;
}

// Cpp 20
template <typename T> decltype(auto) func3(const T &param1, const T &param2) {
  return param1 + param2;
}

// Cpp 20 Abbreviated Function Template Syntax
decltype(auto) func4(const auto &param1, const auto &param2) {
  return param1 + param2;
}

int main() {
  using namespace std;

  cout << format("0! = {}, 1! = {}, 2! = {}, 3! = {}", factorial(0),
                 factorial(1), factorial(2), factorial(3))
       << endl;

  int var{};
  const int constVar{};
  const int &constRefVar{var};

  auto autoVar{var};
  auto autoConstVar{constVar};
  auto autoConstRefVar{constRefVar};

  auto autoPtrVar{&var};
  const auto constAutoPtrVar{&var};
  auto const autoConstPtrVar{&var};

  decltype(auto) decltypeAutoConstRefVar{constRefVar};

  decltype(auto) func4Ret{func4(1, 2.3)};

  cout << format("type_name(autoVar) = {}", type_name<decltype(autoVar)>())
       << endl;
  cout << format("type_name(autoConstVar) = {}",
                 type_name<decltype(autoConstVar)>())
       << endl;
  cout << format("type_name(autoConstRefVar) = {}",
                 type_name<decltype(autoConstRefVar)>())
       << endl;
  cout << format("type_name(autoPtrVar) = {}",
                 type_name<decltype(autoPtrVar)>())
       << endl;
  cout << format("type_name(constAutoPtrVar) = {}",
                 type_name<decltype(constAutoPtrVar)>())
       << endl;
  cout << format("type_name(constAutoPtrVar) = {}",
                 type_name<decltype(autoConstPtrVar)>())
       << endl;
  cout << format("type_name(decltypeAutoConstRefVar) = {}",
                 type_name<decltype(decltypeAutoConstRefVar)>())
       << endl;
  cout << format("type_name(func4Ret) = {}", type_name<decltype(func4Ret)>())
       << endl;
}
