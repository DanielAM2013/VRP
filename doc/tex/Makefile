SRC=src
OUT=out
FIG=fig
REF=ref

SRCS=$(wildcard $(SRC)/*.tex)

target=main

all: compilation

.PHONE: edit pdf view

compilation: $(SRC)/$(target).tex 
	@pdflatex --output-directory=./out --file-line-error $< 2> /dev/null 

view: $(OUT)/$(target).pdf
	@evince $? > /dev/null 2>&1 &

$(OUT)/%.pdf: $(SRC)/%.tex
	@mkdir -p $(OUT) 
	@pdflatex --output-directory=./out --file-line-error $< 2> /dev/null 

edit: $(SRCS)
	@vim -p$(shell echo "$?" | wc -w) $(SRCS);

clean:
	rm -r $(OUT)
