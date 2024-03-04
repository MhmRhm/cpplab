#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <iterator>
#include <locale>
#include <numeric>
#include <queue>
#include <ranges>
#include <typeinfo>
#include <vector>

#include "../vocal/inner_outer.h"

template <typename T>
using owstream_iterator =
    std::ostream_iterator<T, wchar_t, std::char_traits<wchar_t>>;

int main() {
  using namespace std;
  {
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
  {
    array<Inner, 6> src1{};
    sort(begin(src1), end(src1),
         [](const Inner &lhs, const Inner &rhs) { return lhs > rhs; });
    copy(cbegin(src1), cend(src1), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    ranges::sort(src1);
    copy(cbegin(src1), cend(src1), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    // projection
    ranges::sort(src1, greater{}, &Inner::id);
    copy(cbegin(src1), cend(src1), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    struct NLSeperator : ctype<wchar_t> {
      bool do_is(mask m, char_type c) const {
        if (m & space) {
          return false;
        }
        return ctype::do_is(m, c);
      }
    };
    wcin.imbue(locale{wcin.getloc(), new NLSeperator{}});
    vector<wstring> names{};
    wstring name{};
    auto input{views::istream<wstring>(wcin) | views::join |
               views::take_while([](const wchar_t &c) { return c != L'/'; }) |
               views::lazy_split(L'\n')};
    for (const auto &bunch : input) {
      for (const auto &c : bunch) {
        name.push_back(c);
      }
      names.push_back(name);
      name = L"";
    }
    ranges::copy(names, owstream_iterator<wstring>{wcout, L", "});
    wcout << endl;
  }
}
