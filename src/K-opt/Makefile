BIN=bin
OBJ=obj
LIB=lib
SRC=src
INP=arg
OUT=out

CC=g++


all: $(BIN)/main $(INP)/points.dat
	$^ $(OUT)/output.dat

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) -c $? -o $@

$(BIN)/main: $(OBJ)/main.o
	$(CC) $? -o $@

clean: 
	rm -f $(BIN)/* $(OBJ)/* $(OUT)/*
