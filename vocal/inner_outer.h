#pragma once

#include <iostream>

namespace {
int InnerID{0};
int OuterID{0};
} // namespace

class Inner {
public:
  Inner() { std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl; }
  Inner(const Inner &other) : id{other.id} {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }
  Inner &operator=(const Inner &src) {
    std::cout << __PRETTY_FUNCTION__ << " " << id << " = " << src.id
              << std::endl;
    id = src.id;
    return *this;
  }
  Inner(Inner &&other) noexcept : id{std::move(other.id)} {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }
  Inner &operator=(Inner &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << " " << id << " = " << src.id
              << std::endl;
    id = src.id;
    return *this;
  }
  virtual ~Inner() {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }

  auto operator<=>(const Inner &) const = default;

  friend void swap(Inner &lhs, Inner &rhs) {
    using namespace std;
    std::cout << __PRETTY_FUNCTION__ << " " << lhs.id << " <-> " << rhs.id
              << std::endl;
    swap(lhs.id, rhs.id);
  }
  friend std::ostream &operator<<(std::ostream &out, const Inner &inner) {
    return out << inner.id;
  }
  Inner(int identity, int redundant) : id{identity} {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }
  int id{InnerID += 1};
};

class Outer {
public:
  Outer() { std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl; }
  Outer(const Outer &other) : id{other.id} {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }
  Outer &operator=(const Outer &src) {
    std::cout << __PRETTY_FUNCTION__ << " " << id << " = " << src.id
              << std::endl;
    id = src.id;
    return *this;
  }
  Outer(Outer &&other) noexcept : id{std::move(other.id)} {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }
  Outer &operator=(Outer &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << " " << id << " = " << src.id
              << std::endl;
    id = src.id;
    return *this;
  }
  virtual ~Outer() {
    std::cout << __PRETTY_FUNCTION__ << " " << id << std::endl;
  }

  auto operator<=>(const Outer &) const = default;

  friend void swap(Outer &lhs, Outer &rhs) {
    using namespace std;
    std::cout << __PRETTY_FUNCTION__ << " " << lhs.id << " <-> " << rhs.id
              << std::endl;
    swap(lhs.id, rhs.id);
  }
  friend std::ostream &operator<<(std::ostream &out, const Outer &outer) {
    return out << outer.id;
  }

  int id{OuterID += 1};
};
