#include <algorithm>
#include <exception>
#include <format>
#include <fstream>
#include <iostream>
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

  string name;
  vector<string> party{};
  while (getline(cin, name, '\n')) {
    if (!name.length())
      break;
    name.erase(name.find_last_not_of(' ') + 1);
    name.erase(0, name.find_first_not_of(' '));
    party.push_back(name);
  }
  for (auto &&name : party) {
    cout << format("Welcome {}!", name) << endl;
  }
}
