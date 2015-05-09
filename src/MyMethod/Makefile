ARG=arg
BIN=bin
LIB=lib
SRC=src
OUT=out
BIN=bin
EXT=ext
CFLAGS=-I $(LIB)

all:
	mkdir -p $(OUT) $(BIN)
	g++ $(SRC)/vrp.cpp -o $(BIN)/vrp $(CFLAGS)

test:
	$(BIN)/vrp $(ARG)/points.dat $(OUT)/output.dat

edit:
	vim $(SRC)/vrp.cpp

clean:
	rm -rf $(OUT) $(BIN)
