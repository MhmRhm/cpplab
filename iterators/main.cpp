#include <array>
#include <format>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>

#include "../vocal/inner_outer.h"

int main() {
  using namespace std;

  deque<Inner> dst1{};
  auto pos{begin(dst1)};

  array<Inner, 3> src1{};
  copy(cbegin(src1), cend(src1), back_inserter(dst1));
  copy(cbegin(dst1), cend(dst1), ostream_iterator<Inner>{cout, ", "});
  cout << endl;

  array<Inner, 3> src2{};
  copy(cbegin(src2), cend(src2), front_inserter(dst1));
  copy(cbegin(dst1), cend(dst1), ostream_iterator<Inner>{cout, ", "});
  cout << endl;

  // https://en.cppreference.com/w/cpp/container#Iterator_invalidation
  // invalid operation although it may work
  array<Inner, 3> src3{};
  copy(cbegin(src3), cend(src3), inserter(dst1, pos));
  copy(cbegin(dst1), cend(dst1), ostream_iterator<Inner>{cout, ", "});
  cout << endl;

  array<Inner, 3> src4{};
  copy(make_move_iterator(begin(src4)), make_move_iterator(end(src4)),
       make_reverse_iterator(end(dst1)));
  copy(cbegin(dst1), cend(dst1), ostream_iterator<Inner>{cout, ", "});
  cout << endl;

  auto ritr{crbegin(dst1) + 1};
  auto itr{cend(dst1) - 1};
  cout << "*ritr = " << *ritr << ", *ritr.base = " << *ritr.base()
       << ", *itr = " << *itr << endl;
}
