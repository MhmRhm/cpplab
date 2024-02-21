#include <iostream>

template <typename T> constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

class Type final {
public:
  Type() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type(const Type &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type(Type &&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Type &operator=(const Type &) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  Type &operator=(Type &&) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return *this;
  }
  ~Type() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

namespace {
int LineNumber{};
} // namespace

template <class T> T &&myForward(T &arg) {
  using namespace std;
  cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << endl;
  cout << ++LineNumber << " " << type_name<decltype(arg)>() << endl;
  return static_cast<T &&>(arg);
}

template <class T> void typeIndicator(T &&arg) {
  using namespace std;
  cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << endl;
  cout << ++LineNumber << " " << type_name<decltype(arg)>() << endl;
}

template <class T> void wrapper(T &&arg) {
  using namespace std;
  cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << endl;
  cout << ++LineNumber << " " << type_name<decltype(arg)>() << endl;
  typeIndicator(myForward<T>(arg));
  T t = myForward<T>(arg);
}

int main() {
  using namespace std;

  Type var{};
  wrapper(var);

  cout << endl;
  wrapper(Type{});
}
