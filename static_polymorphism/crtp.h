#pragma once

#include <array>
#include <cstdint>

template <typename T> struct CapturedData {
  uint64_t type{};
  uint64_t time{};

  const uint8_t *getPayload(size_t &size_bytes) const {
    return static_cast<const T *>(this)->getPayloadImp(size_bytes);
  }

  const uint8_t *getPayloadImpl(size_t &size_bytes) const {
    size_bytes = 0;
    return nullptr;
  }
};

struct TS : CapturedData<TS> {
  std::array<uint64_t, 4> payload{};
  uint64_t header{};

  const uint8_t *getPayloadImp(size_t &size_bytes) const {
    size_bytes = sizeof(payload);
    return reinterpret_cast<const uint8_t *>(&payload);
  }
};

struct TLP : CapturedData<TLP> {
  std::array<uint64_t, 2> payload{};

  const uint8_t *getPayloadImp(size_t &size_bytes) const {
    size_bytes = sizeof(payload);
    return reinterpret_cast<const uint8_t *>(&payload);
  }
};
