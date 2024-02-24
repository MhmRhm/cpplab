#include <algorithm>
#include <exception>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

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

  string name{};
  vector<string> party{};

  cout << "Enter participants name: " << endl;
  while (cin) {
    int code{cin.get()};
    if (code == char_traits<char>::eof()) {
      break;
    }
    if (iswspace(code)) {
      party.push_back(name);
      name = {};
      continue;
    }
    if (!isalpha(code)) {
      party.push_back(name);
      name = {};
      break;
    }
    name.push_back(static_cast<char>(code));
  }
  for (auto &&name : party) {
    cout << format("Welcome {}!", name) << endl;
  }
  name = {};
  party.clear();

  cin.clear();
  cin.ignore();

  cout << "Enter participants name: " << endl;
  while (getline(cin, name, '\n')) {
    if (!name.length()) {
      cout << '[' << name << ']' << "Here 1" << endl;
      break;
    }
    name.erase(name.find_last_not_of(' ') + 1);
    name.erase(0, name.find_first_not_of(' '));
    party.push_back(name);
  }
  for (auto &&name : party) {
    cout << format("Welcome {}!", name) << endl;
  }

  party.clear();

  cout << "Enter participants name: " << endl;
  copy(istream_iterator<string>{cin}, istream_iterator<string>{},
       back_inserter(party));
  copy(party.begin(), party.end(), ostream_iterator<string>{cout, "\n"});
}
