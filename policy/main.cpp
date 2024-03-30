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
  cout << endl << endl;

  Stream<NormalTrafficProcessor<uint8_t>, FlushOnInterruption> s2{};
  s2.process(&data[0]);
  s2.interrupt(&data[0]);
  cout << endl << endl;

  decltype(s2)::ChangeProcessorUnit<uint16_t>::ChangeFormatter<
      AdvancedFormatter>
      s3{};
  s3.process(reinterpret_cast<uint16_t *>(&data[0]));
  s3.interrupt(reinterpret_cast<uint16_t *>(&data[0]));
}
