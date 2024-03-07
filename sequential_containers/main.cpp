#include <array>
#include <deque>
#include <format>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <span>
#include <type_traits>
#include <vector>

#include "../vocal/inner_outer.h"

int main() {
  using namespace std;
  {
    array a1{"abc"};
    // Cpp 20
    array a2{to_array("abc")};
    for (auto &&i : a1)
      cout << i << endl;
    for (auto &&i : a2)
      cout << i << endl;
  }
  {
    int i1{1}, i2{2}, i3{3};
    const vector v1{ref(i1), ref(i2), ref(i3)};
    auto square{[](const auto &v) {
      for (const auto &i : v) {
        i *= i;
      }
    }};
    square(v1);
    cout << format("i1 = {}, i2 = {}, i3 = {}", i1, i2, i3) << endl;

    vector v2{1, 2, 3};
    vector v3{1, 2, 3, -1};
    auto res{v3 <=> v2};
    cout << format("v3 > v2: {}", is_gt(res)) << endl;

    // Cpp 20
    vector v4{1, 2, 3, 4};
    erase_if(v4, [](auto &i) { return i & 0b1; });
    copy(cbegin(v4), cend(v4), ostream_iterator<int>{cout, ", "});
    cout << endl;

    vector<Inner> v5{};
    v5.reserve(4);
    {
      Inner inner{};
      v5.push_back(inner);
    }
    v5.push_back(Inner{});
    v5.emplace_back();

    cout << format("is std::size signed int: {}",
                   is_signed_v<decltype(size(v5))>)
         << endl;
    // Cpp 20
    cout << format("is std::ssize signed int: {}",
                   is_signed_v<decltype(ssize(v5))>)
         << endl;

    v5.clear();
    cout << format("v5.size() = {}, v5.capacity() = {}", v5.size(),
                   v5.capacity())
         << endl;
    decltype(v5){}.swap(v5);
    cout << format("v5.size() = {}, v5.capacity() = {}", v5.size(),
                   v5.capacity())
         << endl;
  }
  {
    list l1{1, 2, 8, 9};
    list l2{3, 4, 5, 6, 7};
    auto itr1{find(cbegin(l1), cend(l1), 8)};
    l1.splice(itr1, l2);
    copy(cbegin(l1), cend(l1), ostream_iterator<int>{cout, ", "});
    cout << endl;
    copy(cbegin(l2), cend(l2), ostream_iterator<int>{cout, ", "});
    cout << endl;
  }
  {
    list l1{1, 2, 3};
    forward_list f1{1, 2, 3};
    auto litr{l1.cbegin()};
    auto fitr{f1.cbefore_begin()};
    for (auto &&i : {1, 2, 3}) {
      l1.insert(litr, i);
      f1.insert_after(fitr, i);
    }
    copy(cbegin(f1), cend(f1), ostream_iterator<int>{cout, ", "});
    cout << endl;
    copy(cbegin(l1), cend(l1), ostream_iterator<int>{cout, ", "});
    cout << endl;
  }
  {
    auto square{[](span</*const*/ int> s) {
      for (auto &&i : s) {
        i *= i;
      }
    }};

    int carr[]{1, 2, 3};
    span<int> s1(carr);
    span<int> s2{s1.subspan(2, 5)};
    square(s2);
    copy(cbegin(s2), cend(s2), ostream_iterator<int>{cout, ", "});
    cout << endl;
  }
  {
    vector<int> p1{9, 5, 1, 3, 7, 8};
    priority_queue<int, vector<int>, less<>> p2{};

    for (auto &&i : p1) {
      p2.push(i);
    }
    make_heap(begin(p1), end(p1), less<>{});

    while (p1.size() && p2.size()) {
      pop_heap(begin(p1), end(p1), less<>{});
      cout << p1.back() << " " << p2.top() << endl;
      p1.pop_back();
      p2.pop();
    }
  }
}
