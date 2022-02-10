/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA4
* FindComponents.c
* Client module for the Graph ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include"List.h"


int main(int argc, const char * argv[]) {
    FILE *in, *out;

    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s <input file> <outputfile>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing
    in = fopen(argv[1], "r");
    if(in==NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    

    int n;
    List S = newList();
    Graph G;
    Graph GT = NULL;
    
    // Read the first line of the input file
    fscanf(in, "%d\n", &n);
    
    // Create G with n vertices
    G = newGraph(n);
    
    // Input file, terminated by "0 0", consists of "x y" pairs of vertices
    // Each "x y" pair is a source(x) to destination(y) pair
    // Add an arc (a directed edge) between x and y
    int source, dest;
    while(1) {
        fscanf(in, "%d %d\n", &source, &dest);
        
        if (source == 0 && dest == 0) { // finished reading file
            break;
        } else { // add an arc between source and dest
            addArc(G, source, dest);
        }
    }
    
    // Print G
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n\n");
    
    // note: To find strongly connected components of G
    // call DFS(G, S). S is the order of processing vertices, S = 1,2,3,4,...,n
    //      S will now have vertices in order of decreasing finish times
    // compute transpose of G: G^T. This reverses all directed edges in G
    // call DFS(G^T, S) where S has vertices in order of decreasing finish times from first call to DFS
    //      S will now have groups of scc's: a vertice with nil parent down to the vertice before the next nil parent
    //      The bottom scc group in S is the first to be printed
    //      Read S from bottom up: to first nil parent, then down to next nil parent
    
    
    // Fill S with the order of vertices to discover in G
    // S should first have the order 1,2,3,4,....,n
    for(int i=1; i < (getOrder(G)+1); i++) {
        append(S, i);
    }
    
    // call DFS on G
    DFS(G, S);
    
    // S now contains vertices in order of decreasing finish times
    
    // compute transpose of G
    GT = transpose(G);
    
    // call DFS(G^T) and process vertices in order of decreasing finish times of first DFS call (already contained in S)
    DFS(GT, S);
    
    // Now S contains strongly connected components
    
    // The number of SCC's are the number of vertices with nil parents in transpose of G
    int num_components = 0;
    int vertex;
    moveFront(S);
    while(index(S) >= 0) {
        vertex = get(S);
        if (getParent(GT, vertex) == NIL) {
            num_components++;
        }
        moveNext(S);
    }
    
    fprintf(out, "G contains %d strongly connected components:", num_components);
    
    // Read S from bottom up
    int count = 1; // counts up to the number of components
    int cursorPos = 0;
    moveBack(S);
    while(index(S) >= 0) {
        vertex = get(S);
        if (getParent(GT, vertex) == NIL) { // if parent of current vertex is nil, read down to grab the entire scc
            fprintf(out, "\nComponent %d: ", count);
            count++;
            
            cursorPos = index(S); // save cursor position
            
            fprintf(out, "%d", get(S)); // print the current vertex with a nil parent
            moveNext(S); // move to next element
            
            // move down the list S
            while(index(S) >= 0) { // while not at end of list
                int currVertex = get(S);
                int parent = getParent(GT, currVertex);
                
                //fprintf(stdout, "currVertex: %d, parent: %d\n", currVertex, parent);
            
                if (parent != NIL) { // while parent of curr vertex is not NIL
                    fprintf(out, " %d", currVertex); // print out the strong component vertices
                } else { // parent of curr vertex is NIL
                    break;
                }
                moveNext(S);
            }
            // when while exits, finished printing strong component vertices
            
            // restore cursor to original position in S
            moveBack(S);
            while(index(S) >= 0) {
                if (index(S) == cursorPos) {
                    break;
                }
                movePrev(S);
            }
        }
        movePrev(S); // move cursor to next position in S
    }
   
    
    
    fclose(in);
    fclose(out);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&GT);
        
    return 0;
}

