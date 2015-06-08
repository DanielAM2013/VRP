BIN=bin
SRC=src
OCL=ocl
ARG=arg
OUT=out
LIB=lib
GIT=.git

target=tsp
kernel=balance


SRCS=$(SRC)/$(target).cpp $(LIB)/vector_gpu.hpp $(OCL)/$(kernel).cl \
$(OCL)/composition.cl


KERNEL_SRC=$(OCL)/$(kernel).cl
KERNEL_BIN=$(BIN)/$(kernel).bcl
POINTS=$(ARG)/points.dat

CTAGS=$(GIT)/tags

CC=g++
CPPFLAGS=-I $(LIB)
OCLFLAGS=-DOCLFLAGS='"-I $(LIB)"'
CLIBS=-lOpenCL

all: $(BIN)/$(target) $(CTAGS)

convex: $(BIN)/convex

edit: $(SRCS)
	@vim -p$(shell echo "$?" | wc -w) $?

view: test
	@less $(OUT)/*

test: kernel_bin $(OUT)/$(target).test

$(CTAGS):
	@ctags -R --tag-relative=yes -f $@ .
	@echo "Create CTAGS"

$(OUT)/%.test: $(BIN)/% $(KERNEL_BIN)
	@$^ $(kernel) $(POINTS) > $@

$(BIN)/%: $(SRC)/%.cpp
	@$(CC) $(CPPFLAGS) $(OCLFLAGS) $? -o $@ $(CLIBS)
	@echo "Build $?"

BINS=$(patsubst $(OCL)/%.cl, $(BIN)/%.bcl, $(wildcard $(OCL)/*.cl))

kernel_bin: $(BIN)/compilation $(BINS)
	@echo "OpenCL Kernel Binary done"	
	
LOG=$(OUT)/log.txt

$(BIN)/%.bcl:  $(BIN)/compilation $(OCL)/%.cl
	@while [ ! -e "$(LOG)" ] || [ -s "$(LOG)" ]; do \
		$^ $@ 2> $(LOG); \
	done;
	@rm $(LOG)

clean:
	@rm -f $(BIN)/* $(OUT)/*
	@rm -f $(CTAGS)
	@echo "Clean"
