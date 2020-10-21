#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -g -std=c11 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -g -std=c11 -Wall -c Lex.c

ListClient.o : ListClient.c List.h
	gcc -g -std=c11 -Wall -c ListClient.c

ListClient: ListClient.o List.o
	gcc -g -std=c11 -Wall -o ListClient ListClient.o List.o

List.o : List.c List.h
	gcc -g -std=c11 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkClient : 
	valgrind --show-leak-kinds=all --leak-check=full ListClient

checkLex :
	valgrind --show-leak-kinds=all --leak-check=full Lex in3.txt out3.txt
