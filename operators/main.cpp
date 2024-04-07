#include <format>
#include <iostream>
#include <memory>
#include <source_location>
#include <string>

struct Type final {
  int value{};
  int method() { return 100; }

  Type &operator++() {
    std::cout << std::source_location::current().function_name() << std::endl;
    value += 1;
    return *this;
  }
  Type operator--(int) {
    std::cout << std::source_location::current().function_name() << std::endl;
    auto temp{*this};
    value -= 1;
    return temp;
  }

  // Insertion/Extraction operator
  friend std::ostream &operator<<(std::ostream &os, const Type &t) {
    std::cout << std::source_location::current().function_name() << std::endl;
    os << t.value;
    return os;
  }

  int &operator*() {
    std::cout << std::source_location::current().function_name() << std::endl;
    return value;
  }
  const int &operator*() const {
    std::cout << std::source_location::current().function_name() << std::endl;
    return value;
  }

  Type *operator->() {
    std::cout << std::source_location::current().function_name() << std::endl;
    return this;
  }

  explicit operator std::string() const {
    std::cout << std::source_location::current().function_name() << std::endl;
    return std::format(R"("{}")", value);
  }
  operator bool() = delete;

  auto operator->*(int (Type::*)()) const {
    std::cout << std::source_location::current().function_name() << std::endl;
    return [] { return 1'000; };
  }

  int operator()(int multiply, int add) const {
    std::cout << std::source_location::current().function_name() << std::endl;
    return multiply * value + add;
  }

  void *operator new(size_t size, void *placement) {
    std::cout << std::source_location::current().function_name() << std::endl;
    return ::operator new(size, placement); // placement new operator
  }
};

// Raw mode
Type operator""_t(const char *lit) {
  using namespace std;
  std::cout << std::source_location::current().function_name() << std::endl;
  return Type{stoi(lit)};
}
// Cooked mode
Type operator""_t(unsigned long long val) {
  std::cout << std::source_location::current().function_name() << std::endl;
  return Type{int(val)};
}
// Cooked mode string
Type operator""_t(const char *str, size_t len) {
  using namespace std;
  std::cout << std::source_location::current().function_name() << std::endl;
  return Type{stoi(str)};
}

int main() {
  using namespace std;

  Type t{0};
  cout << t << endl;                     // 0
  cout << ++t << endl;                   // 1
  cout << t-- << endl;                   // 1
  cout << *t + 10 << endl;               // 10
  cout << t->value << endl;              // 0
  cout << t.operator->()->value << endl; // 0
  cout << string(t) << endl;             // "0"

  auto memptr{&Type::method};
  cout << (t.*memptr)() << endl;   // 100
  cout << (&t->*memptr)() << endl; // 100
  cout << (t->*memptr)() << endl;  // 1'000

  cout << t(1, 3) << endl; // 3

  byte mem[sizeof(Type)]{};
  Type *tp{new (&mem) Type{int(0xff'ff'ff'ff)}};
  cout << *tp << endl; // -1
  tp->~Type();
  // valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  // --verbose ./operators

  cout << 1234_t << endl;   // 1234 raw or cooked(int)
  cout << "1234"_t << endl; // 1234 cooked(str)
}
