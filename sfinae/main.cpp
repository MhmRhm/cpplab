#include <format>
#include <iostream>

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

int main() {
  using namespace std;

  ovSet1(1, 1.0);
  ovSet1(1.0, 1);
  // ovSet1(1, 1);

  int var1{};
  ovSet2(&var1);

  short var2{};
  // ovSet3(var2, &var1);
}
