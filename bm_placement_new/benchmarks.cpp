#include <array>
#include <cstdint>

#include "benchmark/benchmark.h"

struct Type {
  uint64_t var1{};
  uint64_t var2{};
  uint64_t var3{};
};

void BM_New(benchmark::State &state) {
  using namespace std;

  // initialize

  // benchmark
  for (auto _ : state) {
    auto type{new Type{.var1 = 1, .var2 = 2, .var3 = 3}};
    benchmark::DoNotOptimize(type);
  }

  // measure
  state.counters["Constructions"] = benchmark::Counter(
      static_cast<int64_t>(state.iterations()), benchmark::Counter::kIsRate);
}
BENCHMARK(BM_New);

void BM_PlacementNew(benchmark::State &state) {
  using namespace std;

  // initialize
  array<uint8_t, sizeof(Type)> buffer{};

  // benchmark
  for (auto _ : state) {
    auto type{new (&buffer) Type{.var1 = 1, .var2 = 2, .var3 = 3}};
    benchmark::DoNotOptimize(type);
  }

  // measure
  state.counters["Constructions"] = benchmark::Counter(
      static_cast<int64_t>(state.iterations()), benchmark::Counter::kIsRate);
}
BENCHMARK(BM_PlacementNew);
