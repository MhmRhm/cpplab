#include <format>
#include <iostream>
#include <memory>
#include <string>

struct Product {
  int id{};
  virtual ~Product() = default;

  static const char *getName() { return "Product"; }
  virtual void setID(int id = 1000) { this->id = id; };
};

class Factory {
public:
  virtual ~Factory() = default;
  virtual Product *getProduct() { return new Product{}; }
  // virtual std::unique_ptr<Product> getProduct() {
  //   return std::make_unique<Product>();
  // }
};

struct Iriz final : Product {
  ~Iriz() override = default;
  Iriz &operator=(const Iriz &rhs) {
    if (&rhs == this) {
      return *this;
    }
    Product::operator=(rhs);
    return *this;
  }

  static const char *getName() { return "Iriz"; }
  virtual void setID(int id = 2021) override { this->id = id; };
};

class Proton : public Factory {
public:
  virtual ~Proton() override = default;

  Iriz *getProduct() override { return new Iriz{}; }
  // std::unique_ptr<Iriz> getProduct() override {
  //   return std::make_unique<Iriz>();
  // }
};

int main() {
  using namespace std;
  unique_ptr<Iriz> car{Proton{}.getProduct()};
  cout << car->getName() << endl;

  Product *product{car.get()};
  product->setID();
  cout << product->getName() << endl;
  cout << product->id << endl;
}
