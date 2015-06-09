ARG=arg
BIN=bin
LIB=lib
SRC=src
OUT=out
BIN=bin
CFLAGS=-I $(LIB)

target=main

all: compilation test

test:
	$(BIN)/$(target)

compilation:
	mkdir -p $(OUT) $(BIN)
	g++ $(SRC)/$(target).cpp -o $(BIN)/$(target) $(CFLAGS)

edit:
	vim $(SRC)/$(target).cpp

clean:
	rm -rf $(OUT) $(BIN)
