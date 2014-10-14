#!/bin/bash

rm *.test
g++ cw.cpp -o ../bin/cw
../bin/cw
gnuplot plot.gn
evince cw.eps
