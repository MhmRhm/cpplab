#include <algorithm>
#include <exception>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

struct Record final {
  int id{};
  int partner{};
  int age{};
};

int main() {
  using namespace std;

  ofstream file{};

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

  istringstream str{"Mohammad Rahimi\nWolf Blitzer\nErin Burnett"};
  copy(istream_iterator<string>{str}, istream_iterator<string>{},
       back_inserter(party));
  copy(party.begin(), party.end(), ostream_iterator<string>{cout, "\n"});

  cin.ignore();

  auto records = {Record{1, 0, 10}, Record{2, 0, 20}, Record{3, 0, 30},
                  Record{4, 3, 30}, Record{5, 2, 20}, Record{6, 1, 10}};
  // 161025203430431052206130
  fstream document{};
  document.exceptions(ios::eofbit | ios::badbit | ios::failbit);

  try {
    document.open("./records", ios::binary | ios::trunc | ios::in | ios::out);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  for (auto &&record : records) {
    document.write(reinterpret_cast<const char *>(&record), sizeof(Record));
    document.flush();
    if (record.partner) {
      document.seekp(sizeof(Record) * (record.partner - 1), ios::beg);
      document.seekp(offsetof(Record, partner), ios::cur);
      document.write(reinterpret_cast<const char *>(&record.id),
                     sizeof(Record::id));
      document.flush();
      document.seekp(0, ios::end);
    }
  }

  auto size{document.tellp()};
  document.seekg(0, ios::beg);

  while (document.tellg() < size) {
    Record record;
    document.read(reinterpret_cast<char *>(&record), sizeof(Record));
    cout << format("id: {}, partner: {}, age: {}", record.id, record.partner,
                   record.age)
         << endl;
  }
}
