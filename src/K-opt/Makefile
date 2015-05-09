BIN=bin
LIB=lib
SRC=src
INP=arg
OUT=out

CC=g++
CFLAGS=-I $(LIB)

all:
	mkdir -p $(BIN) $(OUT)

test: $(BIN)/main $(INP)/points.dat
	$^ $(OUT)/output.dat

$(BIN)/%: $(SRC)/%.cpp
	$(CC) $? -o $@ $(CFLAGS)

clean: 
	rm -rf $(BIN) $(OUT)
