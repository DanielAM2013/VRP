LIB=../../lib
SRC= main.cpp madj.cpp

all: main $(LIB)/madj.hpp
main: $(SRC)
	g++ $? -o $@
clean:
	rm main
	#@find . -type f -executable -exec rm -fr {} \;
