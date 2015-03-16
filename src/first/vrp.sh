#!/bin/bash

#rm *.test
mkdir -p ../bin/vrp
g++ vrp.cpp -o ../bin/vrp
../bin/vrp
gnuplot plot.gn
evince vrp.eps
