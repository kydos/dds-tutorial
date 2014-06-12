all:
	latex main
	dvipdf main.dvi main.pdf


deep:
	latex main
	makeindex main
	latex main
	bibtex main
	latex main
	make all

clean:
	rm -f  *~ *.log *.aux *.bbl *.out *.dvi *.blg *.tdo *.idx *.toc *.ilg *.ind

