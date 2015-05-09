LIB=lib
BIN=bin
OBJ=obj
SRC=src
OUT=out

CC=g++
CFLAGS=-I $(LIB)

all: 
	mkdir -p $(BIN) $(OUT)
	$(CC) $(SRC)/main.cpp -o $(BIN)/main $(CFLAGS)

edit:
	vim $(SRC)/main.cpp

clean:
	rm -rf $(OUT) $(BIN)






