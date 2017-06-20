# Makefile for CMPS 101 
# pa3

MAINCLASS = Sparse
JAVAC = javac
JAVASRC = $(wildcard *.java)
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE = $(MAINCLASS)
SOURCES = $(JAVASRC) Makefile README

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<
    
submit : $(SOURCES)
	submit cmps101-pt.f16 pa3 $(SOURCES)

clean:
	rm -f *.class $(JARFILE) ListTest MatrixTest

