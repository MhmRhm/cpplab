#include <compare>
#include <cstdint>
#include <iostream>
#include <string>

struct History {
  uint8_t mem1{};
  std::string mem2{};
  bool mem3{};
  double mem4{};

  // Cpp 20
  // return type can be strong_ordering, partial_ordering or weak_ordering.
  [[nodiscard("must use")]] auto
  operator<=>(const History &other) const = default;

  void method1() & {}
  void method2() && {}
};

[[deprecated("use func(int &a, int b) instead")]] void func() {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
};

// Cpp 20
void func(int &a, /*[[maybe_unused]]*/ int b) { a = 0; }

int main() {
  using namespace std;

  History h1{}, h2{};
  auto result{h1 <=> h2};

  if (is_eq(result)) {
    cout << "is equal" << endl;
  } else if (is_lt(result)) {
    cout << "is less than" << endl;
  }

  h1 <=> h2;
  if (h1 == h2)
    ;
  if (h1 != h2)
    ;
  if (h1 < h2)
    ;
  if (h1 > h2)
    ;
  if (h1 <= h2)
    ;
  if (h1 >= h2)
    ;

  h1.method1();
  History{}.method2();

  func();
}
