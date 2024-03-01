#pragma once

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
  Inner &operator=(Inner &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  virtual ~Inner() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  friend void swap(Inner &lhs, Inner &rhs) {}
};

class Outer {
public:
  Outer() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Outer(const Outer &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Outer &operator=(const Outer &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  Outer(Outer &&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Outer &operator=(Outer &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  virtual ~Outer() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  friend void swap(Outer &lhs, Outer &rhs) {}
};
