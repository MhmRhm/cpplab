#include <exception>
#include <format>
#include <iostream>
#include <limits>
#include <new>
#include <source_location>
#include <typeinfo>

#include "../vocal/inner_outer.h"

// clang-format off
struct Good final {
  Good() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  ~Good() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
struct Bad final {
  Good good{};
  Bad() try : good{Good{}} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    throw std::runtime_error{"Bad Exception"};
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    // cleanup
    throw;
  }
  ~Bad() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
// clang-format off

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
    // clean-up
    throw_with_nested(Outer{});
    // rest of clean-up
  }
}
void run3() { throw std::source_location::current(); }

int main() {
  using namespace std;

  try {
    run2();
  } catch (const Outer &e) {
    cerr << typeid(e).name() << endl;
    try {
      cerr << "catching Outter" << endl;
      rethrow_if_nested(e);
    } catch (const Inner &e) {
      cerr << "catching Inner" << endl;
      cerr << typeid(e).name() << endl;
    }
  }

  try {
    run3();
  } catch (const source_location &e) {
    cerr << format("{}, {}, line {}", e.file_name(), e.function_name(),
                   e.line())
         << endl;
  }

  try {
    Bad{};
  } catch (const std::exception &e) {
    cerr << e.what() << endl;
  }

  try {
    set_new_handler(handler2);
    byte *memory{new byte[1024 * 1024 * 1024 * 1024UL]};
  } catch (const std::exception &e) {
    cerr << e.what() << endl;
  }
}
