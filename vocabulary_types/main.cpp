#include <any>
#include <format>
#include <iostream>
#include <optional>
#include <utility>
#include <variant>

template <typename... Ts> struct Visitor final : Ts... {
  using Ts::operator()...;
};
// Cpp 20 don't need explicit deduction guide
// template <typename... Ts> Visitor(Ts...) -> Visitor<Ts...>;

int main() {
  using namespace std;

  variant<int, string> var1;
  cout << format("get<int>(var1) = {}", get<int>(var1)) << endl;

  variant<monostate, int, string> var2{};
  // var2 = 10;
  try {
    cout << format("get<int>(var2) = {}", get<int>(var2)) << endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // var2 = "text";
  if (holds_alternative<string>(var2)) {
    cout << format("holds_alternative<string>(var2) = {}", get<string>(var2))
         << endl;
  }

  if (auto *ptr{get_if<int>(&var2)}; ptr) {
    cout << format("get_if<int>(&var2) = {}", *ptr) << endl;
  }

  Visitor visitor{
      [](auto) { std::cout << "monostate" << endl; },
      [](int &var) { cout << format("int var = {}", var) << endl; },
      [](string &var) { cout << format("string var = {}", var) << endl; },
  };
  visit(std::move(visitor), var2);
}
