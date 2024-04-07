#pragma once

#include <iostream>
#include <source_location>

template <typename T, template <typename, typename> class... Policies>
class CustomType final : public Policies<T, CustomType<T, Policies...>>... {
  T m_value{};

public:
  const T &getValue() const { return m_value; }
};

template <typename T, typename CustomType> class Processor {
public:
  void process() {
    std::cout << std::source_location::current().function_name() << std::endl;
    CustomType *ct{static_cast<CustomType *>(this)};
  }
};

template <typename T, typename CustomType> class Formatter {
public:
  void format() {
    std::cout << std::source_location::current().function_name() << std::endl;
    CustomType *ct{static_cast<CustomType *>(this)};
  }
};

template <typename T, typename CustomType> class InterruptionManager {
public:
  void interrupt() {
    std::cout << std::source_location::current().function_name() << std::endl;
    CustomType *ct{static_cast<CustomType *>(this)};
  }
};

template <typename T, typename CustomType> class Serializer {
public:
  friend std::ostream &operator<<(std::ostream &out, const CustomType &ct) {
    std::cout << std::source_location::current().function_name() << std::endl;
    out << ct.getValue();
    return out;
  }
};
