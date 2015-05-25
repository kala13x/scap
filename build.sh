#!/bin/bash

cd ${PWD##}/libslog
make clean
make

cd ..
make clean
make

echo "[-] Build done"