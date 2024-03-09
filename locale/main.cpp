#include <algorithm>
#include <format>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <vector>

#include "comma_separator.h"

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

  cout << format("Default Locale: {}, System Locale: {}", locale{}.name(),
                 locale{""}.name())
       << endl;

  locale::global(locale{"fa_IR.UTF-8"});

  cout << format("Default Locale: {}, System Locale: {}, Locale on cout: {}",
                 locale{}.name(), locale{""}.name(), cout.getloc().name())
       << endl;

  cout << '[' << setfill('_') << setw(5) << 42 << ']' << endl
       << hex << noshowbase << 1024 << endl
       << showbase << 1024 << dec << endl;

  auto oldPercision{cout.precision(10)};
  cout << 1.0 / 3.0 << endl;
  cout << setprecision(oldPercision) << 1.0 / 3.0 << endl;

  // cat /etc/locale.gen
  // sudo locale-gen ms_MY.UTF-8
  cout.imbue(locale{"ms_MY.UTF-8"});
  cout << "Paid " << put_money(12345) << " on " << put_time(t, "%c") << endl;
  cout.imbue(locale{"uk_UA.UTF-8"});
  cout << "Paid " << put_money(12345) << " on " << put_time(t, "%c") << endl;
  cout.imbue(locale{"ru_RU.UTF-8"});
  cout << "Paid " << put_money(12345) << " on " << put_time(t, "%c") << endl;
  cout.imbue(locale{"en_US.UTF-8"});
  cout << "Paid " << put_money(12345) << " on " << put_time(t, "%c") << endl;

  cout.imbue(locale{"ms_MY.UTF-8"});
  cout << use_facet<moneypunct<char>>(cout.getloc()).curr_symbol() << endl;
  cout << use_facet<moneypunct<char>>(cout.getloc()).thousands_sep() << endl;
  cout << use_facet<moneypunct<char>>(cout.getloc()).decimal_point() << endl;
  cout << use_facet<moneypunct<char>>(cout.getloc()).frac_digits() << endl;

  // cat /usr/share/locale/de/LC_MESSAGES/debconf.mo
  locale deLocale{"de_DE.UTF-8"};
  cout.imbue(deLocale);
  auto &facet = use_facet<messages<char>>(deLocale);
  auto catalog = facet.open("debconf", deLocale);
  cout << facet.get(catalog, 0, 0, "Really quit configuration?") << endl
       << facet.get(catalog, 0, 0, "yes") << endl
       << facet.get(catalog, 0, 0, "no") << endl;
  facet.close(catalog);

  vector<wstring> wparty{};
  wcin.imbue(locale{wcin.getloc(), new CommaSeparator{}});

  cout << "Enter participants name: " << endl;
  copy(iwstream_iterator<wstring>{wcin}, iwstream_iterator<wstring>{},
       back_inserter(wparty));
  cout << endl << "Our guests are:" << endl;
  copy(begin(wparty), end(wparty), owstream_iterator<wstring>{wcout, L"\n"});
}
