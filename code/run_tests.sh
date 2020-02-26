#!/usr/bin/env bash



ncat -k -vlp 4000 -e "/usr/bin/yes" 1>/dev/null  2>&1 &
ncat_pid=$!

trap 'cleanup $ncat_pid' SIGINT

cleanup () {
    echo "killing $1"
    kill -9 $1
    exit
}

light_usage_tests () {
    LD_PRELOAD=./$1 ./light_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=light_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

sporatic_usage_tests () {
    LD_PRELOAD=./$1 ./sporatic_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=sporatic_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

ALLOCATION_LIBRARIES="libhoard.so  libjemalloc.so.2  libptmalloc3.so  libtcmalloc_minimal.so  libtcmalloc.so libc.so.6"
for allocator in $ALLOCATION_LIBRARIES; do
    chmod +x $allocator
    light_usage_tests $allocator 5 10
    sporatic_usage_tests $allocator 5 10
done

kill -9 $ncat_pid