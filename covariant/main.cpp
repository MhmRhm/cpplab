#include <format>
#include <iostream>
#include <memory>
#include <string>

struct Product {
  virtual ~Product() = default;
  virtual const char *getName() { return "Product"; }
};

class Factory {
public:
  virtual ~Factory() = default;
  virtual Product *getProduct() { return new Product{}; }
  // virtual std::unique_ptr<Product> getProduct() {
  //   return std::make_unique<Product>();
  // }
};

class Proton : public Factory {
public:
  virtual ~Proton() override = default;

  struct Iriz final : Product {
    ~Iriz() override = default;
    const char *getName() override {
      using namespace std::literals;
      return "Iriz";
    }
  };
  Iriz *getProduct() override { return new Iriz{}; }
  // std::unique_ptr<Iriz> getProduct() override {
  //   return std::make_unique<Iriz>();
  // }
};

int main() {
  using namespace std;
  unique_ptr<Proton::Iriz> car{Proton{}.getProduct()};
  cout << car->getName() << endl;
}
