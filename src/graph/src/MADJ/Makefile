LIB=lib
BIN=bin
OBJ=obj
SRC=main.cpp
DEP=madj.cpp 

CPPFLAGS=
#-Wall

all: $(BIN)/main 

$(OBJ)/madj.o: $(DEP)
	g++ -c $? -o $@
$(OBJ)/madj.a: $(OBJ)/madj.o
	ar rcs $@ $?
$(OBJ)/main.o: $(SRC)
	g++ -c $? -o $@
$(BIN)/main: $(OBJ)/main.o $(OBJ)/madj.a
	g++ $? $(CPPFLAGS) -o $@
	
clean:
	rm $(OBJ)/*.o $(OBJ)/*.a
