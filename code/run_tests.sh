#!/usr/bin/env bash



ncat -k -vlp 4000 -e "/usr/bin/yes" 1>/dev/null  2>&1 &
ncat_pid=$!

trap 'cleanup $ncat_pid' SIGINT

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
    echo "**************************************"
    echo "***" Light Usage Test with $1
    echo "**************************************"
    flush_cache
    LD_PRELOAD=./$1 ./light_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/light_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

sporatic_usage_tests () {
    echo "**************************************"
    echo "***" Sporatic Usage Test with $1
    echo "**************************************"
    flush_cache
    LD_PRELOAD=./$1 ./sporatic_usage_test --benchmark_min_time=$2 --benchmark_repetitions=$3 --benchmark_out=output/sporatic_$1_$2s_$3.json --benchmark_out_format=json --benchmark_display_aggregates_only=true
}

mkdir output

ALLOCATION_LIBRARIES="libhoard.so  libjemalloc.so.2  libptmalloc3.so  libtcmalloc_minimal.so  libtcmalloc.so libc.so.6"
for allocator in $ALLOCATION_LIBRARIES; do
    echo Starting work on $allocator
    chmod +x $allocator
    light_usage_tests $allocator 1 20
    sporatic_usage_tests $allocator 1 20
done

kill -9 $ncat_pid