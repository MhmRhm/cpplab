#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

struct ROUTER_CS_0 final {
  uint16_t vendoeID{};
  uint16_t productID{};
};

int main() {
  using namespace std;

  // Cpp 17
  unordered_map<unsigned int, string> vendorNames{};
  auto &&[iter1, inserted1] =
      vendorNames.try_emplace(0x05AC, "Apple"s); // string literal
  cout << format("inserted = {}, iter = {}", inserted1, iter1->second) << endl;

  auto &&[iter2, inserted2] = vendorNames.try_emplace(0x05AC, "Apple Inc."s);
  cout << format("inserted = {}, iter = {}", inserted2, iter2->second) << endl;

  for (auto &&[key, val] : vendorNames) {
    cout << format("key = {}, val = {}", key, val) << endl;
  }

  // Cpp 20 Designated Initializers
  // vendoeID is zero initialized
  // must be an aggregate type
  ROUTER_CS_0 cs0{.productID = 0xF1A7};

  // Cpp 17
  auto &[vendoeID, productID]{cs0};
  productID = 0xD158;
  cout << format("cs0.vendoeID = {:0X}, cs0.productID = {:0X}", cs0.vendoeID,
                 cs0.productID)
       << endl;
}
