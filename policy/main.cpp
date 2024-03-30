#include <array>
#include <cstdint>
#include <iostream>

#include "policies.h"

int main() {
  using namespace std;

  array<uint8_t, 4> data{1, 2, 3, 4};

  Stream s1{};
  s1.process(&data[0]);
  // s1.interrupt(&data[0]);

  Stream<NormalTrafficProcessor, FlushOnInterruption> s2{};
  s2.process(&data[0]);
  s2.interrupt(&data[0]);
}
