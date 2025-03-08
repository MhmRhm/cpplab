#include <array>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <typeinfo>

#include "../type_inference/typename.h"

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

  int *ptr_to_int{};
  const auto const_ptr_to_int{ptr_to_int};
  const auto *ptr_to_const_int{ptr_to_int};
  std::cout << type_name<decltype(const_ptr_to_int)>() << std::endl;
  std::cout << type_name<decltype(ptr_to_const_int)>() << std::endl;

  // Cpp 20
  const char8_t *utf8{u8R"(到底是怎麼回事？)"};
  cout << reinterpret_cast<const char *>(utf8) << endl;

  cout << "\U00002705 \U0000274C" << endl;
  cout << "\101"   // octal
       << "\x41"   // hex
       << "\u0041" // unicode
       << "\U00000041" << endl;

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
  [[maybe_unused]] SomeStruct data1{0};
  [[maybe_unused]] SomeClass data2(0);

  // Cpp 11 uniform initialization
  [[maybe_unused]] SomeStruct data3{0};
  [[maybe_unused]] SomeClass data4{0};
  [[maybe_unused]] void *ptr{};
  [[maybe_unused]] optional<int> opt1{};
  [[maybe_unused]] array<SomeStruct, 3> zarr{};
  [[maybe_unused]] array arr{1, 2, 3};
  [[maybe_unused]] int stack_arr[8]{};
  // Cpp 20
  [[maybe_unused]] int *fcarr = new int[]{1, 2, 3};
  // For uniform initialization in templates, see below

  // opt1 contains value, *opt1 is a moved-from value
  [[maybe_unused]] optional<int> opt2{std::move(opt1)};
}

template <typename T> class AnotherClass final {
  T m_member{};
};
