#include <benchmark/benchmark.h>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include "sorts.h"

#define SIZE 2 << 20

static void BM_std_sort(benchmark::State &state) {

  int end = std::numeric_limits<int>::max();
  int begin = std::numeric_limits<int>::min();

  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) {
      v.push_back((std::rand() % end) + begin);
    }

    std::sort(v.begin(), v.end());
  }
}
BENCHMARK(BM_std_sort)->Arg(SIZE)->Unit(benchmark::kMillisecond);

static void BM_quicksort(benchmark::State &state) {

  int end = std::numeric_limits<int>::max();
  int begin = std::numeric_limits<int>::min();

  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) {
      v.push_back((std::rand() % end) + begin);
    }

    quicksort(v);
  }
}
BENCHMARK(BM_quicksort)->Arg(SIZE)->Unit(benchmark::kMillisecond);

static void BM_quickBubble_sort(benchmark::State &state) {

  int end = std::numeric_limits<int>::max();
  int begin = std::numeric_limits<int>::min();

  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) {
      v.push_back((std::rand() % end) + begin);
    }

    quickBubble_sort(v);
  }
}
BENCHMARK(BM_quickBubble_sort)->Arg(SIZE)->Unit(benchmark::kMillisecond);

static void BM_quicksort_median(benchmark::State &state) {

  int end = std::numeric_limits<int>::max();
  int begin = std::numeric_limits<int>::min();

  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) {
      v.push_back((std::rand() % end) + begin);
    }
    quicksort_median(v);
  }
}
BENCHMARK(BM_quicksort_median)->Arg(SIZE)->Unit(benchmark::kMillisecond);


BENCHMARK_MAIN();
