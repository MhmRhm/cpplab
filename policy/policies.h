#pragma once

#include <cstdint>
#include <iostream>
#include <type_traits>

class NoInterruption {
public:
  virtual ~NoInterruption() = default;
  static constexpr bool CanHandleInterrupt{false};
};
class PassThroughProcessor {
public:
  virtual ~PassThroughProcessor() = default;
  bool process(uint8_t *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }
};
template <typename Stream> class BasicFormatter final {
  friend Stream;
  void format(const Stream &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

template <typename Processor = PassThroughProcessor,
          typename InterruptManager = NoInterruption,
          template <typename T> class Formatter = BasicFormatter>
class Stream final : private Processor, private InterruptManager {
  friend Formatter<Stream>;
  Formatter<Stream> m_formatter{};

public:
  using Processor::process;
  template <typename T = uint8_t>
    requires InterruptManager::CanHandleInterrupt
  void interrupt(T *data) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    InterruptManager::interrupt(data);
    m_formatter.format(*this);
  }
};

class FlushOnInterruption {
public:
  virtual ~FlushOnInterruption() = default;
  static constexpr bool CanHandleInterrupt{true};
  template <typename T = uint8_t> bool interrupt(T *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }
};
class NormalTrafficProcessor {
public:
  virtual ~NormalTrafficProcessor() = default;
  bool process(uint8_t *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }
};
