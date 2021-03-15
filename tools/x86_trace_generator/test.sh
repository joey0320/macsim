#!/bin/bash
make

cd ./x86-test/sort_and_add
make
cd ../../

pin -t ./obj-intel64/trace_generator.so -manual 1 -pim 1 -- ./x86-test/sort_and_add/main

# cat memtrace.txt
