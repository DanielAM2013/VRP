
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
	g++ $(SRC)/convexo.cpp -o $(BIN)/convexo $(CFLAGS)

test:
	$(BIN)/convexo $(ARG)/points.dat $(OUT)/output.dat

edit:
	vim $(SRC)/convexo.cpp

clean:
	rm -rf $(OUT) $(BIN)
