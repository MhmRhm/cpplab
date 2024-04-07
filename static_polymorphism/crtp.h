#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <source_location>

template <typename T> struct CapturedData {
  uint64_t type{};
  uint64_t time{};

  const uint8_t *getPayload(size_t &size_bytes) const {
    return static_cast<const T *>(this)->getPayloadImp(size_bytes);
  }

private:
  const uint8_t *getPayloadImpl(size_t &size_bytes) const {
    size_bytes = 0;
    return nullptr;
  }

  // To make pure virtual
  friend T;
  CapturedData() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
  ~CapturedData() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
};

struct TS : CapturedData<TS> {
  std::array<uint64_t, 4> payload{};
  uint64_t header{};

  TS() : CapturedData{} {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
  ~TS() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }

  // To make private
private:
  friend CapturedData;
  const uint8_t *getPayloadImp(size_t &size_bytes) const {
    size_bytes = sizeof(payload);
    return reinterpret_cast<const uint8_t *>(&payload);
  }
};

struct TLP : CapturedData<TLP> {
  std::array<uint64_t, 2> payload{};

  TLP() : CapturedData{} {
    std::cout << std::source_location::current().function_name() << std::endl;
  }
  ~TLP() {
    std::cout << std::source_location::current().function_name() << std::endl;
  }

  // To make private
private:
  friend CapturedData;
  const uint8_t *getPayloadImp(size_t &size_bytes) const {
    size_bytes = sizeof(payload);
    return reinterpret_cast<const uint8_t *>(&payload);
  }
};

template <typename T> void printPayload(const CapturedData<T> &capture) {
  using namespace std;

  size_t size_bytes{};
  const uint8_t *payload{capture.getPayload(size_bytes)};

  span data{payload, size_bytes};
  copy(cbegin(data), cend(data), ostream_iterator<int>{cout, ", "});
  cout << endl;
}

template <typename T> void trash(CapturedData<T> *capture) {
  delete static_cast<T *>(capture);
}
