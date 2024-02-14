#include <format>
#include <iostream>
#include <vector>

class Inner {
public:
  Inner() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner(const Inner &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner &operator=(const Inner &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  Inner(Inner &&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Inner &operator=(Inner &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  friend void swap(Inner &lhs, Inner &rhs) {}
};

class Vocal {
  int m_data{};
  Inner m_inner{};

public:
  // If no user-declared constructors of any kind are provided for a class type,
  // the compiler will always declare a default constructor.
  Vocal(int data) : m_data{data}, m_inner{Inner{}} {
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  };

  // If no user-defined copy constructors are provided for a class type, the
  // compiler will always declare a copy constructor.
  Vocal(const Vocal &src) : m_data{src.m_data}, m_inner{src.m_inner} {
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  }

  // If no user-defined copy assignment operators are provided for a class type,
  // the compiler will always declare one.
  Vocal &operator=(const Vocal &rhs) {
    Vocal temp{rhs};
    swap(*this, temp);

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
    swap(*this, src);

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
  Vocal &operator=(Vocal &&rhs) noexcept {
    swap(*this, rhs);

    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;

    return *this;
  }

  friend void swap(Vocal &lhs, Vocal &rhs) noexcept {
    using std::swap;
    swap(lhs.m_data, rhs.m_data);
    swap(lhs.m_inner, rhs.m_inner);
  }

  virtual ~Vocal() {
    std::cout << std::format("{}, {}", __PRETTY_FUNCTION__, m_data)
              << std::endl;
  }
};

int main() {
  Vocal v1{1}, v2{2}, v3{3};
  Vocal v12{std::move(v3)};
  // v2 = std::move(v3);

  // std::vector<Vocal> vocals1{};
  // vocals1.push_back(Vocal{10});
  // vocals1.push_back(Vocal{20});
  // vocals1.push_back(Vocal{30});
  // vocals1.push_back(Vocal{40});
}
