#tsp: tsp.cpp

all:

edit:

gpu:

doc:

tex:

tsp: tsp.cpp src/dados.dat
 g++ ./src/tsp.cpp -o ./bin/tsp

random: random.cpp dados.dat
 g++ -std=c++11 ./src/random.cpp -o ./bin/random



clean:

