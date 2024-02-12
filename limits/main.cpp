#include <cmath>
#include <format>
#include <iostream>
#include <limits>

int main() {
  using namespace std;
  cout << format("max double = {}", numeric_limits<double>::max()) << endl;
  cout << format("min double = {}", numeric_limits<double>::min()) << endl;
  cout << format("low double = {}", numeric_limits<double>::lowest()) << endl;

  double num = nan("abc");
  bool a{}, b{};
  (isnan(num) ? a : b) = true;
  cout << format("num = {}, a = {}, b = {}", num, a, b) << endl;
}
