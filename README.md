# Allocation benchmarks
This is research into allocation types and how efficient they are in different scenarios.

## dependencies
The following programs are required to build this project

- gcc (or equivalent)
- g++ (or equivalent)
- cmake
- git
- texlive (may require texlive-full)
- libtool
- automake
- ncat (for running a server during sporadic tests)

## Build
```
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
make install
```
turn off building of docs by changing the cmake command to:
```
cmake .. -DCMAKE_BUILD_TYPE=Release -DNO_DOCS=true
```

## Run a single test
```
./build/code/light_usage_test --benchmark_repetitions=10 --benchmark_display_aggregates_only=true --benchmark_out=./light_usage_test.results --benchmark_out_format=json
```

## Run all tests and generate data
```
cd build/bin
./run_tests.sh
```

## Display results
```
./code/graph.py light_usage_test.results -g 'small' 'large' 'struct' 'recursive'
```
