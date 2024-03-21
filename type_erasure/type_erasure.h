#pragma once

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
  const PlotterBase *m_p{};

public:
  template <typename P>
  Plotable(T &&t, P &&p)
      : m_t{std::forward<T>(t)}, m_p{new Plotter<P>{std::forward<P>(p)}} {}

  Plotable &operator=(Plotable &&src) {
    if (this == &src) {
      return *this;
    }

    m_t = std::move(src.m_t);
    delete m_p;
    m_p = src.m_p;
    src.m_p = nullptr;

    return *this;
  }

  ~Plotable() { delete m_p; }
  void plot() const { m_p->plot(m_t); }
};

template class Plotable<int>;
