#include <algorithm>
#include <array>
#include <cstdint>
#include <deque>
#include <exception>
#include <format>
#include <iostream>
#include <iterator>
#include <list>
#include <locale>
#include <numeric>
#include <ranges>
#include <typeinfo>
#include <vector>

#include "../vocal/inner_outer.h"

template <typename T>
using owstream_iterator =
    std::ostream_iterator<T, wchar_t, std::char_traits<wchar_t>>;

std::vector<uint16_t> operator""_t(const char *str, size_t len) {
  using namespace std;

  auto is_valid{[](const auto &c) {
    switch (c) {
    case ' ':
      return false;
    case '0':
    case '1':
    case '2':
      return true;
    default:
      throw runtime_error{"invalid trit"};
    }
  }};

  string_view chars{str, len};
  auto bytes{chars | views::filter(is_valid) | views::chunk(7) | views::all |
             views::transform([](auto &&chars) {
               uint16_t word{};
               for (auto &&c : chars) {
                 word <<= 2;
                 word |= (c - '0');
               }
               return word;
             }) |
             views::common};

  return vector<uint16_t>{bytes.begin(), bytes.end()};
}

int main() {
  using namespace std;
  {
    deque<Inner> dst{};
    auto pos{begin(dst)};

    array<Inner, 3> src1{};
    copy(cbegin(src1), cend(src1), back_inserter(dst));
    copy(cbegin(dst), cend(dst), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    array<Inner, 3> src2{};
    copy(cbegin(src2), cend(src2), front_inserter(dst));
    copy(cbegin(dst), cend(dst), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    // https://en.cppreference.com/w/cpp/container#Iterator_invalidation
    // invalid operation although it may work
    array<Inner, 3> src3{};
    copy(cbegin(src3), cend(src3), inserter(dst, pos));
    copy(cbegin(dst), cend(dst), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    array<Inner, 3> src4{};
    copy(make_move_iterator(begin(src4)), make_move_iterator(end(src4)),
         make_reverse_iterator(end(dst)));
    copy(cbegin(dst), cend(dst), ostream_iterator<Inner>{cout, ", "});
    cout << endl;

    auto ritr{++crbegin(dst)};
    auto itr{--cend(dst)};
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
  {
    try {
      for (auto &&word : "0222 2220 0000   0002 2220   0000 2222"_t) {
        cout << format("{0:0>4X} - {0:0>16b}", word) << endl;
      }
    } catch (const exception &e) {
      cerr << e.what() << endl;
    }
  }
  {
    // https://www.modernescpp.com/index.php/expression-templates/
    vector vecA{1, 2, 3};
    vector vecB{.1, .1, .1};
    vector vecC{9, 8, 7};
    vector vecX{0, 1, 10};

    // Cpp 23
    auto quadraticEquation{views::zip_transform(
        [](auto a, auto b, auto c, auto x) { return a * x * x + b * x + c; },
        vecA, vecB, vecC, vecX)};
    // compile with gcc or msvc
    // ranges::copy(quadraticEquation, ostream_iterator<float>{cout, ", "});
    cout << endl;
  }
}
