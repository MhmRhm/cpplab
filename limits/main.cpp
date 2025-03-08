#include <cfenv>
#include <cmath>
#include <format>
#include <iostream>
#include <limits>
#include <numbers>

using namespace std;

void show_fe_exceptions() {
  // Pole error occurred in an earlier floating-point operation
  if (fetestexcept(FE_DIVBYZERO))
    cout << "Has FE_DIVBYZERO" << endl;
  // inexact result: rounding was necessary to store the result of an earlier
  // floating-point operation
  if (fetestexcept(FE_INEXACT))
    cout << "Has FE_INEXACT" << endl;
  // domain error occurred in an earlier floating-point operation
  if (fetestexcept(FE_INVALID))
    cout << "Has FE_INVALID" << endl;
  // the result of the earlier floating-point operation was too large to be
  // representable
  if (fetestexcept(FE_OVERFLOW))
    cout << "Has FE_OVERFLOW" << endl;
  // the result of the earlier floating-point operation was subnormal with a
  // loss of precision
  if (fetestexcept(FE_UNDERFLOW))
    cout << "Has FE_UNDERFLOW" << endl;
  // bitwise OR of all supported floating-point exceptions
  if (fetestexcept(FE_ALL_EXCEPT))
    cout << "Has FE_ALL_EXCEPT" << endl;
  else
    cout << "Has no exceptions" << endl;

  feclearexcept(FE_ALL_EXCEPT);
}

int main() {
  cout << format("max double = {}", numeric_limits<double>::max()) << endl;
  cout << format("min double = {}", numeric_limits<double>::min()) << endl;
  cout << format("low double = {}", numeric_limits<double>::lowest()) << endl;

  // Cpp 20 Variable Templates
  cout << format("Pi = {:5.3f}, e = {:5.3f}, √2 = {:5.3f}", numbers::pi,
                 numbers::e, numbers::sqrt2_v<double>)
       << endl;

  double anan = nan("abc");
  cout << format("anan == anan? {}", anan == anan) << endl;

  feclearexcept(FE_ALL_EXCEPT);
  auto res{std::sqrt(-1)};
  cout << format("sqrt(-1) = {}, isnan(sqrt(-1))? {}, fetestexcept? {}", res,
                 isnan(res), fetestexcept(FE_ALL_EXCEPT))
       << endl;

  feclearexcept(FE_ALL_EXCEPT);
  double snan = std::numeric_limits<double>::signaling_NaN();
  std::cout << "After sNaN was obtained:" << endl;
  show_fe_exceptions();

  double qnan = snan * 2.0;
  std::cout << "After sNaN was multiplied by 2:" << endl;
  show_fe_exceptions();

  double qnan2 = qnan * 2.0;
  std::cout << "After the quieted NaN was multiplied by 2" << endl;
  show_fe_exceptions();

  std::cout << "The result is " << qnan2 << endl;

  cout << "Number of fractional part digits that will survive round trip in "
          "double = "
       << std::numeric_limits<double>::digits10 << endl;
}
