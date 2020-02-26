#include <benchmark/benchmark.h>
#include "light.h"

#define newTest(NAME, FUNC) \
    void NAME(benchmark::State& state) \
    {\
        for (auto _ : state)\
        {\
            FUNC();\
        }\
    }

// X_LARGE tests *********************************************************************
newTest(do_malloc_xlarge,malloc_light_xlarge_test);
newTest(do_stack_xlarge,stack_light_xlarge_test);
newTest(do_calloc_xlarge,calloc_light_xlarge_test);
newTest(do_stack_initialized_xlarge,stack_initialized_light_xlarge_test);

// LARGE tests *********************************************************************
newTest(do_malloc_large,malloc_light_large_test);
newTest(do_stack_large,stack_light_large_test);
newTest(do_calloc_large,calloc_light_large_test);
newTest(do_stack_initialized_large,stack_initialized_light_large_test);

// MEDIUM tests *********************************************************************
newTest(do_malloc_medium,malloc_light_medium_test);
newTest(do_stack_medium,stack_light_medium_test);
newTest(do_calloc_medium,calloc_light_medium_test);
newTest(do_stack_initialized_medium,stack_initialized_light_medium_test);

// SMALL tests *********************************************************************
newTest(do_malloc_small,malloc_light_small_test);
newTest(do_stack_small,stack_light_small_test);
newTest(do_calloc_small,calloc_light_small_test);
newTest(do_stack_initialized_small,stack_initialized_light_small_test);


// struct tests *********************************************************************
newTest(do_malloc_struct,malloc_struct_test);
newTest(do_stack_struct,stack_struct_test);
newTest(do_calloc_struct,calloc_struct_test);
newTest(do_stack_initialized_struct,stack_initialized_struct_test);


// multiple tests *********************************************************************
newTest(do_malloc_multiple,malloc_multi_test);
newTest(do_stack_multiple,stack_multi_test);
newTest(do_calloc_multiple,calloc_multi_test);
newTest(do_stack_initialized_multiple,stack_initialized_multi_test);


// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_xlarge);
BENCHMARK(do_malloc_xlarge);
BENCHMARK(do_stack_initialized_xlarge);
BENCHMARK(do_calloc_xlarge);
#else
BENCHMARK(do_stack_xlarge)->ThreadRange(1,8);
BENCHMARK(do_malloc_xlarge)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_xlarge)->ThreadRange(1,8);
BENCHMARK(do_calloc_xlarge)->ThreadRange(1,8);
#endif

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_large);
BENCHMARK(do_malloc_large);
BENCHMARK(do_stack_initialized_large);
BENCHMARK(do_calloc_large);
#else
BENCHMARK(do_stack_large)->ThreadRange(1,8);
BENCHMARK(do_malloc_large)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_large)->ThreadRange(1,8);
BENCHMARK(do_calloc_large)->ThreadRange(1,8);
#endif

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_medium);
BENCHMARK(do_malloc_medium);
BENCHMARK(do_stack_initialized_medium);
BENCHMARK(do_calloc_medium);
#else
BENCHMARK(do_stack_medium)->ThreadRange(1,8);
BENCHMARK(do_malloc_medium)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_medium)->ThreadRange(1,8);
BENCHMARK(do_calloc_medium)->ThreadRange(1,8);
#endif

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_small);
BENCHMARK(do_malloc_small);
BENCHMARK(do_stack_initialized_small);
BENCHMARK(do_calloc_small);
#else
BENCHMARK(do_stack_small)->ThreadRange(1,8);
BENCHMARK(do_malloc_small)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_small)->ThreadRange(1,8);
BENCHMARK(do_calloc_small)->ThreadRange(1,8);
#endif

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_struct);
BENCHMARK(do_malloc_struct);
BENCHMARK(do_stack_initialized_struct);
BENCHMARK(do_calloc_struct);
#else
BENCHMARK(do_stack_struct)->ThreadRange(1,8);
BENCHMARK(do_malloc_struct)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_struct)->ThreadRange(1,8);
BENCHMARK(do_calloc_struct)->ThreadRange(1,8);
#endif

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_multiple);
BENCHMARK(do_malloc_multiple);
BENCHMARK(do_stack_initialized_multiple);
BENCHMARK(do_calloc_multiple);
#else
BENCHMARK(do_stack_multiple)->ThreadRange(1,8);
BENCHMARK(do_malloc_multiple)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_multiple)->ThreadRange(1,8);
BENCHMARK(do_calloc_multiple)->ThreadRange(1,8);
#endif
// Run the benchmark
BENCHMARK_MAIN();