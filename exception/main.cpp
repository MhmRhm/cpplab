#include <exception>
#include <format>
#include <iostream>
#include <limits>
#include <new>
#include <source_location>
#include <typeinfo>

#include "../vocal/inner_outer.h"

static std::byte *reservoir{new std::byte[1024 * 1024 * 1024]};
void handler1() {
  // std::set_new_handler(nullptr);
  std::cout << "handler1" << std::endl;
  delete[] reservoir;
  reservoir = nullptr;
}
void handler2() {
  std::cout << "handler2" << std::endl;
  std::set_new_handler(handler1);
};

void run1() { throw Inner{}; }
void run2() {
  using namespace std;
  try {
    cerr << "throwing Inner" << endl;
    run1();
  } catch (...) {
    cerr << "throwing Outer" << endl;
    throw_with_nested(Outer{});
  }
}
void run3() { throw std::source_location::current(); }

int main() {
  using namespace std;

  try {
    run2();
  } catch (const Outer &e) {
    cout << typeid(e).name() << endl;
    try {
      cout << "catching Outter" << endl;
      rethrow_if_nested(e);
    } catch (const Inner &e) {
      cout << typeid(e).name() << endl;
      cout << "catching Inner" << endl;
    }
  }

  try {
    run3();
  } catch (const source_location &e) {
    cout << format("{}, {}, line {}", e.file_name(), e.function_name(),
                   e.line())
         << endl;
  }

  try {
    set_new_handler(handler2);
    byte *memory{new byte[1024 * 1024 * 1024 * 1024UL]};
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
