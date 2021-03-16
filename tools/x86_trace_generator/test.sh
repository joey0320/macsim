#!/bin/bash
make

cd ./x86-test/avx-add
make
cd ../../

pin -t ./obj-intel64/trace_generator.so -manual 1 -pim 1 -- ./x86-test/avx-add/main

# cat memtrace.txt
