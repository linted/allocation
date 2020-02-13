#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <benchmark/benchmark.h>


void do_stack(void)
{
  uint32_t volatile t[65445] = {0};
  t[100] = 51;
}

void do_test(benchmark::State& state)
{

  for (auto _ : state)
  {
    do_stack();
  }

}

// Register the function as a benchmark
BENCHMARK(do_test);
// Run the benchmark
BENCHMARK_MAIN();