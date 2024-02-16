#include <algorithm>
#include <format>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  using namespace std;

  map<int, char> dict{{1, 'a'}, {2, 'b'}, {3, 'c'}};

  {
    decltype(dict) temp{};
    transform(dict.begin(), dict.end(), inserter(temp, temp.begin()),
              [](const auto &item) {
                const auto &[key, val] = item;
                return pair{key * 2, val};
              });
    dict.swap(temp);
  }

  {
    decltype(dict) temp{};
    transform(dict.begin(), dict.end(), inserter(temp, temp.begin()),
              [](const auto &item) {
                const auto &[key, val] = item;
                return pair{key, toupper(val)};
              });
    dict.swap(temp);
  }

  for (auto &&[key, val] : dict) {
    cout << format("{}: {}", key, val) << endl;
  }
}
