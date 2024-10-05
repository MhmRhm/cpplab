#include <algorithm>
#include <any>
#include <format>
#include <iostream>
#include <optional>
#include <random>
#include <utility>
#include <variant>

// This is not CRTP
template <typename... Ts> struct Visitor final : Ts... {
  using Ts::operator()...;
};
// Cpp 20 don't need explicit deduction guide
// template <typename... Ts> Visitor(Ts...) -> Visitor<Ts...>;

int main() {
  using namespace std;
  {
    // Cpp 17
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
  {
    // Cpp 17
    any var{1};

    cout << var.type().name() << endl;

    var = "char*"s;
    try {
      cout << format("any_cast<string>(var) = {}", any_cast<string>(var))
           << endl;
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }

    var = 1.f;
    if (var.has_value()) {
      cout << format("var = {}", any_cast<float>(var)) << endl;
    }

    var.emplace<pair<int, char>, int, char>(1, 'c');
    auto value{any_cast<pair<int, char>>(var)};
    cout << format("var = {{{}, {}}}", value.first, value.second) << endl;
  }
  {
    tuple var{1, 'c', "text"s};
    cout << format("var = {{{}, {}, {}}} of {} elements", get<int>(var),
                   get<1>(var), get<tuple_element<2, decltype(var)>::type>(var),
                   tuple_size<decltype(var)>::value)
         << endl;

    auto &[i, c, s]{var};
    i *= 2, c = 'd', reverse(s.begin(), s.end());
    cout << format("var = {{{}, {}, {}}}", get<0>(var), get<1>(var),
                   get<2>(var))
         << endl;

    int var1{};
    char var2{};
    string var3{};
    tie(var1, ignore, var3) = var;
    cout << format("var1 = {}, var2 = {}, var3 = {}", var1, var2, var3) << endl;

    tuple refvar{ref(var1), ref(var2), ref(var3)};
    auto [v1, v2, v3]{refvar};
    v1.get() *= 3, v2.get() = 'e',
                   shuffle(v3.get().begin(), v3.get().end(), random_device{});
    cout << format("var1 = {}, var2 = {}, var3 = {}", var1, var2, var3) << endl;

    struct Person {
      string firstName{};
      string lastName{};
      auto operator<=>(const Person &other) const {
        return tie(firstName, lastName) <=>
               tie(other.firstName, other.lastName);
      }
    };
    auto res{Person{"John", "King"} <=> Person{"John", "King"}};
    cout << is_lt(res) << endl;
  }
}
