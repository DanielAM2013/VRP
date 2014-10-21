#!/bin/bash

rm *.test
g++ cw.cpp -o ../bin/cw
../bin/cw
gnuplot -p plot.gn
