/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA4
* Graph.c
* A Graph ADT and its associated algorithms, including a Depth First Search Algorithm (DFS).
*/

#include "Graph.h"

// prototypes --------------------------------------------------------------------------
void insertAndSortNeighbor(Graph G, int u, int v);


// structs -----------------------------------------------------------------------------
typedef struct GraphObj {

    List* neighbors;
    int* color;
    int* parent;
    int* discoverTime;
    int* finishTime;
    
    int order;
    int size;
    
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Creates and returns reference to a new Graph object with n vertices and no edges.
Graph newGraph(int n) {
    if (n <= 0) {
        fprintf(stderr, "Graph Error: calling newGraph() with invalid number of vertices\n");
        exit(EXIT_FAILURE);
    }
    
    Graph G = (GraphObj *)malloc(sizeof(GraphObj));
    
    G->order = n;
    G->size = 0;
    
    // initialize GraphObj fields - all arrays should be of size n+1 because index 0 is not used
    G->neighbors = (List *)malloc(sizeof(List)*(n+1));
    G->color = (int *)malloc(sizeof(int)*(n+1));
    G->parent = (int *)malloc(sizeof(int)*(n+1));
    G->discoverTime = (int *)malloc(sizeof(int)*(n+1));
    G->finishTime = (int *)malloc(sizeof(int)*(n+1));
    
    // create the base for neighbors list
    G->neighbors[0] = NULL;
    for(int i=1; i < n+1; i++) {
        G->neighbors[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
    }
    
    return G;
}

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG
// then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        
        // free all lists in the arrays from 1 to n+1
        for(int i=1; i < ((*pG)->order + 1); i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        
        // free all arrays
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discoverTime);
        free((*pG)->finishTime);
        
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
}

// getDiscover()
// Returns the discover time of the vertex.
// Undefined before DFS() is called
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) { // if u is a vertex that does not exist in G
        fprintf(stderr, "Graph Error: calling getDiscover() with an invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discoverTime[u]; // return the parent of vertex u
}

// getFinish()
// Returns the finish time of the vertex.
// Undefined before DFS() is called
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference.\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) { // if u is a vertex that does not exist in G
        fprintf(stderr, "Graph Error: calling getFinish() with an invalid vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finishTime[u]; // return the parent of vertex u
}


// Manipulation procedures ----------------------------------------------------

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
    
    // increment size
    G->size++;
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
    

// Visit()
// Visits the vertex given as the parameter, updating discovery time and finish time fields accordingly.
void Visit(Graph G, int x, int *time, List S) {
    G->discoverTime[x] = ((*time)++);  // update discover time of vertex x
    G->color[x] = GRAY; // x is now gray (discovered but a path btwn discovered & undiscovered vertices)
    
    // go through x's adj list and visit x's undiscovered neighbors
    List neighbors_of_x = G->neighbors[x];
    moveFront(neighbors_of_x);
    while(index(neighbors_of_x) >= 0) {
        int neighbor = get(neighbors_of_x);
        if (G->color[neighbor] == WHITE) {
            G->parent[neighbor] = x;
            Visit(G, neighbor, time, S);
        }
    }
    G->color[x] = BLACK; // x is now discovered
    G->finishTime[x] = ((*time)++); // update finish time of x
    
    prepend(S, x); // add the finished vertex to the top(front) of S
}

// DFS()
// Runs the Depth First Search Algorithm on Graph G
// The order of vertices processed is contained in the List S
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() with NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Graph Error: the first argument given to addArc() isn an invalid List\n");
        exit(EXIT_FAILURE);
    }
    
    // set all colors to white, parents to nil, discover/finish times to undef
    for(int i=1; i < getOrder(G)+1; i++) {  // for each vertex (in smallest to largest order) in G
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
    }
    
    // create time variable
    int time = 0;
    
    // create pointer to time's address
    int* timePtr = &time;
    
    // go through each vertex in the List S and process vertices according to this order
    moveFront(S);
    while(index(S) >= 0) {
        int currVertex = get(S); // get the next currVertex from S
        if (G->color[currVertex] == WHITE) { // if color of currVertex is white, process it through Visit()
            Visit(G, currVertex, timePtr, S);     // give Visit the pointer to time's address
        }
        moveNext(S);
    }
}


// Other operations -----------------------------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G
// The transpose of G is obtained obtained by reversing directions on all edges of G.
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    // Note:
    // To reverse an edge in G
    // For each v in G:
    //     For each neighbor in v.neighbors:
    //         add v to neighbor's adj list in G^T
    
    
    Graph GT = newGraph(getOrder(G));
    
    for (int currVertex=1; currVertex < getOrder(G)+1; currVertex++) {       // for each vertex in G
        List neighborsList = G->neighbors[currVertex];                       // neighborsList of currVertex
        
        // traverse neighborsList, grabbing each neighbor, and add currVertex to its adj list
        moveFront(neighborsList);
        while(index(neighborsList) >= 0) {
            int neighbor = get(neighborsList);
            addArc(GT, neighbor, currVertex); // add currVertex to each neighbor's adj list
            moveNext(neighborsList);
        }
    }
    
    // size of GT is updated from addArc()
    return GT;
}

// copyGraph()
// Returns a reference to a new graph object that is a copy of G
Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    Graph copyG = newGraph(getOrder(G));
    copyG->size = getSize(G);
    
    for (int i=1; i<(getOrder(G)+1); i++) {
        copyG->neighbors[i] = G->neighbors[i];
        copyG->color[i] = G->color[i];
        copyG->parent[i] = G->parent[i];
        copyG->discoverTime[i] = G->parent[i];
        copyG->finishTime[i] = G->parent[i];
    }
    
    return copyG;
}

// printGraph()
// Prints the adjacency List representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    // print out the vertex and its adjacency list
    for (int i = 1; i < (G->order + 1); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->neighbors[i]);
        
        // no new line for last print
        if (i != (G->order + 1)) {
            fprintf(out, "\n");
        }
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
