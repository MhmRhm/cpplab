#include <iostream>

// Cpp 11
namespace old1 {
namespace old2 {
void print() {
  using namespace std;
  cout << "Hello Cpp 11 World! " << 013 << endl;
}
} // namespace old2
} // namespace old1

// Cpp 17
namespace new1::new2 {
void print() {
  using namespace std;
  cout << "Hello Cpp 17 World! " << 0b0001'0001 << endl;
}
} // namespace new1::new2

enum class Seasons : int {
  Spring = 0,
  Summer,
  Fall,
  Winter,
};

int main() {
  {
    using old1::old2::print;
    print();
  }
  {
    using new1::new2::print;
    print();
  }

  // Cpp 20
  auto var{Seasons::Summer};
  switch (var) {
    using enum Seasons;
  [[likely]] case Spring:
    break;
  case Summer:
    break;
  [[unlikely]] case Fall:
    break;
  default:
    break;
  }

  return 0;
}
