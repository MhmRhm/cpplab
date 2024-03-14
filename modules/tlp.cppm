module;
// Global Module Fragment
#include <cstdint>

export module tlp;

using namespace std;

// Export Block
export {
  namespace USB4 {
  class PRBS final {};
  class PRTS final {};
  } // namespace USB4
}

export struct TLPHeader final {
  uint32_t HEC : 8;
  uint32_t Length : 8;
  uint32_t HopID : 7;
  uint32_t Rsvd : 4;
  uint32_t SuppID : 1;
  uint32_t PDF : 4;

  inline bool getPaddingSize() {
    auto extra{Length & 0b11};
    if (extra) {
      extra = 4 - extra;
    }
    return extra;
  }

  bool getPaddedSize();
};

bool TLPHeader::getPaddedSize() {
  auto extra{Length & 0b11};
  if (extra) {
    extra = 4 - extra;
  }
  return Length + extra;
}

struct CSLink final {
  uint32_t DW0{};
};

export struct ConfigurationSpace final {
  CSLink linkCS{};
};
