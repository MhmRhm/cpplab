#include <chrono>
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
  Good() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
  ~Good() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
};
struct Bad final {
  Good good{};
  Bad() try : good{Good{}}
  {
    std::cout << std::source_location::current().function_name() << std::endl;
    throw std::runtime_error{"Bad Exception"};
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    // cleanup
    throw;
  }
  ~Bad() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
};
// clang-format on

bool save_document() { return true; }

namespace {
std::byte *reservoir{new std::byte[1024 * 1024 * 1024]};
} // namespace

void final_attempt() {
  using namespace std;
  cout << "final attempt" << endl;
  // set_new_handler(nullptr);
  delete[] reservoir;
  reservoir = nullptr;
  save_document();
}
void first_attempt() {
  using namespace std;
  cout << "first attempt" << endl;
  set_new_handler(final_attempt);
  cout << "Close other applications then hit enter." << endl;
  cin.ignore();
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

class ExactException : public std::exception {
public:
  ExactException(std::string explanation, std::source_location location =
                                              std::source_location::current())
      : m_explanation{std::move(explanation)}, m_location{std::move(location)},
        m_time{std::chrono::system_clock::now()} {}
  virtual const std::chrono::system_clock::time_point when() const noexcept {
    return m_time;
  }
  virtual const std::source_location &where() const noexcept {
    return m_location;
  }
  const char *what() const noexcept override { return m_explanation.data(); }

private:
  std::chrono::system_clock::time_point m_time{};
  std::source_location m_location{};
  std::string m_explanation{};
};
void run3() { throw ExactException{"run3 threw"}; }

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
  } catch (const ExactException &e) {
    cerr << format("{}\t{}:{}: {}", e.when(), e.where().file_name(),
                   e.where().line(), e.what())
         << endl;
  }

  try {
    Bad{};
  } catch (const std::exception &e) {
    cerr << e.what() << endl;
  }

  try {
    set_new_handler(first_attempt);
    byte *memory{new byte[1024 * 1024 * 1024 * 1024UL]};
  } catch (const std::exception &e) {
    cerr << e.what() << endl;
  }
}
