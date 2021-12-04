#!/bin/sh

mkdir -p outputs/small
mkdir -p outputs/medium
mkdir -p outputs/large

find ./inputs -name "*.in" |
    cut -f 3- -d "/" - |
    cut -f 1 -d "." - |
    parallel -j 100% --progress "bash -c "$*" < inputs/{}.in > outputs/{}.out"
