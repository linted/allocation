#include <iostream>
#include <benchmark/benchmark.h>
#include <unistd.h>

#include "sporadic.h"


void  do_stack(benchmark::State& state)
{
  // setup
  int sock = sporadic_setup();
  if (-1 == sock)
  {
    return;
  }
  
  for (auto _ : state)
  {
    // code that is timed
    stack_sporadic_test(sock);
  }

  // cleanup
  close(sock);
}

void  do_malloc(benchmark::State& state)
{
  // setup
  int sock = sporadic_setup();
  if (-1 == sock)
  {
    return;
  }
  
  for (auto _ : state)
  {
    // code that is timed
    malloc_sporadic_test(sock);
  }

  // cleanup
  close(sock);

}

void  do_stack_initialized(benchmark::State& state)
{
  // setup
  int sock = sporadic_setup();
  if (-1 == sock)
  {
    return;
  }
  
  for (auto _ : state)
  {
    // code that is timed
    stack_initalized_sporadic_test(sock);
  }

  // cleanup
  close(sock);
}

void  do_calloc(benchmark::State& state)
{
  // setup
  int sock = sporadic_setup();
  if (-1 == sock)
  {
    return;
  }
  
  for (auto _ : state)
  {
    // code that is timed
    calloc_sporadic_test(sock);
  }

  // cleanup
  close(sock);

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