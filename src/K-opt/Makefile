ARG=arg
BIN=bin
LIB=lib
SRC=src
OUT=out
BIN=bin
CFLAGS=-I $(LIB) -fpermissive

target=main

all:
	mkdir -p $(OUT) $(BIN)
	g++ $(SRC)/$(target).cpp -o $(BIN)/$(target) $(CFLAGS)
	for i in $(shell seq 1 3); do \
		$(BIN)/$(target) $(ARG)/points$$i.dat $(OUT)/output$$i.dat; \
	done; 


$(BIN)/%: $(SRC)/%.cpp
	g++ $? -o $@ $(CFLAGS)

SRCs=$(wildcard $(SRC)/*)
edit:
	vim -p$(ls $(SRC) | wc -w) $(SRCs)

clean:
	rm -rf $(OUT) $(BIN)
