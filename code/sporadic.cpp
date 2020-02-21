#include <benchmark/benchmark.h>
#include <iostream>
#include <unistd.h>

#include "sporadic.h"

#define newTest(name, testFunc)                                                     \
    void name(benchmark::State &state)                                              \
    {                                                                               \
        double bytes_transferred = 0;                                               \
        int sock = sporadic_setup();                                                \
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
                bytes_transferred += tmp;                                                             \
            }                                                                       \
                                                           \
        }                                                                           \
                                                                                    \
        state.counters["Rate"] = benchmark::Counter(bytes_transferred, benchmark::Counter::kIsRate);                     \
                                                                                    \
        /* cleanup */                                                               \
        close(sock);                                                                \
    }

newTest(do_stack, stack_sporadic_test);
newTest(do_malloc, malloc_sporadic_test);
newTest(do_stack_initialized, stack_initalized_sporadic_test);
newTest(do_calloc, calloc_sporadic_test);
    

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