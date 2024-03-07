#include <format>
#include <iostream>
#include <iterator>
#include <map>
#include <set>

#include "../vocal/inner_outer.h"

int main() {
  using namespace std;
  int mark{};

  map dict{{0, Inner{}}, {1, Inner{}}, pair{2, Inner{}}};
  cout << format("MARK {}", mark += 1) << endl;
  {
    if (auto [itr, success]{dict.insert({3, Inner{}})}; success) {
      cout << format("{{{} - {}}} added", itr->first, itr->second.id) << endl;
    }
  }
  cout << format("MARK {}", mark += 1) << endl;
  {
    if (auto [itr, inserted]{dict.insert_or_assign(0, Inner{})}; inserted) {
      cout << format("{{{} - {}}} added", itr->first, itr->second.id) << endl;
    } else {
      cout << format("{{{} - {}}} reassigned", itr->first, itr->second.id)
           << endl;
    }
  }
  cout << format("MARK {}", mark += 1) << endl;
  {
    // allows the new element to be constructed while avoiding unnecessary copy
    // or move operations. The element may be constructed even if there already
    // is an element with the key in the container.
    if (auto [itr, success]{dict.emplace(0, Inner{1000})}; success) {
      cout << format("{{{} - {}}} emplaced", itr->first, itr->second.id)
           << endl;
    }
  }
  cout << format("MARK {}", mark += 1) << endl;
  {
    // these functions do not move from rvalue arguments if the insertion does
    // not happen. makes it easy to manipulate maps whose values are move-only
    // types, such as std::map<std::string, std::unique_ptr<foo>>.
    if (auto [itr, success]{dict.try_emplace(0, Inner{1001})}; success) {
      cout << format("{{{} - {}}} emplaced", itr->first, itr->second.id)
           << endl;
    }
  }
  cout << format("MARK {}", mark += 1) << endl;
  {
    auto itr{dict.find(0)};
    if (itr != end(dict)) {
      cout << format("found {{{} - {}}}", itr->first, itr->second.id) << endl;
    }
    if (dict.contains(1)) {
      cout << format("found {{{} - {}}}", 1, dict[1].id) << endl;
    }
    if (dict[-1].id) {
      cout << format("found {{{} - {}}}", -1, dict[-1].id) << endl;
    }
  }
  cout << format("MARK {}", mark += 1) << endl;
  for (auto &&[id, inner] : dict) {
    // id *= -1;
  }
}
