/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA3
* Graph.c
* A Graph ADT and its associated algorithms, including a Breadth First Search Algorithm (BFS) from a given source vertex.
*/

#include <stdio.h>
#include "Graph.h"

// prototypes --------------------------------------------------------------------------
void insertAndSortNeighbor(Graph G, int u, int v);

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
    
    // n must be 1 or greater to be valid
    if (n <= 0) {
        fprintf(stderr, "Graph Error: calling newGraph with invalid number of vertices\n");
        exit(EXIT_FAILURE);
    }
    
    Graph G = (GraphObj *)malloc(sizeof(GraphObj)); // create space for GraphObj
    
    G->order = n; // num of vertices
    G->size = 0;
    G->mostRecentSource = NIL; // will hold the vertex that BFS() was called with last
    
    // initialize GraphObj fields - all arrays should be of size n+1 because index 0 is not used
    G->neighbors = (List *)malloc(sizeof(List)*(n+1));
    G->color = (int *)malloc(sizeof(int)*(n+1));
    G->parent = (int *)malloc(sizeof(int)*(n+1));
    G->distance = (int *)malloc(sizeof(int)*(n+1));
    
    // note:
    // set all elements of G: (the 0th place is empty for all elems)
    // each vertex's neighbors contains a new, empty list
    // each vertex's color is white
    // each vertex's parent is NIL
    // each vertex's distance is INF
    
    for(int i=0; i < n+1; i++) {
        if (i == 0) { // for the 0th place of all elements (there is no vertex 0)
            G->neighbors[0] = NULL;
            // don't set the other elements
        } else {
            G->neighbors[i] = newList();
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }
    
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        
        // free all lists in the arrays from 0 to n+1
        for(int i=0; i < ((*pG)->order + 1); i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        
        // free all arrays
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        
        // free the graph pointer
        free(*pG);
        *pG = NULL;
    }
}


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
    return G->parent[u]; // return the parent of vertex u
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
    return G->distance[u]; // return the distance of vertex u
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
        fprintf(stderr, "Graph Error: calling getPath() before BFS() has been called\n");
        exit(EXIT_FAILURE);
    }
    
    int source = G->mostRecentSource;
    
    // if u is the source, then the list contains just the source
    if (u == source) {
        append(L, source);
    } else if (G->parent[u] == NIL) {
        // if the parent of u is NIL
        // then there is no path from source to u
        append(L, NIL);
    } else {
        // there exists a path between the source and u
        getPath(L, G, G->parent[u]); // recursive call with u's parent
        append(L, u); // add vertices to List from the source down to u
    }
}


// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    // restore G to its original state:
    // all neighbors are empty lists
    // all colors are white
    // all parents are NIL
    // all distances are INF
    
    for (int i=0; i < G->order+1; i++) {
        if (i == 0) { // index 0, there is no List or elements defined
            G->neighbors[0] = NULL;
        } else { // for all other indices (vertices)
            clear(G->neighbors[i]); // clear the neighbors List
            
            // even though G is NULL, it has already been declared to be of size n
            // this does not change, so its not necessary to free all other elements to prepare for a new size - size n doesn't change
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }
    
    // restore size and most recent source to original values
    G->size = 0;
    G->mostRecentSource = NIL;
}

// addEdge()
// Inserts a new edge joining u to v
// u is added to the adjacency List of v, and v to the adjacency List of u
// These Lists  are maintained in sorted order by increasing labels.
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    // an undirected edge is added from u to v
    // so v is added to u's neighbors list and u is added to v's in sorted order (smallest to largest)
    
    // v is added to u's neighbors list
    insertAndSortNeighbor(G, u, v);
    
    // u is added to v's neighbors list
    insertAndSortNeighbor(G, v, u);
    
    // increment the number of edges in G (size)
    G->size++;
}

// addArc()
// Inserts a new directed edge from u to v
// v is added to the adjacency List of u (but not u to the adjacency List of v)
// Pre: the two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: the first argument given to addArc() isn an invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: the second argument given to addArc() is an invalid vertex\n");
        exit(EXIT_FAILURE);
    }

    // a directed edge is added from u to v
    // so v is added to u's neighbors list in sorted order (smallest to largest)
    insertAndSortNeighbor(G, u, v);
    
    // don't increment size of G unless a directed edge exists from u to v AND from v to u
    // size is the number of edges in G
    // an edge is an undirected line between two vertices and an arc is a directed edge
    List vNeighbors = G->neighbors[v];
    moveFront(vNeighbors);
    while(index(vNeighbors) >= 0) {
        int currVertex = get(vNeighbors);
        if (currVertex == u) { // if u exists in v's neighbors list
            G->size++; // increment the number of edges in G
            break;
        }
        moveNext(vNeighbors);
    }
}


//BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance,
// parent, and source fields of G accordingly.
// Pre: 1 <= s <= getOrder(G)
void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling BFS() with invalid source\n");
        exit(EXIT_FAILURE);
    }
    
    /* Teacher's Pseudo-Code
     BFS(G,s)
        for x in V(G)-{s}
             color[x] = white
             d[x] = inf
             p[x] = nil
        color[s] = gray       // discover the source s
        d[s] = 0
        p[s] = nil
        Q = { }              // construct a new empty queue
        Enqueue(Q,s)
        while Q != { }       // while Q is not empty
             x = Dequeue(Q)
             for y in adj[x]
                  if color[y] == white         // y is undiscovered
                       color[y] = gray         // discover y
                       d[y] = d[x]+1
                       p[y] = x
                       Enqueue(Q,y)
             color[x] = black                  // finish x
     */
    
    
    // reset color, parent, and distance arrays for each vertex
    for (int i=0; i < G->order; i++) {
        if (i != 0) { // ignore the 0th elem
            G->color[i] = WHITE;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }
    
    // discover the source s, set its distance and parent as NIL
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    
    // construct an empty Queue (List)
    List Q = newList();
    
    // add the source to Q
    append(Q, s);
    
    while (length(Q) != 0) {   // while Q is not empty
        
        // Dequeueing
        int currVertex = front(Q); // currVertex is the front element of Q
        deleteFront(Q); // delete the front element
        
        // search currVertex's neighbors list and add to Q
        List currVertexNeighbors = G->neighbors[currVertex]; // neighbors of currVertex
        moveFront(currVertexNeighbors);
        while (index(currVertexNeighbors) >= 0) { // traversing currNeighbors List
            int currNeighbor = get(currVertexNeighbors); // current neighbor
            
            if (G->color[currNeighbor] == WHITE) { // if curr neighbor is undiscovered
                G->color[currNeighbor] = GRAY; // discover the neighbor
                G->parent[currNeighbor] = currVertex; // parent of currNeighbor is currVertex
                G->distance[currNeighbor] = (G->distance[currVertex] + 1); // distance is the distance of the parent + 1
                
                // enqueue currNeighbor into Q (put in back of Q)
                append(Q, currNeighbor);
            }
            
            // currVertex's neighbors have now all been put into Q (discovered)
            // so currVertex is now fully discovered
            G->color[currVertex] = BLACK;

            moveNext(currVertexNeighbors); // go to next neighbor
        }
    }
    
    G->mostRecentSource = s; // set the most recent source of G
    
    freeList(&Q);

}


// Other operations -----------------------------------------------------------

// printGraph()
// Prints the adjacency List representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    // print out the vertex and its adjacency list
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
        fprintf(out, "\n");
    }
}

// insertAndSortNeighbor()
// Inserts a vertex v into u's Neighbor List in sorted (least to greatest) order
void insertAndSortNeighbor(Graph G, int u, int v) {
    
    // add v to u's neighbors list
    List uNeighbors = G->neighbors[u];
    
    if (length(uNeighbors) == 0) { // uNeighbors is empty
        append(uNeighbors, v); // append the first neighbor
        
    } else { // if uNeighbors has other elements in it
        moveFront(uNeighbors);
        
        int isDuplicate = 0; // duplicate flag
        int hasInserted = 0; // elemenent has been inserted into list flag
        
        while(index(uNeighbors) >= 0) {
            int currElem = get(uNeighbors);
            if (v > currElem) { // v is bigger than currElem
                moveNext(uNeighbors); // move to next element
                
            } else if (v < currElem) { // v is smaller than currElem
                insertBefore(uNeighbors, v); // insert v before currElem
                hasInserted = 1;
                break;
                
            } else if (currElem == v) { // if v is equal to a current elem
                isDuplicate = 1; // do nothing, there should be no duplicate directed edges
                break;
            }
        }
        // if while exits and v is not a duplicate element in uNeighbors List
        // add v to the back of the list, it is the largest element
        
        if (isDuplicate == 0 && hasInserted == 0) {
            append(uNeighbors, v);
        }
    }
}
