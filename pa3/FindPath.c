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
     
    
    int n;
    
    // First line of text file is the number of vertices n
    fscanf(in, "%d\n", &n); // %d\n means ignore the new line character
     
    // Create G with n vertices
    Graph G = newGraph(n);
    
    // First part of the input file, terminated by "0 0" consists of all edges in the graph
    // Each "x y" pair is a source(x)-destination(y) pair
    int source, dest;
    while(1) {
        fscanf(in, "%d %d\n", &source, &dest); // grab source and dest from the line

        if (source == 0 && dest == 0) { // if source and dest are grabbed from the "0 0" line
            break; // do nothing with the "0 0" data
        } else {
            // add an undirected edge between source and dest to the Graph
            addEdge(G, source, dest);
        }
    }
    
    // Print out the Adjacency list of the Graph to the output file
    printGraph(out, G);

    
    // Second part of the input file, terminated by "0 0" consists of "x y" source-desination pairs in range 1-n where: BFS will be called with source x, then print out the path between x and y
    
    List L = newList(); // will hold the path from source to dest
    while(1) {
        fscanf(in, "%d %d\n", &source, &dest); // grab source and dest from the line
        
        if (source == 0 && dest == 0) { // if source and dest are grabbed from the "0 0" line
            break; // do nothing with the "0 0" data
        } else {
            BFS(G, source); // call BFS using the source
            getPath(L, G, dest); // path is saved in L
            
            // print out the path
            fprintf(out, "\nThe distance from %d to %d is ", source, dest);
            
            moveFront(L);
            if (get(L) == NIL) { // If NIL is in L, then no path exists
                fprintf(out, "infinity");
                fprintf(out, "\n");
                fprintf(out, "No 1-7 path exists");
                fprintf(out, "\n");
                
            } else { // there is a path to print
                fprintf(out, "%d", length(L)-1);
                fprintf(out, "\n");
                fprintf(out, "A shortest %d-%d path is: ", source, dest);
                printList(out, L);
                fprintf(out, "\n");
            }
            
            clear(L); // clear the List
        }
    }
    
    fclose(in);
    fclose(out);
    
    freeList(&L);
    freeGraph(&G);
    
    return 0;
}

