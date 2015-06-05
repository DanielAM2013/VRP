SRC=src
OUT=out
DOC=doc

SHELL=/bin/bash

ifndef VERBOSE
.SILENT:
endif

all:
	@for i in $$(ls $(SRC)); do \
		echo make $(SRC)/$$i; \
		$(MAKE) -C $(SRC)/$$i; \
	done;

doc:
	cd $(DOC)


edit:


tsp: tsp.cpp src/dados.dat
	g++ ./src/tsp.cpp -o ./bin/tsp

random: random.cpp dados.dat
	g++ -std=c++11 ./src/random.cpp -o ./bin/random

clean:
	for i in $$(ls $(SRC)); do \
		echo clean $(SRC)/$$i; \
		$(MAKE) clean -C $(SRC)/$$i; \
	done;
	rm -rf $(OUT);


