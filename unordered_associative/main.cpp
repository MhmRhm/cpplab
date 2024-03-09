#include <cmath>
#include <format>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
  using namespace std;

  auto absHash{[](int num) { return hash<int>{}(abs(num)); }};

  unordered_map<int, string, decltype(absHash)> table{
      pair{1, "1"s}, {2, "2"s}, {-1, "-1"s}, {-2, "-2"s}};

  cout << format("bucket count: {}, max bucket count: {}, load factor: {}, max "
                 "load factor: {}",
                 table.bucket_count(), table.max_bucket_count(),
                 table.load_factor(), table.max_load_factor())
       << endl;

  size_t bucketIndex{table.bucket(1)};
  for (auto it{table.cbegin(bucketIndex)}; it != table.cend(bucketIndex);
       ++it) {
    cout << format("{{{}, {}}}", it->first, it->second) << endl;
  }
}
