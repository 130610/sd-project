# Compile all xml files to html using the xalan program.
all: $(patsubst %.xml, %.html, $(wildcard *.xml))

%.html: %.xml Makefile
	    ~cs251/.bin/xalan < $< > $@

clean:
	rm -f *.html
