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

#define MAX_LEN 300

// prototypes
int getNumLinesInFile(FILE*);
void insertionSort(char array[][MAX_LEN], List);

int main(int argc, const char * argv[]) {
    FILE *in, *out;
    int linecount; // the number of lines in the infile

    // check command line for correct number of arguments
    // argv[0] = Lex, argv[1] = in file, argv[2] = out file
    // Lex.c will take two command line args: Lex <infile> <outfile>
    
    /*
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
     */
    
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
    
    // count the number of lines 'linecount' in the input file
    linecount = getNumLinesInFile(in);
    
    // must read the file again to grab each line as a string - use rewind(fptr);
    rewind(in);
    
    // define the size of the array that will store the strings
    char array[linecount][MAX_LEN]; //row = num of lines, col = max characters in a line
    
    // read in the lines of the file as strings, placing them into the array
    char *c; // will store the line
    c = (char *)malloc(MAX_LEN);
    int i = 0; // will be used to increment array's index and insert into index
    
    while(fgets(c, MAX_LEN, in) != NULL) {
        int stringLen = 0;
        stringLen = (int)strlen(c);
        
        if (c[stringLen-1] == '\n') { // if last character of the string is \n
            c[stringLen-1] = '\0'; // replace it with null terminator character
        } else {
            c[stringLen] = '\0'; // add a null terminator as last character of string
        }
        
        strcpy(array[i], c); // must use strcpy or the memory inside array will change with each update of c
        
        printf("array[%d] %s\n", i, array[i]); // printing array contents
        i++;
    }
    
    // close file and free c
    fclose(in);
    free(c);
    
    // Create a List and insert in sorted order into List (using insertion sort)
    List L = newList();
    
    
    
    
    

}

// getNumLinesInFile()
// Takes in a file pointer and returns the number of lines in the file
int getNumLinesInFile(FILE *fptr) {
    int linecount = 0; // number of lines in file
    char *c; // string input is stored at the memory location referened by pointer c
    c = (char *)malloc(MAX_LEN); // c is an array of size 300 on the heap
                                // malloc returns a pointer
    
    while (fgets(c, MAX_LEN, fptr) != NULL) { // while a line exists in file
        linecount++; // increment linecount
    }
    free(c);
    return linecount;
}

// insertionSort()
// Takes in an array and List and inserts each array item (a string)
// into the List in sorted order
void insertionSort(char array[][MAX_LEN], List L);
