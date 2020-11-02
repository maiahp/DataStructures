//
//  Graph.c
//  
//
//  Created by Maiah Pardo on 11/1/20.
//

#include "Graph.h"
#include <stdio.h>

// structs -----------------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
    
    // array of Lists whose ith elem contains the neighbors of vertex i in sorted order (least to greatest)
    // starts at index 1 (no vertex 0)
    List* neighbors;
    
    
    // array of ints whose ith elem is the color of vertex i
    // 0=white, 1=gray, 2=black
    // white is undiscovered, gray is a vertex that has not been fully discovered - a frontier between discovered and undiscovered vertices, black is discovered
    int* color;
    
    // array of ints whose ith elem is the parent of vertex i
    int* parent;
    
    // array of ints whose ith elem is the distance from the (most recent) source to vertex i
    int* distance;
    
    // num of vertices, given as n in constructor
    int order;
    
    // num of edges, initially 0
    int size;
    
    // contains the vertex which was used in the last call to BFS()
    // it is initially NIL until BFS() called with a source
    int mostRecentSource;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Creates and returns reference to a new Graph object with n vertices and no edges.
Graph newGraph(int n) {
    
    Graph G = (GraphObj *)malloc(sizeof(GraphObj)); // create space for GraphObj
    
    G->order = n; // num of vertices
    G->size = 0;
    G->mostRecentSource = NIL; // will hold the vertex that BFS() was called with last
    
    // initialize GraphObj fields - all arrays should be of size n+1 because index 0 is not used
    G->neighbors = (List *)malloc(sizeof(List)*(n+1));
    G->color = (int *)malloc(sizeof(int)*(n+1));
    G->parent = (int *)malloc(sizeof(int)*(n+1));
    G->distance = (int *)malloc(sizeof(int)*(n+1));
    
    return G;

}

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of the Graph.
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize()
// Returns the size of the Graph.
int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

//getSource()
// Returns the source vertex most recently used in the function BFS(),
// or NIL if BFS() has not yet been called.
int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    return G->mostRecentSource;
}

// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) { // if u is a vertex that does not exist in G
        fprintf(stderr, "Graph Error: calling getParent() with an invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent; // return the parent of vertex u
                         // result will be NIL if BFS hasn't been called
 }

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if
// BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) { // if u is a vertex that does not exist in G
        fprintf(stderr, "Graph Error: calling getDist() with an invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->distance; // return the distance of vertex u
                        // result will be NIL if BFS() hasn't been called or if the vertex is not reachable from the mostRecentSource
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
// Has the precondition getSource(G) != NIL, so BFS() must be called before getPath()
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
    if (G == NULL) {
         fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference.\n");
         exit(EXIT_FAILURE);
     }
    if (u < 1 || u > getOrder(G)) { // if u is a vertex that does not exist in G
        fprintf(stderr, "Graph Error: calling getPath() with invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    // if there is no mostRecentSource
    // then BFS() has not yet been called
    if (G->mostRecentSource == NIL) {
        printf("Graph Error: calling getPath() before BFS() has been called\n");
        exit(EXIT_FAILURE);
    }
    
    
    // do something
    
}


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

