#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

// a wrapper around std::vector
template <typename T> class NaiveVector final : public std::vector<T> {
public:
  using std::vector<T>::vector;

  NaiveVector() : std::vector<T>{} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  NaiveVector(const NaiveVector &src) : std::vector<T>{src} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  NaiveVector &operator=(const NaiveVector &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<T>::operator=(src);
    return *this;
  }
  NaiveVector(NaiveVector &&src) noexcept : std::vector<T>{std::move(src)} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  NaiveVector &operator=(NaiveVector &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::vector<T>::operator=(std::move(src));
    return *this;
  }

  friend NaiveVector operator+(const NaiveVector &lhs, const NaiveVector &rhs) {
    NaiveVector data{};
    std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(),
                   std::back_inserter(data), std::plus<>{});
    return data;
  }
};

template class NaiveVector<int>;
template class NaiveVector<double>;

template <typename T, typename ContainerType = std::vector<T>>
class MatureVector final {
public:
  MatureVector(ContainerType &&container) noexcept
      : m_container{std::move(container)} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  MatureVector() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  MatureVector(const MatureVector &src) : m_container{src.container} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  MatureVector &operator=(const MatureVector &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    m_container = src.m_container;
    return *this;
  }
  MatureVector(MatureVector &&src) noexcept
      : m_container{std::move(src.container)} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  MatureVector &operator=(MatureVector &&src) noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    m_container = std::move(src.m_container);
    return *this;
  }

  template <typename SrcT, typename SrcContainerType>
  MatureVector &operator=(const MatureVector<SrcT, SrcContainerType> &src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    for (size_t i{0}; i < src.size(); i++) {
      m_container[i] = src[i];
    }
    return *this;
  }
  template <typename SrcT, typename SrcContainerType>
  MatureVector &operator=(MatureVector<SrcT, SrcContainerType> &&src) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    for (size_t i{0}; i < src.size(); i++) {
      m_container[i] = std::move(src[i]);
    }
    return *this;
  }

  size_t size() const { return m_container.size(); }

  T &operator[](const size_t index) { return m_container[index]; }
  T operator[](const size_t index) const { return m_container[index]; }

  const ContainerType &data() const { return m_container; }

private:
  ContainerType m_container{};
};

template <typename T, typename LhsContainerType, typename RhsContainerType>
class MatureAdd final {
public:
  MatureAdd(const LhsContainerType &lhs, const RhsContainerType &rhs)
      : m_lhs{lhs}, m_rhs{rhs} {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  T operator[](const size_t index) const { return m_lhs[index] + m_rhs[index]; }
  size_t size() const { return m_lhs.size(); }

private:
  const LhsContainerType &m_lhs;
  const RhsContainerType &m_rhs;
};

template <typename T, typename LhsContainerType, typename RhsContainerType>
MatureVector<T, MatureAdd<T, LhsContainerType, RhsContainerType>>
operator+(const MatureVector<T, LhsContainerType> &lhs,
          const MatureVector<T, RhsContainerType> &rhs) {
  return MatureVector<T, MatureAdd<T, LhsContainerType, RhsContainerType>>{
      MatureAdd<T, LhsContainerType, RhsContainerType>{lhs.data(), rhs.data()}};
}
