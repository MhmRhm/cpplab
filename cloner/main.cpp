#include <iostream>
#include <memory>

// single-level drived class cloning
class Parent {
public:
  virtual ~Parent() = default;
  virtual std::unique_ptr<Parent> clone() const = 0;
};
template <typename Child> class OneLevelCloner : public Parent {
public:
  virtual std::unique_ptr<Parent> clone() const override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::unique_ptr<Parent>{
        new Child{*static_cast<const Child *>(this)}};
  }
};
class Child : public OneLevelCloner<Child> {
public:
  Child() = default;
  Child(const Child &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
class GrandChild : public Child {
public:
  GrandChild() = default;
  GrandChild(const GrandChild &) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

// multi-level drived class cloning
class Base {
public:
  virtual ~Base() = default;
  Base *clone() const;
};
class ClonerBase {
public:
  virtual ~ClonerBase() = default;
  virtual Base *clone() const = 0;
};
Base *Base::clone() const {
  return dynamic_cast<const ClonerBase *>(this)->clone();
}
template <typename Drived> class MultiLevelCloner : public ClonerBase {
public:
  virtual Base *clone() const override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return new Drived{*static_cast<const Drived *>(this)};
  }
};
class Drived : public Base, public MultiLevelCloner<Drived> {
public:
  Drived() = default;
  Drived(const Drived &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
class OverDrived : public Drived, public MultiLevelCloner<OverDrived> {
public:
  OverDrived() = default;
  OverDrived(const OverDrived &) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int main() {
  using namespace std;

  unique_ptr<Parent> parentPtr{new Child{}};
  auto chPtr{parentPtr->clone()};

  parentPtr.reset(new GrandChild{});
  auto gchPtr{parentPtr->clone()};

  unique_ptr<Base> basePtr{new Drived{}};
  unique_ptr<Base> drPtr{basePtr->clone()};

  basePtr.reset(new OverDrived{});
  // The following will result in a `Segmentation fault (core dumped)`
  // https://github.com/PacktPublishing/Hands-On-Design-Patterns-with-CPP
  unique_ptr<Base> odrPtr{basePtr->clone()};
}
