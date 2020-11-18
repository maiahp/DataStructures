/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA4
* GraphTest.c
* Test module for the Graph ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


int main() {
    printf("Graph Testing\n\n");
    
    int n = 10; // order
    Graph G = newGraph(n);
    List S = newList();
    
    printf("Creating new Graph G.\n");
    printf("Order of G is: %d\n", n);
    printf("Size of G is: %d\n", getSize(G));
    
    // create a list S of vertices up to order n
    for (int i=1; i<=n; i++) {
        append(S, i);
    }
    
    addArc(G, 1, 10);
    addArc(G, 10, 4);
    addArc(G, 4, 1);
    addArc(G, 1, 7);
    addArc(G, 7, 8);
    addArc(G, 8, 9);
    addArc(G, 9, 5);
    addArc(G, 5, 2);
    addArc(G, 2, 5);
    addArc(G, 2, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 5);
    addArc(G, 5, 2);
    addArc(G, 5, 6);
    addEdge(G, 1, 3);
    addEdge(G, 5, 10);
    addEdge(G, 3, 10);
    addEdge(G, 3, 5);
    
    
    printf("Graph G's adjacency list representation:\n");
    printGraph(stdout, G);
    printf("\n\n");
    
    printf("Calling copyGraph() on G:\n");
    Graph copyG = copyGraph(G);
    printf("Graph copyG's adjacency list representation:\n");
    printGraph(stdout, copyG);
    printf("Graph copyG has size: %d\n", getSize(copyG));
    printf("Graph G has size: %d\n", getSize(G));
    printf("\n\n");
    
    // Call DFS()
    printf("First call to DFS() on G.\n");
    DFS(G, S);
    
    // call Transpose()
    printf("Calling transpose() on G.\n\n");
    Graph GT;
    GT = transpose(G);
    printf("Transpose of G adjacency list representation:\n");
    printGraph(stdout, GT);
    printf("\n");
    
    printf("Second call to DFS() with Transpose of G.\n\n");
    // run DFS on transpose of G
    DFS(GT, S);
    // S now contains the strongly connected components of G
    printf("Transpose of G now contains strongly connected components of G.\n");
    
    
    
    
    // Testing getParent(), getDiscover(), getFinish()
    printf("\n\nList S is: ");
    printList(stdout, S);
     
    printf("\n\nGraph G^T data:");
    moveFront(S);
    while(index(S) >= 0) {
        int currV = get(S);
        int currParent = getParent(GT, currV);
        if (currParent == 0) {
            printf("\nvertex %d: parent is NIL, discover time is %d, finish time is %d", currV, getDiscover(GT, currV), getFinish(GT, currV));
        } else {
            printf("\nvertex %d: parentis %d, discover time is %d, finish time is %d", currV, currParent, getDiscover(GT, currV), getFinish(GT, currV));
        }
        moveNext(S);
    }

    
    
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
    
    printf("\n\nG contains %d strongly connected components:", num_components);
    
    // Read S from bottom up
    int count = 1; // counts up to the number of components
    int cursorPos = 0;
    moveBack(S);
    while(index(S) >= 0) {
        vertex = get(S);
        if (getParent(GT, vertex) == NIL) { // if parent of current vertex is nil, read down to grab the entire scc
            printf("\nComponent %d: ", count);
            count++;
            
            cursorPos = index(S); // save cursor position
            
            printf("%d", get(S)); // print the current vertex with a nil parent
            moveNext(S); // move to next element
            
            // move down the list S
            while(index(S) >= 0) { // while not at end of list
                int currVertex = get(S);
                int parent = getParent(GT, currVertex);
                
                //fprintf(stdout, "currVertex: %d, parent: %d\n", currVertex, parent);
            
                if (parent != NIL) { // while parent of curr vertex is not NIL
                    printf(" %d", currVertex); // print out the strong component vertices
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

    
    printf("\n\n\nDone.\n");
    
    freeGraph(&G);
    freeGraph(&copyG);
    freeGraph(&GT);
    freeList(&S);
  
}
