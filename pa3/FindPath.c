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
     */
    
    Graph G = newGraph(5);
    
    // This project consists of an undirected graph
    // Only have to use addEdge() and not addArc() - ???
    
    addEdge(G, 1, 5);
    addEdge(G, 2, 3);
    addEdge(G, 3, 2);
    addEdge(G, 4, 5);
    addEdge(G, 2, 1);
    
    printGraph(stdout, G);

    
}
