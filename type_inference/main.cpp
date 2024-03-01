#include <format>
#include <iostream>

#include "typename.h"

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

template <typename T, size_t N> void stackArrayFunc(T (&arr)[N]) {
  std::cout << format("{} array[{}]", type_name<T>(), N) << std::endl;
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

  int arr[]{0, 1, 2, 3};
  stackArrayFunc(arr);

  // valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  // --verbose ./type_inference
  new int;
}
