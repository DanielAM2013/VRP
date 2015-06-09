CC=g++
OCL=ocl
BIN=bin
LIB=lib
SRC=src
OUT=out
ARG=arg

CPPFLAGS=-I $(LIB)
CLIBS=-lOpenCL

target=convex
kernel=mean

CPPFLAGS=-I $(LIB)
OCLFLAGS=-DOCLFLAGS='"-I $(LIB)"'

BINS=$(patsubst $(OCL)/%.cl, $(BIN)/%.bcl, $(wildcard $(OCL)/*.cl))
LOG=$(OUT)/log.txt
#-------------------------------------------------------------------------------

all:

edit: $(SRC)/$(target).cpp $(OCL)/$(kernel).cl $(LIB)/base.hpp
	@vim -p$(shell echo "$?" | wc -w) $?

.PHONY: kernel view

view: $(OUT)/$(target).test
	less $?

kernel: $(BIN)/$(kernel).bcl

#-------------------------------------------------------------------------------

$(OUT)/%.test: $(BIN)/% $(BIN)/$(kernel).bcl
	$^ $(kernel) $(ARG)/points.dat > $@
	
$(BIN)/%.bcl: $(BIN)/compilation $(OCL)/%.cl
	@while [ ! -e "$(LOG)" ] || [ -s "$(LOG)" ]; do \
		$^ $@ 2> $(LOG); \
		echo "try"; \
	done;
	@rm -f $(LOG)

$(BIN)/%: $(SRC)/%.cpp
	@$(CC) $(CPPFLAGS) $(OCLFLAGS) $? -o $@ $(CLIBS)

clean:
	rm -rf bin/ out/
	mkdir bin out
