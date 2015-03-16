LIB=../../lib
SRC=madj.cpp main.cpp

all: main $(LIB)/madj.hpp
main: $(SRC)
	g++ $? -o $@
clean:
	@find . -type f -executable -exec rm -fr {} \;
