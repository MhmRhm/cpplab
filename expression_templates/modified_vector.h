#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

template <typename T> class NaiveVector final {
public:
  NaiveVector(std::vector<T> &&src) : m_data{std::move(src)} {}

  const T &operator[](size_t index) const { return m_data[index]; }
  T &operator[](size_t index) {
    return const_cast<T &>(const_cast<const NaiveVector &>(*this)[index]);
  }

  size_t size() { return m_data.size(); }

  friend NaiveVector operator+(const NaiveVector &lhs, const NaiveVector &rhs) {
    std::vector<T> data{};
    transform(cbegin(lhs), cend(lhs), cbegin(rhs), back_inserter(data),
              plus<>{});
    return NaiveVector{std::move(data)};
  }

private:
  std::vector<T> m_data{};
};

template class NaiveVector<int>;
template class NaiveVector<double>;
