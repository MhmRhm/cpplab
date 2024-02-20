#include <array>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <typeinfo>

int main() {
  using namespace std;

  // Do not rely on char to be signed or unsigned.
  char a{};
  signed char b{};
  unsigned char c{};

  cout << string{typeid(a).name()} << endl;
  cout << string{typeid(b).name()} << endl;
  cout << string{typeid(c).name()} << endl;

  if (typeid(a) == typeid(b)) {
    cout << "typeid(a) == typeid(b)" << endl;
  }
  if (typeid(a) == typeid(c)) {
    cout << "typeid(a) == typeid(c)" << endl;
  }

  // Cpp 17
  byte h{0xff};
  cout << string{typeid(h).name()} << endl;

  // Cpp 20
  const char8_t *utf8{u8R"(到底是怎麼回事？)"};
  cout << reinterpret_cast<const char *>(utf8) << endl;

  cout << "\U00002705 \U0000274C" << endl;

  long double num1 = 1.234'567L;
  int num2 = num1;
  cout << format("num1 = {0:.3f}, num2 = {1}", num1, num2) << endl;
  // int num3{num1};

  struct SomeStruct {
    int val{};
  };
  class SomeClass {
  public:
    SomeClass(int val) { this->val = val; }
    int val{};
  };

  // Cpp 98
  SomeStruct data1{0};
  SomeClass data2(0);

  // Cpp 11 uniform initialization
  SomeStruct data3{0};
  SomeClass data4{0};
  void *ptr{};
  optional<int> opt1{};
  array<SomeStruct, 3> zarr{};
  array arr{1, 2, 3};
  // Cpp 20
  int *carr = new int[]{1, 2, 3};
  // for uniform initialization in templates, see below

  // opt1 contains value, *opt1 is a moved-from value
  optional<int> opt2{std::move(opt1)};
}

template <typename T> class AnotherClass final {
  T m_member{};
};
