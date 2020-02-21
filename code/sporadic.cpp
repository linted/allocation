#include <benchmark/benchmark.h>
#include <iostream>
#include <unistd.h>

#include "sporadic.h"

#define newNetworkTest(name, testFunc)                                                               \
    void name(benchmark::State &state)                                                               \
    {                                                                                                \
        double bytes_transferred = 0;                                                                \
        int sock = network_setup();                                                                  \
        if (-1 == sock)                                                                              \
        {                                                                                            \
            return;                                                                                  \
        }                                                                                            \
        for (auto _ : state)                                                                         \
        {                                                                                            \
            /* code that is timed */                                                                 \
            ssize_t tmp = testFunc(sock);                                                            \
            if (0 < tmp)                                                                             \
            {                                                                                        \
                /* if the socket dies, quit early. there is no reason to continue*/                  \
                bytes_transferred += tmp;                                                            \
            }                                                                                        \
        }                                                                                            \
        state.counters["Rate"] = benchmark::Counter(bytes_transferred, benchmark::Counter::kIsRate); \
        /* cleanup */                                                                                \
        close(sock);                                                                                 \
    }

newNetworkTest(do_stack_network_large, stack_network_large_test);
newNetworkTest(do_malloc_network_large, malloc_network_large_test);
newNetworkTest(do_stack_initialized_network_large, stack_initialized_network_large_test);
newNetworkTest(do_calloc_network_large, calloc_network_large_test);

newNetworkTest(do_stack_network_small, stack_network_small_test);
newNetworkTest(do_malloc_network_small, malloc_network_small_test);
newNetworkTest(do_stack_initialized_network_small, stack_initialized_network_small_test);
newNetworkTest(do_calloc_network_small, calloc_network_small_test);

// Register the function as a benchmark
BENCHMARK(do_stack_network_large);
BENCHMARK(do_malloc_network_large);
BENCHMARK(do_stack_initialized_network_large);
BENCHMARK(do_calloc_network_large);
// Register the function as a benchmark
BENCHMARK(do_stack_network_small);
BENCHMARK(do_malloc_network_small);
BENCHMARK(do_stack_initialized_network_small);
BENCHMARK(do_calloc_network_small);
// Run the benchmark
BENCHMARK_MAIN();