#!/bin/sh
cd build
cmake ..
make clean
make -j16

echo "Run demo..."
ulimit -c unlimited
./demo
