#include <iostream>
#include <string_view>

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
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
  return static_cast<T &&>(arg);
}

template <class T> void typeIndicator(T &&arg) {
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
}

template <class T> void wrapper(T &&arg) {
  std::cout << ++LineNumber << " " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ++LineNumber << " " << type_name<decltype(arg)>() << std::endl;
  typeIndicator(myForward<T>(arg));
  T temp = myForward<T>(arg);
}

int main() {
  Type var{};
  wrapper(var);

  std::cout << std::endl;
  wrapper(std::move(var));
}
