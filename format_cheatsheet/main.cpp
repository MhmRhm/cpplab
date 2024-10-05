#include <format>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
  using namespace std;
  cout << endl
       << "[[fill]align][sign][#][0][width][.precision][type]" << endl
       << endl;

  cout << format("If num = {0} then {{}} shows |{0}|", 10) << endl << endl;

  cout << format("For width, if num = {0} then {{:5}} shows |{0:5}|", 10)
       << endl
       << endl;

  cout << format("For align, if num = {0} then {{:<5}} shows |{0:<5}|", 10)
       << endl;
  cout << format("For align, if num = {0} then {{:^5}} shows |{0:^5}|", 10)
       << endl;
  cout << format("For align, if num = {0} then {{:>5}} shows |{0:>5}|", 10)
       << endl
       << endl;

  cout << format("For fill, if num = {0} then {{:*^5}} shows |{0:*^5}|", 10)
       << endl
       << endl;

  cout << format("For sign, if num = {0} then {{:< 5}} shows  |{0:< 5}|", 10)
       << endl;
  cout << format("For sign, if num = {0} then {{:< 5}} shows |{0:< 5}|", -10)
       << endl;
  cout << format("For sign, if num = {0} then {{:<+5}} shows  |{0:<+5}|", 10)
       << endl;
  cout << format("For sign, if num = {0} then {{:<+5}} shows |{0:<+5}|", -10)
       << endl;
  cout << format("For sign, if num = {0} then {{:<-5}} shows  |{0:<-5}|", 10)
       << endl;
  cout << format("For sign, if num = {0} then {{:<-5}} shows |{0:<-5}|", -10)
       << endl
       << endl;

  cout << format("For 0, if num = {0} then {{:05}} shows  |{0:05}|", 10)
       << endl;
  cout << format("For 0, if num = {0} then {{:^05}} shows |{0:^05}|", 10)
       << endl
       << endl;

  cout << format("For type, if num = {0} then {{:<10d}} shows   |{0:<10d}|",
                 101)
       << endl;
  cout << format("For type, if num = {0} then {{:_>10x}} shows  |{0:_>10x}|",
                 123)
       << endl;
  cout << format("For type, if num = {0} then {{:_>10X}} shows  |{0:_>10X}|",
                 123)
       << endl
       << endl;

  cout << format("For #, if num = {0} then {{:_>#10X}} shows    |{0:_>#10X}|",
                 123)
       << endl;
  cout << format("For #, if num = {0} then {{:_>#10B}} shows    |{0:_>#10B}|",
                 123)
       << endl;
  cout << format("For #, if num = {0} then {{:_>#10o}} shows    |{0:_>#10o}|",
                 123)
       << endl
       << endl;

  cout << format("For type, if num = {0} then {{:g}} shows     |{0:g}|", 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:e}} shows     |{0:e}|", 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:.2e}} shows   |{0:.2e}|", 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:f}} shows     |{0:f}|", 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:.2f}} shows   |{0:.2f}|", 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:>8.2f}} shows |{0:>8.2f}|",
                 1.1)
       << endl;
  cout << format("For type, if num = {0} then {{:a}} shows     |{0:a}|", 1.1)
       << endl
       << endl;

  cout << format("For #, if num = {0:.1f} then {{:g}} shows  |{0:g}|", 1.0)
       << endl;
  cout << format("For #, if num = {0:.1f} then {{:#g}} shows |{0:#g}|", 1.0)
       << endl
       << endl;

  string text{"Hello format!"};
  cout << format("For type, if char is {0} then {{:c}} shows |{0:c}|", 'Z')
       << endl;
  cout << format("For type, if bool is {0} then {{:s}} shows |{0:s}|", true)
       << endl;
  cout << format("For type, if pointer is {0} then {{:p}} shows |{0:p}|",
                 static_cast<void *>(&text))
       << endl;
  cout << format("For type, if string is '{0}' and width is {1}\n"
                 "\tthen {{0:^{{1}}s}} shows |{0:^{1}s}|",
                 text, text.size() + 10)
       << endl
       << endl;
}
