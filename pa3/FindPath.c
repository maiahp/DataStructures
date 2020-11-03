/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA3
* Arithmetic.c
* Client module for the Graph ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, const char * argv[]) {
    FILE *in, *out;

    /*
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
   */
    
    // hardcoding the filename (testing):
    in = fopen("in1.txt", "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", "in1.txt"); // print error message to stderr
        exit(1);
    }
    out = fopen("out1.txt", "w");
    if(out==NULL) {
        printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
        exit(1);
    }
    // end (testing)
    
    Graph G;
    int n;
    
    // First line of text file is the number of vertices n
    fscanf(in, "%d\n", &n); // %d\n means ignore the new line character
     
    // Create G with n vertices
    G = newGraph(n);
    
    // First part of the input file, terminated by "0 0" consists of all edges in the graph
    // Each "x y" pair is a source(x)-destination(y) pair
    
    // Print out the Adjacency list of the Graph to the output file
    
    // Second part of the input file, terminated by "0 0" consists of "x y" source-desination pairs in range 1-n where: BFS will be called with source x, then print out the path between x and y
    // The distance from 1 to 5 is 2
    // A shortest 1-5 path is: 1 2 5
    
    // If Path DNE:
    // The distance from 1 to 7 is infinity
    // No 1-7 path exists
    

     
    
    
    
}
