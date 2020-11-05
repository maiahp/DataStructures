/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA3
* GraphTest.c
* Test module for the Graph ADT
*/

#include <stdio.h>
#include "Graph.h"


int main() {
    printf("Graph Test\n\n");
    
    printf("Creating a new Directed Graph G of order 25.\n");
    Graph G = newGraph(25);
    List path = newList();
    
    fprintf(stdout, "Inserting Edges.\n");
    addEdge(G, 1, 1);
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 1, 6);
    addEdge(G, 1, 10);
    addEdge(G, 1, 4);
    addEdge(G, 2, 6);
    addEdge(G, 3, 8);
    addEdge(G, 3, 5);
    addEdge(G, 5, 2);
    addEdge(G, 6, 2);
    addEdge(G, 5, 4);
    addEdge(G, 4, 12);
    addEdge(G, 10, 11);
    addEdge(G, 7, 9);
    addEdge(G, 12, 16);
    addEdge(G, 12, 17);
    addEdge(G, 12, 19);
    addEdge(G, 12, 11);
    addEdge(G, 12, 5);
    addEdge(G, 12, 4);
    addEdge(G, 12, 22);
    addEdge(G, 12, 25);
    addEdge(G, 25, 24);
    addEdge(G, 25, 1);
    addEdge(G, 2, 20);
    addEdge(G, 20, 10);
    addEdge(G, 11, 15);
    addEdge(G, 12, 21);
    addEdge(G, 10, 7);
    addEdge(G, 13, 25);
    
    // print G and its information
    fprintf(stdout, "\nG's order is: %d", getOrder(G));
    fprintf(stdout, "\nG's size is: %d", getSize(G));
    fprintf(stdout, "\n\nGraph G is: \n");
    printGraph(stdout, G);
    fprintf(stdout, "\n\n\n");
    
    // call BFS with 4 as source
    fprintf(stdout, "Calling BFS on G with 4 as source.\n");
    BFS(G, 4);
    
    fprintf(stdout, "\nG's source is currently: %d", getSource(G));
    fprintf(stdout, "\nThe distance from %d to %d is %d", 4, 1, getDist(G, 1));
    fprintf(stdout, "\nA shortest %d-%d path is: ", 4, 1);
    getPath(path, G, 1);
    printList(stdout, path);
    
    // call getParent() on each vertex in the path list
    fprintf(stdout, "\n\nThe parent of each Vertex in the path %d-%d", 4, 1);
    moveFront(path);
    while(index(path) >= 0) {
        int currVertex = get(path);
        fprintf(stdout, "\n\n%d's parent is: %d", currVertex, getParent(G, currVertex));
        moveNext(path);
    }
    clear(path);
    fprintf(stdout, "\n\n");
    
    // call BFS with 7 as source
    fprintf(stdout, "\nCalling BFS on G with 7 as source.\n");
    BFS(G, 7);
    
    fprintf(stdout, "\nG's source is currently: %d", getSource(G));
    fprintf(stdout, "\nThe distance from %d to %d is %d", 7, 22, getDist(G, 22));
    fprintf(stdout, "\nA shortest %d-%d path is: ", 7, 22);
    getPath(path, G, 22);
    printList(stdout, path);
   
    
    // call getParent() on each vertex in the path list
    fprintf(stdout, "\n\nThe parent of each Vertex in the path %d-%d", 7, 22);
    moveFront(path);
    while(index(path) >= 0) {
        int currVertex = get(path);
        fprintf(stdout, "\n\n%d's parent is: %d", currVertex, getParent(G, currVertex));
        moveNext(path);
    }

    clear(path);
    fprintf(stdout, "\n");

    
    // Test makeNull()
    fprintf(stdout, "\n\nCalling makeNull().\nGraph G is now: \n");
    makeNull(G);
    printGraph(stdout, G);
    
    freeGraph(&G);
    
    
    
    // Creating a Directed Graph D
    Graph D = newGraph(25);
    
    fprintf(stdout, "\n\nCreating a Directed Graph D:");
    fprintf(stdout, "\nAdding Arcs to D.\n");
    
    // Testing addArc()
    
    addArc(D, 1, 6);
    addArc(D, 1, 7);
    addArc(D, 1, 8);
    addArc(D, 1, 9);
    addArc(D, 1, 10);
    addArc(D, 1, 2);
    addArc(D, 2, 6);
    addArc(D, 3, 1);
    addArc(D, 3, 4);
    addArc(D, 5, 2);
    addArc(D, 6, 2);
    addArc(D, 5, 4);
    addArc(D, 4, 5);
    addArc(D, 10, 11);
    addArc(D, 7, 9);
    addArc(D, 12, 16);
    addArc(D, 12, 17);
    addArc(D, 12, 19);
    addArc(D, 12, 11);
    addArc(D, 12, 5);
    addArc(D, 12, 4);
    addArc(D, 12, 22);
    addArc(D, 12, 25);
    addArc(D, 25, 24);
    addArc(D, 25, 1);
    addArc(D, 2, 20);
    addArc(D, 20, 10);
    addArc(D, 11, 15);
    addArc(D, 12, 21);
    addArc(D, 10, 7);
    addArc(D, 13, 25);
    
    fprintf(stdout, "\nD's order is: %d", getOrder(D));
    fprintf(stdout, "\nD's size is: %d", getSize(D));
    fprintf(stdout, "\n\nGraph D is: \n");
    printGraph(stdout, D);
    fprintf(stdout, "\n\n");
    
    // call BFS with 4 as source
    fprintf(stdout, "Calling BFS on D with 1 as source.\n");
    BFS(D, 1);
    
    fprintf(stdout, "\nD's source is currently: %d", getSource(D));
    fprintf(stdout, "\nThe distance from %d to %d is %d", 1, 15, getDist(D, 15));
    fprintf(stdout, "\nA shortest %d-%d path is: ", 1, 15);
    getPath(path, D, 15);
    printList(stdout, path);
    
    // call getParent() on each vertex in the path list
    fprintf(stdout, "\n\nThe parent of each Vertex in the path %d-%d", 1, 15);
    moveFront(path);
    while(index(path) >= 0) {
        int currVertex = get(path);
        fprintf(stdout, "\n\n%d's parent is: %d", currVertex, getParent(D, currVertex));
        moveNext(path);
    }

    clear(path);
    fprintf(stdout, "\n\n");
    
    // call BFS with 7 as source
    fprintf(stdout, "\nCalling BFS on D with 12 as source.\n");
    BFS(D, 12);
    
    fprintf(stdout, "\nD's source is currently: %d", getSource(D));
    fprintf(stdout, "\nThe distance from %d to %d is %d", 12, 5, getDist(D, 5));
    fprintf(stdout, "\nA shortest %d-%d path is: ", 12, 5);
    getPath(path, D, 5);
    printList(stdout, path);
    
    // call getParent() on each vertex in the path list
    fprintf(stdout, "\n\nThe parent of each Vertex in the path %d-%d", 12, 5);
    moveFront(path);
    while(index(path) >= 0) {
        int currVertex = get(path);
        fprintf(stdout, "\n\n%d's parent is: %d", currVertex, getParent(D, currVertex));
        moveNext(path);
    }

    clear(path);
    fprintf(stdout,"\n\n");

    freeList(&path);
    freeGraph(&D);
    
    fprintf(stdout, "\n\nDone.\n");
    
    return 0;
}

