#include <benchmark/benchmark.h>
#include "light.h"

#define RECURSIVE_COUNT 10

// LARGE tests *********************************************************************

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

// SMALL tests *********************************************************************

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

// struct tests *********************************************************************

void  do_malloc_struct(benchmark::State& state)
{
  for (auto _ : state)
  {
    malloc_struct_test();
  }
}

void do_stack_struct(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_struct_test();
  }
}

void  do_calloc_struct(benchmark::State& state)
{
  for (auto _ : state)
  {
    calloc_struct_test();
  }
}

void do_stack_initialized_struct(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_initialized_struct_test();
  }
}

// recursive tests *********************************************************************

void  do_malloc_recursive(benchmark::State& state)
{
  for (auto _ : state)
  {
    malloc_recur_test(RECURSIVE_COUNT);
  }
}


void do_stack_recursive(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_recur_test(RECURSIVE_COUNT);
  }
}

void  do_calloc_recursive(benchmark::State& state)
{
  for (auto _ : state)
  {
    calloc_recur_test(RECURSIVE_COUNT);
  }
}

void do_stack_initialized_recursive(benchmark::State& state)
{
  for (auto _ : state)
  {
    stack_initialized_recur_test(RECURSIVE_COUNT);
  }
}

// Register the function as a benchmark
BENCHMARK(do_stack_large);
BENCHMARK(do_malloc_large);
BENCHMARK(do_stack_initialized_large);
BENCHMARK(do_calloc_large);

#ifdef DO_THREADED_TESTS
BENCHMARK(do_stack_large)->Threads(2);
BENCHMARK(do_malloc_large)->Threads(2);
BENCHMARK(do_stack_initialized_large)->Threads(2);
BENCHMARK(do_calloc_large)->Threads(2);
BENCHMARK(do_stack_large)->Threads(4);
BENCHMARK(do_malloc_large)->Threads(4);
BENCHMARK(do_stack_initialized_large)->Threads(4);
BENCHMARK(do_calloc_large)->Threads(4);
BENCHMARK(do_stack_large)->Threads(8);
BENCHMARK(do_malloc_large)->Threads(8);
BENCHMARK(do_stack_initialized_large)->Threads(8);
BENCHMARK(do_calloc_large)->Threads(8);
#endif

// Register the function as a benchmark
BENCHMARK(do_stack_small);
BENCHMARK(do_malloc_small);
BENCHMARK(do_stack_initialized_small);
BENCHMARK(do_calloc_small);

#ifdef DO_THREADED_TESTS
BENCHMARK(do_stack_small)->Threads(2);
BENCHMARK(do_malloc_small)->Threads(2);
BENCHMARK(do_stack_initialized_small)->Threads(2);
BENCHMARK(do_calloc_small)->Threads(2);
BENCHMARK(do_stack_small)->Threads(4);
BENCHMARK(do_malloc_small)->Threads(4);
BENCHMARK(do_stack_initialized_small)->Threads(4);
BENCHMARK(do_calloc_small)->Threads(4);
BENCHMARK(do_stack_small)->Threads(8);
BENCHMARK(do_malloc_small)->Threads(8);
BENCHMARK(do_stack_initialized_small)->Threads(8);
BENCHMARK(do_calloc_small)->Threads(8);
#endif

// Register the function as a benchmark
BENCHMARK(do_stack_struct);
BENCHMARK(do_malloc_struct);
BENCHMARK(do_stack_initialized_struct);
BENCHMARK(do_calloc_struct);

#ifdef DO_THREADED_TESTS
BENCHMARK(do_stack_struct)->Threads(2);
BENCHMARK(do_malloc_struct)->Threads(2);
BENCHMARK(do_stack_initialized_struct)->Threads(2);
BENCHMARK(do_calloc_struct)->Threads(2);
BENCHMARK(do_stack_struct)->Threads(4);
BENCHMARK(do_malloc_struct)->Threads(4);
BENCHMARK(do_stack_initialized_struct)->Threads(4);
BENCHMARK(do_calloc_struct)->Threads(4);
BENCHMARK(do_stack_struct)->Threads(8);
BENCHMARK(do_malloc_struct)->Threads(8);
BENCHMARK(do_stack_initialized_struct)->Threads(8);
BENCHMARK(do_calloc_struct)->Threads(8);
#endif

// Register the function as a benchmark
BENCHMARK(do_stack_recursive);
BENCHMARK(do_malloc_recursive);
BENCHMARK(do_stack_initialized_recursive);
BENCHMARK(do_calloc_recursive);

#ifdef DO_THREADED_TESTS
BENCHMARK(do_stack_recursive)->Threads(2);
BENCHMARK(do_malloc_recursive)->Threads(2);
BENCHMARK(do_stack_initialized_recursive)->Threads(2);
BENCHMARK(do_calloc_recursive)->Threads(2);
BENCHMARK(do_stack_recursive)->Threads(4);
BENCHMARK(do_malloc_recursive)->Threads(4);
BENCHMARK(do_stack_initialized_recursive)->Threads(4);
BENCHMARK(do_calloc_recursive)->Threads(4);
BENCHMARK(do_stack_recursive)->Threads(8);
BENCHMARK(do_malloc_recursive)->Threads(8);
BENCHMARK(do_stack_initialized_recursive)->Threads(8);
BENCHMARK(do_calloc_recursive)->Threads(8);
#endif
// Run the benchmark
BENCHMARK_MAIN();