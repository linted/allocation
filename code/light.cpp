#include <benchmark/benchmark.h>
#include "light.h"

void  do_malloc_large(benchmark::State& state)
{
  for (auto _ : state)
  {
    malloc_light_large_test();
  }
}

void do_stack_large(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_light_large_test();
  }
}

void  do_calloc_large(benchmark::State& state)
{
  for (auto _ : state)
  {
    calloc_light_large_test();
  }
}

void do_stack_initialized_large(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_initialized_light_large_test();
  }
}

void  do_malloc_small(benchmark::State& state)
{
  for (auto _ : state)
  {
    malloc_light_small_test();
  }
}

void do_stack_small(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_light_small_test();
  }
}

void  do_calloc_small(benchmark::State& state)
{
  for (auto _ : state)
  {
    calloc_light_small_test();
  }
}

void do_stack_initialized_small(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_initialized_light_small_test();
  }
}


// Register the function as a benchmark
BENCHMARK(do_stack_large);
BENCHMARK(do_malloc_large);
BENCHMARK(do_stack_initialized_large);
BENCHMARK(do_calloc_large);
// Register the function as a benchmark
BENCHMARK(do_stack_small);
BENCHMARK(do_malloc_small);
BENCHMARK(do_stack_initialized_small);
BENCHMARK(do_calloc_small);
// Run the benchmark
BENCHMARK_MAIN();