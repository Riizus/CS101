#-------------------------------------------------------------------------------#
#   Riise Kennard, riakenna@ucsc.edu                                            #
#   CS 101: PA1                                                                 #
#   Makefile for Lex                                                            #
#   Compiles all .java files in the current directory and creates an            #
#   executable jar file called Lex.                                             #
#                                                                               #
#-------------------------------------------------------------------------------#

MAINCLASS  = Lex
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	- checksource $<
	- cid + $<
	$(JAVAC) $<

ci : $(SOURCES)
	- checksource $(SOURCES)
	cid + $(SOURCES)

submit : $(SOURCES)
	submit cmps101-pt.f16 pa1 $(SOURCES)

clean:
	rm -f *.class $(JARFILE)

