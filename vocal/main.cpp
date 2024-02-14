#include <format>
#include <iostream>

class Inner {
public:
  Inner() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner(const Inner &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner &operator=(const Inner &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  Inner(Inner &&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner &operator=(Inner &&src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
};

class Vocal {
  int m_data{};
  Inner m_inner{};

public:
  // If no user-declared constructors of any kind are provided for a class type,
  // the compiler will always declare a default constructor.
  Vocal(int data) {
    m_data = data;
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  };

  // If no user-defined copy constructors are provided for a class type, the
  // compiler will always declare a copy constructor.
  Vocal(const Vocal &src) {
    m_data = src.m_data;
    m_inner = src.m_inner;
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  }

  // If no user-defined copy assignment operators are provided for a class type,
  // the compiler will always declare one.
  Vocal &operator=(const Vocal &src) {
    if (this == &src)
      return *this;

    m_data = src.m_data;
    m_inner = src.m_inner;
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;

    return *this;
  }

  // If no user-defined move constructors are provided for a class type, and
  // all of the following is true:
  //    there are no user-declared copy constructors;
  //    there are no user-declared copy assignment operators;
  //    there are no user-declared move assignment operators;
  //    there is no user-declared destructor,
  // then the compiler will declare a move constructor.
  Vocal(Vocal &&src) noexcept {
    m_data = std::move(src.m_data);
    m_inner = std::move(src.m_inner);
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  }

  // If no user-defined move assignment operators are provided for a class type,
  // and all of the following is true:
  //    there are no user-declared copy constructors;
  //    there are no user-declared move constructors;
  //    there are no user-declared copy assignment operators;
  //    there is no user-declared destructor,
  // then the compiler will declare a move assignment operator.
  Vocal &operator=(Vocal &&src) {
    if (this == &src)
      return *this;

    m_data = std::move(src.m_data);
    m_inner = std::move(src.m_inner);
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;

    return *this;
  }

  ~Vocal() {
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  }
};

int main() {
  Vocal v1{1}, v2{2}, v3{3};
  Vocal v12{std::move(v3)};
  v2 = std::move(v3);
}
