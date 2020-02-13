#include <benchmark/benchmark.h>
#include "light.h"

void  do_malloc(benchmark::State& state)
{
  for (auto _ : state)
  {
    malloc_light_test();
  }
}

void do_stack(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_light_test();
  }
}

void  do_calloc(benchmark::State& state)
{
  for (auto _ : state)
  {
    calloc_light_test();
  }
}

void do_stack_initialized(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_initialized_light_test();
  }
}

// Register the function as a benchmark
BENCHMARK(do_stack);
// Register the function as a benchmark
BENCHMARK(do_malloc);
// Register the function as a benchmark
BENCHMARK(do_stack_initialized);
// Register the function as a benchmark
BENCHMARK(do_calloc);
// Run the benchmark
BENCHMARK_MAIN();