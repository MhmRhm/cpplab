#include <iostream>
#include <string_view>

#include "../type_inference/typename.h"

class Type final {
public:
  Type() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type(const Type &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type(Type &&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type &operator=(const Type &) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  Type &operator=(Type &&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  ~Type() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

namespace {
int LineNumber{};
} // namespace

template <class T> T &&myForward(T &arg) {
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
  return static_cast<T &&>(arg);
}

template <class T> void typeIndicator(T &&arg) {
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
}

template <class T> void wrapper(T &&arg) {
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
  typeIndicator(myForward<T>(arg));
  T temp = myForward<T>(arg);
}

int main() {
  Type var{};
  wrapper(var);

  std::cout << std::endl;
  wrapper(std::move(var));
}
