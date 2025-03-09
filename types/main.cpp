#include <array>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <source_location>
#include <string>
#include <typeinfo>

#include "../type_inference/typename.h"

void variableArgFunc([[maybe_unused]] std::initializer_list<int> args) {}
class VariableArgCtor {
public:
  VariableArgCtor(std::initializer_list<int> args) {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
  VariableArgCtor(int a, int b, int c) {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
};

int main() {
  using namespace std;

  variableArgFunc({0, 1, 2});
  VariableArgCtor{0, 1, 2};

  // Do not rely on char to be signed or unsigned.
  char a{};
  signed char b{};
  unsigned char c{};

  if (typeid(a) == typeid(b)) {
    cout << "typeid(char) == typeid(signed char)" << endl;
  }
  if (typeid(a) == typeid(c)) {
    cout << "typeid(char) == typeid(unsigned char)" << endl;
  }

  cout << string{typeid(a).name()} << endl;
  cout << string{typeid(b).name()} << endl;
  cout << string{typeid(c).name()} << endl;

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
  SomeStruct data1{0};
  SomeClass data2(0);

  // Cpp 11 uniform initialization
  SomeStruct data3{0};
  SomeClass data4{0};
  void *ptr{};
  optional<int> opt1{};
  array<SomeStruct, 3> zarr{};
  array arr{1, 2, 3};
  int stack_arr[8]{};
  // Cpp 20
  int *fcarr = new int[]{1, 2, 3};
  // For uniform initialization in templates, see below

  // opt1 contains value, *opt1 is a moved-from value
  optional<int> opt2{std::move(opt1)};
}

template <typename T> class AnotherClass final {
  T m_member{};
};
