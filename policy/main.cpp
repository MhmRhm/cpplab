#include <array>
#include <cstdint>
#include <iostream>

#include "improved_policies.h"
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

  CustomType<int, Processor, Formatter, InterruptionManager> ct3{};
  ct3.process();
  ct3.format();
  ct3.interrupt();

  CustomType<int, InterruptionManager, Processor> ct2{};
  ct2.interrupt();
  ct2.process();
  // ct2.format();

  CustomType<int, Formatter> ct1{};
  ct1.format();
  // ct1.process();
  // ct1.interrupt();

  CustomType<int, Serializer> ct0{};
  cout << ct0 << endl;
}
