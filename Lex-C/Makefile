#-------------------------------------------------------------------------------#
#   Riise Kennard, riakenna@ucsc.edu                                            #
#   CS 101: PA2                                                                 #
#   Makefile for Lex.C                                                          #
#   Compiles files in the current directory and creates a file called Lex.      #
#                                                                               #
#-------------------------------------------------------------------------------#

SOURCES = Lex.c List.c List.h Makefile README ListClient.c

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
    
submit : $(SOURCES)
	submit cmps101-pt.f16 pa2 $(SOURCES)

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o