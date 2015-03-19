BIN=bin
OBJ=obj
LIB=lib
SRC=src
CC=g++

all: $(BIN)/main

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) -c $? -o $@

$(BIN)/main: $(OBJ)/main.o
	$(CC) $? -o $@

clean: 
	rm -f $(BIN)/* $(OBJ)/*
