ARG=arg
BIN=bin
LIB=lib
SRC=src
OUT=out
BIN=bin
CFLAGS=-I $(LIB)

target=main

all:
	mkdir -p $(OUT) $(BIN)
	g++ $(SRC)/$(target).cpp -o $(BIN)/$(target) $(CFLAGS)
	for i in $(shell seq 1 3); do \
		$(BIN)/$(target) $(ARG)/points$$i.dat $(OUT)/output$$i.dat; \
	done; 

		#$(BIN)/$(target) $(ARG)/points$$i.dat $(OUT)/output$$i.dat; 
edit:
	vim $(SRC)/$(target).cpp

clean:
	rm -rf $(OUT) $(BIN)
