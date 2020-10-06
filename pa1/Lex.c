/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA1
* Lex.c
* Client module for the List ADT
*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

int main(int argc, const char * argv[]) {
    FILE *in, *out;
    int linecount; // num lines in file
    int count; // counter to count up to num lines in file

    // check command line for correct number of arguments
    //argv[0] = Lex, argv[1] = in file, argv[2] = out file
    // Lex.c will take two command line args: Lex <infile> <outfile>
     
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <outputfile>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    
    out = fopen(argv[2], "w");
    if (out == NULL){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    // count the number of lines 'n' in the input file
    
    // create a string array of length 'n' and read in the lines of the file as strings, placing them into the array
    // then use insertion sort to insert the string to its correct placement inside the List
    
    
    

}
