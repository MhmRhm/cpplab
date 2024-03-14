#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

/*
Any characters matches itself except ^ $ \ . * + ? ( ) [ ] { } |
You can scape these with \ for example \$
^ and $ are called anchors they match the beginning and ending of a string
. matches anything but new line character
| used for alternation for example a|b
* matches zero or more + matches one or more ? matches zero or one repetitions
{3,} matches at least three repetitions and they bind to one element to the left
^ means anything but
| has lowest precedence
\d = [[:digit:]], \D = [^[:digit:]]
\s = [[:space:]], \S = [^[:space:]]
\w = [_[:alnum:]], \W = [^_[:alnum:]]
\b = word boundary first character that is [a-zA-Z0-9_] while preceding is not
     or last character that is [a-zA-Z0-9_] while next one is not
\1 or \2 to match with first capture group or second one
*/
int main() {
  using namespace std;

  string text{R"(test)"};
  string pattern{R"(^test$)"};

  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // true
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern},
                             regex_constants::match_default |
                                 regex_constants::match_not_bol |
                                 regex_constants::match_not_eol))
       << endl; // false
  pattern = R"(....)";
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // true

  pattern = R"(te[x|s]t)";
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // true

  pattern = R"(std[:_[:w:]]*)";
  text = R"(std::chrono::duration_cast<>)";
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // false

  pattern = R"(\bstd\b.*)";
  text = R"(std::)";
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // true

  pattern = R"**((.{0,16})\(.*\)\1)**";
  text = R"_:(%%(Hello)%_%)_:";
  cout << format(R"([{}] matches [{}]: {})", pattern, text,
                 regex_match(text, regex{pattern}))
       << endl; // false

  pattern = R"((\w*)_(\w*))";
  text = R"(variable_name)";
  if (smatch matches{}; regex_match(text, matches, regex{pattern})) {
    for (auto &&match : matches) {
      cout << match.str() << endl;
    }
  }

  pattern = R"((\d{1,3}).(\d{1,3}).(\d{1,3}).(\d{1,3}))";
  regex regx1{pattern};
  cout << "Enter valid IP: " << endl;
  // try abc1.1.1.444.0
  while (getline(cin, text) && text != "finish") {
    for (sregex_token_iterator token{cbegin(text), cend(text), regx1, {4}};
         token != sregex_token_iterator{}; advance(token, 1)) {
      cout << format("Your Sub-Domain Address is {}", token->str()) << endl;
    }
  }

  pattern = R"(@(.*)\.com)";
  regex regx2{pattern};
  text = R"(logged-in user is name@domain.com)";
  string report{" from $1"};
  cout << regex_replace(text, regx2, report) << endl;

  struct csv_whitespace : std::ctype<char> {
    static const mask *make_table() {
      static std::vector<mask> v(classic_table(), classic_table() + table_size);
      v[','] |= space;
      v[' '] &= ~space;
      return &v[0];
    }
    csv_whitespace(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
  };

  locale::global(locale{locale{}, new csv_whitespace{}});
  pattern = R"((\S+))";
  regex regx3{pattern};

  string guests{"Christiane Amanpour,,,Jim Acosta,Kate Bolduan"};

  cout << endl << "Our guests are:" << endl;
  for (auto it{sregex_iterator{cbegin(guests), cend(guests), regx3}};
       it != sregex_iterator{}; ++it) {
    cout << it->str() << endl;
  }
}
