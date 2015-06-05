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
	$(BIN)/$(target) $(ARG)/points.dat $(OUT)/output.dat

edit:
	vim $(SRC)/$(target).cpp

clean:
	rm -rf $(OUT) $(BIN)
