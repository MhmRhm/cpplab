#pragma once

#include <cstdint>
#include <iostream>
#include <type_traits>

class NoInterruption {
public:
  virtual ~NoInterruption() = default;
  static constexpr bool CanHandleInterrupt{false};
};

template <typename Unit> class PassThroughProcessor {
public:
  virtual ~PassThroughProcessor() = default;
  bool process(Unit *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }

  template <typename NewUnit> using ChangeUnit = PassThroughProcessor<NewUnit>;
};

template <typename Stream> class BasicFormatter final {
  friend Stream;
  void format(const Stream &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

template <typename Processor = PassThroughProcessor<uint8_t>,
          typename InterruptManager = NoInterruption,
          template <typename T> class Formatter = BasicFormatter>
class Stream final : private Processor, private InterruptManager {
  friend Formatter<Stream>;
  Formatter<Stream> m_formatter{};

public:
  using Processor::process;

  template <typename T>
    requires InterruptManager::CanHandleInterrupt
  void interrupt(T *data) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    InterruptManager::interrupt(data);
    m_formatter.format(*this);
  }

  template <typename NewProcessorUnit>
  using ChangeProcessorUnit =
      Stream<typename Processor::template ChangeUnit<NewProcessorUnit>,
             InterruptManager, Formatter>;

  template <template <typename NewStream> class NewFormatter>
  using ChangeFormatter = Stream<Processor, InterruptManager, NewFormatter>;
};

class FlushOnInterruption {
public:
  virtual ~FlushOnInterruption() = default;
  static constexpr bool CanHandleInterrupt{true};
  template <typename T> bool interrupt(T *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }
};

template <typename Unit> class NormalTrafficProcessor {
public:
  virtual ~NormalTrafficProcessor() = default;
  bool process(Unit *data) const {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }

  template <typename NewUnit>
  using ChangeUnit = NormalTrafficProcessor<NewUnit>;
};

template <typename Stream> class AdvancedFormatter final {
  friend Stream;
  void format(const Stream &) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};
