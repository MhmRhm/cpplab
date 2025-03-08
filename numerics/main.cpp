#include <bit>
#include <cmath>
#include <format>
#include <iostream>
#include <utility>

double normalDistributionProbability(double start, double end) {
  return (std::erf(end / std::sqrt(2)) - std::erf(start / std::sqrt(2))) / 2;
}

int main() {
  using namespace std;
  cout << format("-1 > 0UL = {}", -1 > 0UL) << endl;
  // Cpp 20
  cout << format("1 > 0UL = {}, -1 > 0UL = {}", cmp_greater(1, 0UL),
                 cmp_greater(-1, 0UL))
       << endl;

  // Cpp 20
  cout << format("bit_ceil(17U) = {}", bit_ceil(17U)) << endl;
  cout << format("bit_floor(31U) = {}", bit_floor(31U)) << endl;
  cout << format("rotl(0b0011'1100U, 2) = {:B}", rotl(0b0011'1100U, 2)) << endl;
  cout << format("popcount(0b0001'0000U) = {}", popcount(0b0001'0000U)) << endl;

  if constexpr (endian::native == endian::big) {
    cout << "big-endian" << endl;
  } else if constexpr (endian::native == endian::little) {
    cout << "little-endian" << endl;
  } else {
    cout << "mixed-endian" << endl;
  }

  cout << format("Probability of the outcome to be above 4\u03c3 = {:.5f}%",
                 100 - 100 * normalDistributionProbability(
                                 numeric_limits<double>::lowest(), 3))
       << endl;

  cout << format("PI = {0:.{1}f}", numbers::pi_v<long double>,
                 numeric_limits<long double>::digits10 - 1)
       << endl;
  // PI = 3.14159265358979323846264338327950
}
