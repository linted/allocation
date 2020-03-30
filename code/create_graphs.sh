#!/usr/bin/env bash

if [ 3 -ne $# ]; then
    echo "Usage: " $0 " <Binary Dir> <Source Dir> <Output Dir>"
fi

BINARY_DIR=$1
SOURCE_DIR=$2
OUTPUT_DIR=$3

for test_data in $SOURCE_DIR/light*; do
    echo "Creating graph of $test_data"
    $BINARY_DIR/graph.py $test_data -g huge large medium small -o $OUTPUT_DIR/$(basename $test_data .json).png
done

for threaded_data in $SOURCE_DIR/*thread*; do
    echo "Creating threaded graph of $threaded_data"
    $BINARY_DIR/graph.py $threaded_data -g 8 4 2 1 -o $OUTPUT_DIR/$(basename $threaded_data .json)_threads.png
done

echo "Creating full histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -o $OUTPUT_DIR/light_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -o $OUTPUT_DIR/light_threaded_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -o $OUTPUT_DIR/sporatic_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -o $OUTPUT_DIR/sporatic_threaded_hist.png

echo "Creating stack and malloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "stack_[^i]|malloc" -o $OUTPUT_DIR/light_stack_malloc_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "stack_[^i]|malloc" -o $OUTPUT_DIR/light_stack_malloc_threaded_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "stack_[^i]|malloc" -o $OUTPUT_DIR/sporatic_stack_malloc_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "stack_[^i]|malloc" -o $OUTPUT_DIR/sporatic_stack_malloc_threaded_hist.png

echo "Creating init and calloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "init|calloc" -o $OUTPUT_DIR/light_init_calloc_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "init|calloc" -o $OUTPUT_DIR/light_init_calloc_threaded_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "init|calloc" -o $OUTPUT_DIR/sporatic_init_calloc_hist.png
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "init|calloc" -o $OUTPUT_DIR/sporatic_init_calloc_threaded_hist.png