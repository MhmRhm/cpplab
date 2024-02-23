#include <exception>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>

int main() {
  using namespace std;

  std::ofstream file{};

  // for files use neutral locale, for UI use system locale
  file.imbue(locale{"C"});
  // if constructor was used to open the file this line would have thrown
  file.exceptions(ios::eofbit | ios::badbit | ios::failbit);

  try {
    file.open("/file.txt", fstream::out | fstream::app);
    file << "content" << endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

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
}
