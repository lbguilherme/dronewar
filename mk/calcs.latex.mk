
PDFLATEX := pdflatex -halt-on-error -file-line-error

build/calcs.pdf: calcs/calcs.tex $(wildcard calcs/**/*.tex) mk/calcs.latex.mk
	@echo "Producing  $@ ..."
	@mkdir -p $(dir $@)
	-@cd calcs && ( \
		$(PDFLATEX) -output-directory=../$(dir $@) calcs.tex && \
		$(PDFLATEX) -output-directory=../$(dir $@) calcs.tex && \
		$(PDFLATEX) -output-directory=../$(dir $@) calcs.tex \
	) | grep ^\\./ | cat
	@rm -f `ls build/calcs.* | grep -v pdf`
