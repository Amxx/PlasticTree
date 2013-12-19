#!/bin/bash
mkdir -p build &&
cd build &&
cmake -DCMAKE_INSTALL_PREFIX:PATH=../install .. &&
make install &&
cd .. &&
./install/bin/PlasticTree