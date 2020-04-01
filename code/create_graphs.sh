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

echo "Creating full histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -t "Light Usage Compairison" -o $OUTPUT_DIR/light_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -t "Threaded Light Usage Compairison" -o $OUTPUT_DIR/light_threaded_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -t "Sporatic Usage Compairison" -o $OUTPUT_DIR/sporatic_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -t "Threaded Sporatic Usage Compairison" -o $OUTPUT_DIR/sporatic_threaded_hist.png &
wait

echo "Creating stack and malloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "stack_[^i]|malloc" -t "Light Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/light_stack_malloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "stack_[^i]|malloc" -t "Threaded Light Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/light_stack_malloc_threaded_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "stack_[^i]|malloc" -t "Sporatic Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/sporatic_stack_malloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "stack_[^i]|malloc" -t "Threaded Sporatic Usage Stack and Malloc Compairison" -o $OUTPUT_DIR/sporatic_stack_malloc_threaded_hist.png &
wait

echo "Creating init and calloc histograms"
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_lib*.json -f "init|calloc" -t "Light Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/light_init_calloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/light_thread*.json -f "init|calloc" -t "Threaded Light Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/light_init_calloc_threaded_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_lib*.json -f "init|calloc" -t "Sporatic Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/sporatic_init_calloc_hist.png &
$BINARY_DIR/graph_hist.py $SOURCE_DIR/sporatic_thread*.json -f "init|calloc" -t "Threaded Sporatic Usage Initalized and Calloc Compairison" -o $OUTPUT_DIR/sporatic_init_calloc_threaded_hist.png &
wait
