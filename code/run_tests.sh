#!/usr/bin/env bash

cleanup () {
    echo "killing $1"
    kill -9 $1
    exit
}

flush_cache () {
    sudo sync
    echo 1 | sudo tee /proc/sys/vm/drop_caches 1>/dev/null
}

light_usage_tests () {
    echo "******************************************"
    echo "***" Light Usage Tests with $1
    echo "******************************************"
    flush_cache
    LD_PRELOAD=./$1 ./light_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/light_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

light_usage_threaded_tests () {
    echo "******************************************"
    echo "***" Light Usage Threaded Tests with $1
    echo "******************************************"
    flush_cache
    LD_PRELOAD=./$1 ./light_usage_test_threaded --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/light_threaded_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

sporatic_usage_tests () {
    echo "******************************************"
    echo "***" Sporatic Usage Tests with $1
    echo "******************************************"
    flush_cache
    LD_PRELOAD=./$1 ./sporatic_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/sporatic_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

sporatic_usage_threaded_tests () {
    echo "******************************************"
    echo "***" Sporatic Usage Threaded Tests with $1
    echo "******************************************"
    flush_cache
    LD_PRELOAD=./$1 ./sporatic_usage_test_threaded --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/sporatic_threaded_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}


# stat the ncat server that will be sending the data for the networking tests
ncat -k -vlp 4000 -e "/usr/bin/yes" 1>/dev/null  2>&1 &
ncat_pid=$!

# setup a signal handler to cleanup the ncat server if we die
trap 'cleanup $ncat_pid' SIGINT

# make the output dir if it doesn't exist
mkdir -p output

ALLOCATION_LIBRARIES="libdlmalloc.so libhoard.so libptmalloc3.so libjemalloc.so.2 libtcmalloc_minimal.so"
for allocator in $ALLOCATION_LIBRARIES; do
    echo Starting work on $allocator

    # make sure that the library is executable
    chmod +x $allocator

    # run the single threaded tests
    light_usage_tests $allocator 1 20
    sporatic_usage_tests $allocator 1 20

    # check and see if there is a discrete thread safe version of the allocator
    allocator_threaded=$allocator
    if [ -f ${allocator%.so}_threadsafe.so ]; then
        allocator_threaded=${allocator%.so}_threadsafe.so
    fi

    # run the threaded tests
    sporatic_usage_threaded_tests $allocator_threaded 1 20
    sporatic_usage_threaded_tests $allocator_threaded 1 20

done

kill -9 $ncat_pid