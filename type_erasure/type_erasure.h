#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <source_location>

template <typename T> struct Plotable final {
  class PlotterBase {
  public:
    virtual ~PlotterBase() = default;
    virtual void plot(const T &plotable) const = 0;
  };

  template <typename P> class Plotter final : public PlotterBase {
    P m_p{};

  public:
    Plotter(P &&p) : m_p{std::forward<P>(p)} {}
    virtual void plot(const T &plotable) const override { m_p(plotable); }
  };

  T m_t;
  std::array<uint8_t, 16> m_local_buffer{};
  const PlotterBase *m_p{};

  bool is_lb_optimized() const {
    return static_cast<const void *>(m_p) ==
           static_cast<const void *>(&m_local_buffer);
  }
  void destroy_plotter() {
    using namespace std;
    if (is_lb_optimized()) {
      cout << std::source_location::current().function_name()
           << " was optimized." << endl;
      std::destroy_at(m_p);
    } else {
      delete m_p;
    }
  }

public:
  template <typename P>
  Plotable(T &&t, P &&p)
      : m_t{std::forward<T>(t)},
        m_p{sizeof(P) <= sizeof(m_local_buffer)
                ? new(&m_local_buffer) Plotter<P>{std::forward<P>(p)}
                : new Plotter<P>{std::forward<P>(p)}} {}

  Plotable &operator=(Plotable &&src) {
    if (this == &src) {
      return *this;
    }

    m_t = std::move(src.m_t);

    destroy_plotter();
    if (src.is_lb_optimized()) {
      m_local_buffer = src.m_local_buffer;
      m_p = reinterpret_cast<const PlotterBase *>(&m_local_buffer);
    } else {
      m_p = src.m_p;
    }
    src.m_p = nullptr;

    return *this;
  }

  ~Plotable() { destroy_plotter(); }
  void plot() const { m_p->plot(m_t); }
};

template class Plotable<int>;
