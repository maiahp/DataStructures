/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA4
* FindComponents.c
* Client module for the Graph ADT
*/

#include <stdio.h>
#include "Graph.h"

int main(int argc, const char * argv[]) {
    printf("Graph Testing\n\n");
    
    int n = 10; // order
    Graph G = newGraph(n);
    List S = newList();
    
    printf("Creating new Graph G.\n");
    printf("Order of G is: %d\n", n);
    
    // create a list of vertices up to order n
    for (int i=1; i<=n; i++) {
        append(S, i);
    }
    
    
    
    
    
    return 0;
}
