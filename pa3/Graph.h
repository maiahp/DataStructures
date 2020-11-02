//
//  Graph.h
//  Assignment3
//
//  Created by Maiah Pardo on 8/23/20.
//  Copyright © 2020 maiah. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include "List.h"

#define INF -1 // represents the distance infinity
#define NIL 0  // represents a non-existent parent

#define WHITE 1   // undiscovered
#define GRAY 2    // frontier between discovered and undiscovered vertices
#define BLACK 3   // discovered vertices

#include <stdio.h>

// Exported Type -------------------------------------------------------------
typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Creates and returns reference to a new Graph object with n vertices and no edges.
Graph newGraph(int n);

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of the Graph.
int getOrder(Graph G);

// getSize()
// Returns the size of the Graph.
int getSize(Graph G);

//getSource()
// Returns the source vertex most recently used in the function BFS(),
// or NIL if BFS() has not yet been called.
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if
// BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
// Has the precondition getSource(G) != NIL, so BFS() must be called before getPath()
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);


// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v
// u is added to the adjacency List of v, and v to the adjacency List of u
// These Lists  are maintained in sorted order by increasing labels.
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v
// v is added to teh adjacency List of u (but not u to the adjacency List of v)
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

//BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance,
// parent, and source fields of G accordingly.
void BFS(Graph G, int s);


// Other operations -----------------------------------------------------------

// printGraph()
// Prints the adjacency List representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);


#endif /* Graph_h */
