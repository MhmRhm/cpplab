#include <format>
#include <iostream>
#include <iterator>
#include <ranges>

#include "modified_vector.h"

int main() {
  using namespace std;
  {
    NaiveVector<int> nv1{1, 2, 3}, nv2{9, 8, 7}, nv3{3, 2, 1};
    auto res{nv1 + nv2 + nv3};
    ranges::copy(res, ostream_iterator<int>{cout, ", "});
    cout << endl;
  }
  {
    MatureVector<int, vector<int>> mv1{vector{1, 2, 3}}, mv2{vector{9, 8, 7}},
        mv3{vector{3, 2, 1}};
    const auto res{mv1 + mv2 + mv3};
    for (size_t i{}; i < res.size(); i++) {
      cout << res[i] << endl;
    }
  }
}
