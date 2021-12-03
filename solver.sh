#!/bin/sh

mkdir -p outputs/small
mkdir -p outputs/medium
mkdir -p outputs/large

cat unsolved |
    # head -n 1 |
    parallel -j 100% --progress "bash -c "$*" < inputs/{}.in > outputs/{}.out"
