ARG=arg
BIN=bin
LIB=lib
SRC=src
OUT=out
BIN=bin
CFLAGS=-I $(LIB)

target=main

all:
	mkdir -p $(OUT) $(BIN)
	g++ $(SRC)/$(target).cpp -o $(BIN)/$(target) $(CFLAGS)
	for i in $(shell seq 1 1); do \
		$(BIN)/$(target) $(ARG)/points$$i.dat $(OUT)/output$$i.dat; \
	done; 


plot:
	@gnuplot -e "set term postscript; set output '$(OUT)/plot.ps'; plot '$(OUT)/output1.dat' with linespoints"
	@epstopdf $(OUT)/plot.ps --outfile=$(OUT)/plot.pdf
	@pdftk $(OUT)/plot.pdf cat 1east output $(OUT)/output.pdf
	@rm $(OUT)/plot.ps $(OUT)/plot.pdf

view: plot
	evince $(OUT)/output.pdf &

edit:
	vim $(SRC)/$(target).cpp

clean:
	rm -rf $(OUT) $(BIN)
