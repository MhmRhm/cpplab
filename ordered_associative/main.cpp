#include <format>
#include <iostream>
#include <iterator>
#include <map>
#include <set>

#include "../vocal/inner_outer.h"

int main() {
  using namespace std;
  int mark{};
  {
    map dict{{0, Inner{}}, {1, Inner{}}, pair{2, Inner{}}};
    cout << format("MARK {}", 1) << endl;
    {
      if (auto [itr, success]{dict.insert({3, Inner{}})}; success) {
        cout << format("{{{}, {}}} added", itr->first, itr->second.id) << endl;
      }
    }
    cout << format("MARK {}", 2) << endl;
    {
      if (auto [itr, inserted]{dict.insert_or_assign(0, Inner{})}; inserted) {
        cout << format("{{{}, {}}} added", itr->first, itr->second.id) << endl;
      } else {
        cout << format("{{{}, {}}} reassigned", itr->first, itr->second.id)
             << endl;
      }
    }
    cout << format("MARK {}", 3) << endl;
    {
      // Allows the new element to be constructed while avoiding unnecessary
      // copy or move operations. The element may be constructed even if there
      // already is an element with the key in the container.
      if (auto [itr, success]{dict.emplace(0, Inner{1000, 0})}; success) {
        cout << format("{{{}, {}}} emplaced", itr->first, itr->second.id)
             << endl;
      }
    }
    cout << format("MARK {}", 4) << endl;
    {
      // These functions do not move from rvalue arguments if the insertion does
      // not happen. Makes it easy to manipulate maps whose values are move-only
      // types, such as std::map<std::string, std::unique_ptr<foo>>.
      if (auto [itr, success]{dict.try_emplace(0, 1001, 1)}; success) {
        cout << format("{{{}, {}}} emplaced", itr->first, itr->second.id)
             << endl;
      }
    }
    cout << format("MARK {}", 5) << endl;
    {
      auto itr{dict.find(0)};
      if (itr != end(dict)) {
        cout << format("found {{{}, {}}}", itr->first, itr->second.id) << endl;
      }
      if (dict.contains(1)) {
        cout << format("found {{{}, {}}}", 1, dict[1].id) << endl;
      }
      if (dict[-1].id) {
        cout << format("found {{{}, {}}}", -1, dict[-1].id) << endl;
      }
    }
    cout << format("MARK {}", 6) << endl;
    // decltype(dict) dict2{};
    {
      // node_handle owns the data
      if (auto node_handle{dict.extract(-1)}; node_handle) {
        cout << format("{{{}, {}}}", node_handle.key(), node_handle.mapped().id)
             << endl;
        // No iterators or references are invalidated. Unless they are obtained
        // from node_handle. If the insertion is successful, pointers and
        // references obtained to that element before it was extracted become
        // valid.
        // dict2.insert(std::move(node_handle));
      }
    }
    cout << format("MARK {}", 7) << endl;
    for (auto &&[id, inner] : dict) {
      // id *= -1;
    }
  }
  cout << format("MARK {}", 8) << endl;
  {
    map<uint16_t, uint16_t> map1{{0, 0}, {1, 1}, {2, 2}};
    map<uint16_t, uint16_t> map2{{2, 2}, {3, 3}, {4, 4}};
    map2.merge(map1);
    for (auto &[k, v] : map1) {
      cout << format("{{{}, {}}} ", k, v);
    }
    cout << "\n";
    for (auto &[k, v] : map2) {
      cout << format("{{{}, {}}} ", k, v);
    }
    cout << endl;
  }
  cout << format("MARK {}", 9) << endl;
  {
    multimap mdict{pair{1, Outer{}}, pair{2, Outer{}}, pair{2, Outer{}},
                   pair{2, Outer{}}, pair{2, Outer{}}, pair{3, Outer{}}};

    cout << format("MARK {}", 10) << endl;

    auto lb{mdict.lower_bound(2)};
    auto ub{mdict.upper_bound(2)};
    auto er{mdict.equal_range(2)};
    if (er.first != lb || er.second != ub) {
      cerr << "something is wrong" << endl;
    }

    cout << format("MARK {}", 11) << endl;

    if (auto node_handle{mdict.extract(2)}; node_handle) {
      cout << format("{{{}, {}}}", node_handle.key(), node_handle.mapped().id)
           << endl;
    }
  }
}
