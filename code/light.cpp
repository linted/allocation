#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <benchmark/benchmark.h>


void  do_malloc(benchmark::State& state)
{

  for (auto _ : state)
  {
    uint32_t volatile * t = (uint32_t *)calloc(65445, sizeof(uint32_t));
    if (t[100] == 51)
    {
      return;
    }
    t[100] = 51;
    free((void*)t);
  }

}

void do_stack(benchmark::State& state)
{
  for (auto _ : state)
  {
    uint32_t volatile t[65445] = {0};
    if (t[100] == 51)
    {
      return;
    }
    t[100] = 51;
  }
}

// Register the function as a benchmark
BENCHMARK(do_stack);
// Register the function as a benchmark
BENCHMARK(do_malloc);
// Run the benchmark
BENCHMARK_MAIN();