#!/bin/bash

cd ${PWD##}/slog
make clean
make

cd ../src
make clean
make

echo "[-] Build done"