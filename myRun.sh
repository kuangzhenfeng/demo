#!/bin/sh
cd build
cmake ..
make clean
make -j16

ulimit -c unlimited
./demo