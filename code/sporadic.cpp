#include <benchmark/benchmark.h>
#include <iostream>
#include <unistd.h>

#include "sporadic.h"

#define newNetworkTest(name, testFunc)                                              \
    void name(benchmark::State &state)                                              \
    {                                                                               \
        double bytes_transferred = 0;                                               \
        int sock = network_setup();                                                 \
        if (-1 == sock)                                                             \
        {                                                                           \
            return;                                                                 \
        }                                                                           \
        for (auto _ : state)                                                        \
        {                                                                           \
            /* code that is timed */                                                \
            ssize_t tmp = testFunc(sock);                                           \
            if (0 < tmp)                                                            \
            {                                                                       \
                /* if the socket dies, quit early. there is no reason to continue*/ \
                bytes_transferred += tmp;                                           \
            }                                                                       \
        }                                                                           \
        state.SetBytesProcessed(bytes_transferred);                                 \
        /* cleanup */                                                               \
        close(sock);                                                                \
    }

newNetworkTest(do_stack_network_large, stack_network_large_test);
newNetworkTest(do_malloc_network_large, malloc_network_large_test);
newNetworkTest(do_stack_initialized_network_large, stack_initialized_network_large_test);
newNetworkTest(do_calloc_network_large, calloc_network_large_test);

newNetworkTest(do_stack_network_medium, stack_network_medium_test);
newNetworkTest(do_malloc_network_medium, malloc_network_medium_test);
newNetworkTest(do_stack_initialized_network_medium, stack_initialized_network_medium_test);
newNetworkTest(do_calloc_network_medium, calloc_network_medium_test);

newNetworkTest(do_stack_network_small, stack_network_small_test);
newNetworkTest(do_malloc_network_small, malloc_network_small_test);
newNetworkTest(do_stack_initialized_network_small, stack_initialized_network_small_test);
newNetworkTest(do_calloc_network_small, calloc_network_small_test);

// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_network_large);
BENCHMARK(do_malloc_network_large);
BENCHMARK(do_stack_initialized_network_large);
BENCHMARK(do_calloc_network_large);
#else 
BENCHMARK(do_stack_network_large)->ThreadRange(1,8);
BENCHMARK(do_malloc_network_large)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_network_large)->ThreadRange(1,8);
BENCHMARK(do_calloc_network_large)->ThreadRange(1,8);
#endif
// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_network_medium);
BENCHMARK(do_malloc_network_medium);
BENCHMARK(do_stack_initialized_network_medium);
BENCHMARK(do_calloc_network_medium);
#else 
BENCHMARK(do_stack_network_medium)->ThreadRange(1,8);
BENCHMARK(do_malloc_network_medium)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_network_medium)->ThreadRange(1,8);
BENCHMARK(do_calloc_network_medium)->ThreadRange(1,8);
#endif
// Register the function as a benchmark
#ifndef DO_THREADED_TESTS
BENCHMARK(do_stack_network_small);
BENCHMARK(do_malloc_network_small);
BENCHMARK(do_stack_initialized_network_small);
BENCHMARK(do_calloc_network_small);
#else 
BENCHMARK(do_stack_network_small)->ThreadRange(1,8);
BENCHMARK(do_malloc_network_small)->ThreadRange(1,8);
BENCHMARK(do_stack_initialized_network_small)->ThreadRange(1,8);
BENCHMARK(do_calloc_network_small)->ThreadRange(1,8);
#endif
// Run the benchmark
BENCHMARK_MAIN();