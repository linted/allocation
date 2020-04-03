#!/usr/bin/env bash

if [ 3 -ne $# ]; then
    echo "Usage: " $0 " <Binary Dir> <Source Dir> <Output Dir>"
    exit 1
fi

BINARY_DIR=$1
SOURCE_DIR=$2
OUTPUT_DIR=$3

echo "Creating bar graphs"
for test_data in $SOURCE_DIR/light*; do
    $BINARY_DIR/graph.py $test_data -g huge large medium small -o $OUTPUT_DIR/$(basename $test_data .json).png &
done
wait

echo "Creating threaded bar graphs"
for threaded_data in $SOURCE_DIR/*thread*; do
    $BINARY_DIR/graph.py $threaded_data -g 8 4 2 1 -o $OUTPUT_DIR/$(basename $threaded_data .json)_threads.png &
done
wait

echo "Creating Algo 1 histograms"
echo "-Creating full histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "small" "medium" "large" "huge" -t "Light Usage Compairison" -o $OUTPUT_DIR/light_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "small" "medium" "large" "huge" -t "Threaded Light Usage Compairison" -o $OUTPUT_DIR/light_threaded_hist.png &
wait

echo "-Creating stack and malloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "stack_small" "stack_medium" "stack_large" "stack_huge" "malloc_small" "malloc_medium" "malloc_large" "malloc_huge" -t "Light Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/light_stack_malloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "stack_small" "stack_medium" "stack_large" "stack_huge" "malloc_small" "malloc_medium" "malloc_large" "malloc_huge" -t "Threaded Light Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/light_stack_malloc_threaded_hist.png &
wait

echo "-Creating init and calloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "initialized_small" "initialized_medium" "initialized_large" "initialized_huge" "calloc_small" "calloc_medium" "calloc_large" "calloc_huge" -t "Light Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/light_init_calloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "initialized_small" "initialized_medium" "initialized_large" "initialized_huge" "calloc_small" "calloc_medium" "calloc_large" "calloc_huge"  -t "Threaded Light Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/light_init_calloc_threaded_hist.png &
wait

echo "Creating Algo 2 histograms"
echo "-Creating full histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "struct" -t "Struct Usage Compairison" -o $OUTPUT_DIR/struct_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "struct" -t "Threaded Struct Usage Compairison" -o $OUTPUT_DIR/struct_threaded_hist.png &
wait

echo "-Creating stack and malloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "(?:malloc|stack)_struct" -t "Struct Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/struct_stack_malloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "(?:calloc|init)_struct"  -t "Threaded Struct Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/struct_stack_malloc_threaded_hist.png &
wait

echo "-Creating init and calloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "(?:calloc|initialized)_struct" -t "Struct Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/struct_init_calloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f  "(?:calloc|initialized)_struct" -t "Threaded Struct Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/struct_init_calloc_threaded_hist.png &
wait

echo "Creating Algo 3 histograms"
echo "-Creating full histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "small" "medium" "large" "huge" -t "Sporatic Usage Compairison" -o $OUTPUT_DIR/sporatic_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "small" "medium" "large" "huge" -t "Threaded Sporatic Usage Compairison" -o $OUTPUT_DIR/sporatic_threaded_hist.png &
wait

echo "-Creating stack and malloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "stack_[^i(:?st)(:?mu)]" "malloc_[^(:?st)(:?mu)]" -t "Sporatic Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/sporatic_stack_malloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "stack_[^i(:?st)(:?mu)]" "malloc_[^(:?st)(:?mu)]" -t "Threaded Sporatic Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/sporatic_stack_malloc_threaded_hist.png &
wait

echo "-Creating init and calloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "initialized.*_small" "initialized.*_medium" "initialized.*_large" "initialized.*_huge" "calloc.*_small" "calloc.*_medium" "calloc.*_large" "calloc.*_huge"  -t "Sporatic Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/sporatic_init_calloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "initialized.*_small" "initialized.*_medium" "initialized.*_large" "initialized.*_huge" "calloc.*_small" "calloc.*_medium" "calloc.*_large" "calloc.*_huge"  -t "Threaded Sporatic Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/sporatic_init_calloc_threaded_hist.png &
wait