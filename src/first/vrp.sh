#!/bin/bash

#rm *.test
g++ vrp.cpp -o ../bin/vrp
../bin/vrp
gnuplot plot.gn
evince vrp.eps
