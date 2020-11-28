/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA5
* List.cpp
* Implementation file for Dictionary ADT
* The Dictionary ADT is an underlying Binary Search Tree. A Dictionary maintains a set of pairs called key and value. The Dictionary contains a switch that determines whether or not it will accept duplicate keys.
*/

#include "Dictionary.h"

// Private type --------------------------------------------------------------
typedef struct NodeObj {
    KEY_TYPE key;
    VAL_TYPE val;
    struct NodeObj *parent;
    struct NodeObj *left;       // left child
    struct NodeObj *right;      // right child
} NodeObj;

typedef NodeObj* Node;

// Exported type --------------------------------------------------------------
typedef struct DictionaryObj {
    int size;                   // number of nodes in the BST
    int unique;                 // 1 if keys are unique, 0 if keys are not unique
    Node root;                  // root of the BST
    Node currNode;              // current node of the BST (when iterating)
}


// Constructors-Destructors ---------------------------------------------------

//newNode()
// Creates and returns reference to a new Node object.
// Initializes next, prev and data fields
Node newNode(KEY_TYPE key, VAL_TYPE val) {
    Node N = (Node *)malloc(sizeof(NodeObj));
    N->key = key;  // since key is a string, must it be malloced?
    N->val = val;
    N->parent = NULL;
    N->left = NULL;
    N->right = NULL;
    return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
    if ((pN != NULL && *pN != NULL)) {
        free(*pN); // if key is a string and is malloced, will have to free it here
        *pN = NULL;
    }
}
// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique) {
    if (unique != 1 || unique != 0) {
        fprintf(stderr, "Dictionary Error: calling newDictionary() with an invalid entry for unique\n");
        exit(EXIT_FAILURE);
    }
    Dictionary D = (Dictionary *)malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->unique = unique;
    D->root = NULL;
    D->currNode = NULL;
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
    if (pD != NULL && *pD != NULL) {
        if ((*pD)->size != 0) {
            makeEmpty(*pD);
        }
        free(*pD); // delete heap memory
        *pD = NULL; // pD points to null
    }
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling size() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    return(D->size);
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling getUnique() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    return((D->unique==1)); // true if 1, false if 0
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
         printf("Dictionary Error: calling lookup() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    // search the tree by comparing keys to find k
    // note: if keys are not unique, find and return the first one with key = k
    
    // note:
    // strcmp(x, y)
    // returns neg if ascii value of x < y
    // returns pos if ascii value of x > y
    // returns 0 if ascii values are equal
    
    Node currNode = D->root;
    while (curr != NULL) {
        KEY_TYPE currKey = curr->key;
        if (KEY_CMP(currKey, k) < 0) { // ascii value of x < y
            // move to left child of currNode
            currNode = currNode->left;
        } else if (KEY_CMP(currKey, k) < 0) { // ascii value of x > y
            // move to right child of currNode
            currNode = currNode->right;
        } else { // ascii value of x = y
            // found k
            return currNode->val;
        }
    }
    // reached here, then k was not found in the tree
    return VAL_UNDEF;   // return val undef
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v) {
    if (D == NULL) {
         printf("Dictionary Error: calling insert() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
         printf("Dictionary Error: calling delete() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling beginReverse() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling currentKey() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling currentVal() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling next() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling prev() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D) {
    if (D == NULL) {
         printf("Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

