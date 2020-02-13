#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <benchmark/benchmark.h>



void do_malloc(void)
{
  uint32_t volatile * t = (uint32_t *)calloc(65445, sizeof(uint32_t));
  // if (t[100] == 51)
  //   exit(1);
  t[100] = 51;
  free((void*)t);
}

void  do_test(benchmark::State& state)
{

  for (auto _ : state)
  {
    do_malloc();
  }

}


// Register the function as a benchmark
BENCHMARK(do_test);
// Run the benchmark
BENCHMARK_MAIN();