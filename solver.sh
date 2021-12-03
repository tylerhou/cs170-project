#!/bin/sh

mkdir -p outputs/small
mkdir -p outputs/medium
mkdir -p outputs/large

cat tosolve |
    parallel -j 100% --progress "bash -c "$*" < inputs/{}.in > outputs/{}.out"
