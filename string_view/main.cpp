#include <algorithm>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

// Cpp 17
bool isUSBFile(std::string_view sv) {
  // Cpp 20
  return sv.ends_with(".usb") || sv.ends_with(".usbraw");
  // never return string_view
}

int main() {
  using namespace std;

  string str{"file.usb"};
  char cstr[]{"file.usbraw"};
  string_view svstr{"file.rec"};

  cout << isUSBFile(str) << endl
       << isUSBFile(cstr) << endl
       << isUSBFile(svstr) << endl
       << isUSBFile("file.dat") << endl
       << isUSBFile(string_view{cstr, 8}) << endl;
}
