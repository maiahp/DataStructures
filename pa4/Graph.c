/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA4
* Graph.h
* A Graph ADT and its associated algorithms, including a Depth First Search Algorithm (DFS).
*/

#include "Graph.h"

// structs -----------------------------------------------------------------------------
typedef struct GraphObj {
    
} GraphObj;


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

// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of the vertex.
// Undefined before DFS() is called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of the vertex.
// Undefined before DFS() is called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);


// Manipulation procedures ----------------------------------------------------

// addArc()
// Inserts a new directed edge from u to v
// v is added to teh adjacency List of u (but not u to the adjacency List of v)
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

// addEdge()
// Inserts a new edge joining u to v
// u is added to the adjacency List of v, and v to the adjacency List of u
// These Lists  are maintained in sorted order by increasing labels.
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);
    
// DFS()
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S);


// Other operations -----------------------------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G
// The transpose of G is obtained obtained by reversing directions on all edges of G.
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new graph object that is a copy of G
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency List representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);
