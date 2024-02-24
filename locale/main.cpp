#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <vector>

template <typename T>
using iwstream_iterator =
    std::istream_iterator<T, wchar_t, std::char_traits<wchar_t>>;

template <typename T>
using owstream_iterator =
    std::ostream_iterator<T, wchar_t, std::char_traits<wchar_t>>;

int main() {
  using namespace std;
  time_t t_t{time(nullptr)};
  tm *t{localtime(&t_t)};

  cout << format("Default Locale: {}, System Locale;{}", locale{}.name(),
                 locale{""}.name())
       << endl;

  locale::global(locale{"en_US.UTF-8"});

  cout << format("Default Locale: {}, System Locale: {}, Locale on cout: {}",
                 locale{}.name(), locale{""}.name(), cout.getloc().name())
       << endl;

  // sudo locale-gen ms_MY.UTF-8
  cout.imbue(locale{"ms_MY.UTF-8"});
  cout << '[' << setfill('_') << setw(5) << 42 << ']' << endl
       << showbase << put_money(1024) << noshowbase << endl
       << put_time(t, "%c") << endl
       << use_facet<moneypunct<char>>(cout.getloc()).curr_symbol() << endl;

  auto oldPercision{cout.precision(10)};
  cout << 1.0 / 3.0 << endl;
  cout << setprecision(oldPercision) << 1.0 / 3.0 << endl;

  struct CommaSeperator : ctype<wchar_t> {
    bool do_is(mask m, char_type c) const {
      if ((m & space) && c == L' ') {
        return false;
      }
      if ((m & space) && c == L',') {
        return true;
      }
      return ctype::do_is(m, c);
    }
  };

  wstring wname{};
  vector<wstring> wparty{};

  wcin.imbue(locale{wcin.getloc(), new CommaSeperator{}});

  cout << "Enter participants name: " << endl;
  copy(iwstream_iterator<wstring>{wcin}, iwstream_iterator<wstring>{},
       back_inserter(wparty));
  copy(wparty.begin(), wparty.end(), owstream_iterator<wstring>{wcout, L"\n"});
}
