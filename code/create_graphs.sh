#!/usr/bin/env bash

if [ 3 -ne $# ]; then
    echo "Usage: " $0 " <Binary Dir> <Source Dir>  <Output Dir>"
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