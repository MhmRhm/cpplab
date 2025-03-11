#include <format>
#include <functional>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <unordered_map>

int main() {
  using namespace std;

  locale::global(locale{""});

  random_device dev{};
  cout << format("device.entropy = {}, device.max = {:L}, device.min = {}, "
                 "value = {}",
                 dev.entropy(), dev.max(), dev.min(), dev())
       << endl;

  mt19937_64 eng{static_cast<mt19937_64::result_type>(
      dev.entropy() ? dev() : time(nullptr))};
  cout << format("sizeof(engine) = {}, engine.max = {:L}, engine.min = {}, "
                 "value = {:L}",
                 sizeof(eng), eng.max(), eng.min(), eng())
       << endl;

  poisson_distribution<int> dist{3};
  cout << format("likely we have a 3 in [{}, {}, {}, {}]", dist(eng), dist(eng),
                 dist(eng), dist(eng))
       << endl;

  auto generate{bind(dist, eng)};
  unordered_map<int, int> samples{};
  for (size_t i = 0; i < 10'000; i++) {
    ++samples[generate()];
  }
  for (const auto &[outcome, occurance] : samples) {
    cout << format("{:<3}: {}", outcome, string(occurance / 100, '*')) << endl;
  }
}
