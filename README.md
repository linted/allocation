# Allocation benchmarks
This is research into allocation types and how efficient they are in different scenarios.

## Build
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release && make -j8
```

## Run
```
./build/code/light_usage_test --benchmark_repetitions=10 --benchmark_display_aggregates_only=true --benchmark_out=./light_usage_test.results --benchmark_out_format=json
```

## Display results
```
./code/graph.py light_usage_test.results -g 'small' 'large' 'struct' 'recursive'
```