#-------------------------------------------------------------------------------#
#   Riise Kennard, riakenna@ucsc.edu                                            #
#   CS 101: PA2                                                                 #
#   Makefile for Lex.C                                                          #
#   Compiles files in the current directory and creates a file called Lex.      #
#                                                                               #
#-------------------------------------------------------------------------------#


BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)
	- cid $(BASE_SOURCES) $(HEADERS) $<

clean :
	$(REMOVE) FindComponents GraphClient FindComponents.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in3 junk3

checkClient : GraphTest
	$(MEMCHECK) GraphTest

submit : 
	submit cmps101-pt.f16 pa5 $(BASE_SOURCES) $(HEADERS) GraphTest.c FindComponents.c Makefile README