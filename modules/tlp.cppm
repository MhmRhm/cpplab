module;
#include <cstdint>

export module tlp;

export struct TLPHeader {
  uint32_t HEC : 8;
  uint32_t Length : 8;
  uint32_t HopID : 7;
  uint32_t Rsvd : 4;
  uint32_t SuppID : 1;
  uint32_t PDF : 4;

  bool getPaddingSize();
};

bool TLPHeader::getPaddingSize() {
  auto extra{Length & 0b11};
  if (extra) {
    extra = 4 - extra;
  }
  return Length + extra;
}