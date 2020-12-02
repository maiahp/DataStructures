/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Lex.c
* Client module for the Dictionary ADT
*/

#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#define MAX_LEN 300


int main(int argc, const char * argv[]) {

    FILE *in, *out;

    // check command line for correct number of arguments
    // argv[0] = Lex, argv[1] = in file, argv[2] = out file
    
    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s <input file> <outputfile>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing
    in = fopen(argv[1], "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    /*
    // hardcoding the filename (testing):
    in = fopen("in1.txt", "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", "input.txt"); // print error message to stderr
        exit(1);
    }
    out = fopen("out1.txt", "w");
    if(out==NULL) {
        printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
        exit(1);
    }
    // end (testing)
    */
    
    // grab each line from file and insert key, val into dict
    // line = key
    // line number = val
    
    Dictionary D = newDictionary(0); // create a non-unique dictionary
    int line_count = 1; // start at 1 so first line is line 1
    char *line = NULL;
    line = (char *)malloc(MAX_LEN);
    
    while(fgets(line, MAX_LEN, in) != NULL) {
        int line_length = (int)strlen(line);
        
        if (line[line_length-1] == '\n') {  // if last char of line is '\n'
            line[line_length-1] = '\0'; // replace '\n' with null terminator
        } else {  // if no '\n' add a null terminator at end of line
            line[line_length] = '\0';
        }
        
        insert(D, line, line_count); // insert key = line, val = line_count into D
        line_count++;
    }
    // when getline is finished, it returns 0 (false) and while exits
    
    fclose(in);
    free(line);
    
    // print out the keys in order
    int numKeys = size(D);
    beginForward(D);
    
    for(int i=0; i < numKeys; i++) {
        fprintf(out, "%s", (char*)currentKey(D));
        if (i != numKeys-1) {   // if not at last print
            fprintf(out, "\n");
        }
        next(D);
    }
    
    freeDictionary(&D);
    fclose(out);
    
    return 0;
}

