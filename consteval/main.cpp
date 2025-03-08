#include <iostream>

constexpr double symbolsTimeNs(double symbols) { return symbols * 0.8; }

int main() {
  using namespace std;

  double symbols1{4};
  cout << symbolsTimeNs(symbols1) << endl;

  const double symbols2{4};
  cout << symbolsTimeNs(symbols2) << endl;

  constexpr double symbols3{4};
  cout << symbolsTimeNs(symbols3) << endl;

  // 'consteval' is not permitted on the declaration of a variable or static
  // data member
  // consteval double symbols4{4};
}
