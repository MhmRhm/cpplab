#include <algorithm>
#include <array>
#include <chrono>
#include <execution>
#include <format>
#include <iostream>
#include <map>
#include <numeric>
#include <syncstream>
#include <thread>
#include <vector>

#include "../vocal/inner_outer.h"

int main() {
  using namespace std;

  vector anchorsVec{
      pair{"S.E. Cupp"s, 45}, {"Dr. Sanjay Gupta"s, 54}, {"Van Jones"s, 55}};
  map anchorsMap{
      pair{"S.E. Cupp"s, 45}, {"Dr. Sanjay Gupta"s, 54}, {"Van Jones"s, 55}};

  // remove-erase-idiom
  auto isSenior{[](const auto &val) { return val.second > 50; }};
  auto it{remove_if(begin(anchorsVec), end(anchorsVec), isSenior)};
  anchorsVec.erase(it, end(anchorsVec));
  for (auto &&person : anchorsVec) {
    cout << format("{}, {} y.o.", person.first, person.second) << endl;
  }

  // Cpp 20 uniform container erasure
  erase_if(anchorsMap, isSenior);
  for (auto &&person : anchorsMap) {
    cout << format("{}, {} y.o.", person.first, person.second) << endl;
  }

  array inners{Inner{}, Inner{}, Inner{}, Inner{}};

  auto t1{chrono::steady_clock::now()};
  for_each(cbegin(inners), cend(inners), [](const Inner &inner) {
    this_thread::sleep_for(1s);
    cout << format("inner.id = {}", inner.id) << endl;
  });
  auto t2{chrono::steady_clock::now()};
  cout << format("t2 - t1 = {}", t2 - t1) << endl;

  auto t3{chrono::steady_clock::now()};
  for_each(execution::par_unseq, cbegin(inners), cend(inners),
           [](const Inner &inner) {
             this_thread::sleep_for(1s);
             osyncstream(cout) << format("inner.id = {}", inner.id) << endl;
           });
  auto t4{chrono::steady_clock::now()};
  cout << format("t4 - t3 = {}", t4 - t3) << endl;

  // Cpp 20
  shift_left(begin(inners), end(inners), 1);
  shift_right(begin(inners), end(inners), 1);
  for (auto &&inner : inners) {
    cout << inner.id << endl;
  }

  vector v1{1, 2, 3};
  vector v2{9, 8, 7};
  vector<int> v3{};
  transform(cbegin(v1), cend(v1), cbegin(v2), back_inserter(v3), plus<>{});
  copy(cbegin(v3), cend(v3), ostream_iterator<int>{cout, ", "});
  cout << endl;
}
