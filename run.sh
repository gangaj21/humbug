#!/bin/bash
cpp_file="./src/main.cpp" 

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 Moves testcase_file"
    exit 1
fi

arg1="$1"
arg2="$2"

if [ ! -f "$cpp_file" ]; then
    echo "Error: Source file '$cpp_file' not found"
    exit 1
fi

echo "Compiling $cpp_file..."
g++ -O3 "$cpp_file"

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

echo "Running a.out with arguments: $arg1 $arg2"
"./a.out" "$arg1" "$arg2"
cd ..
