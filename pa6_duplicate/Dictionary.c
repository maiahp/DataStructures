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
    
    Node NIL;                   // the "NIL" dummy node that is all leaf nodes and parent of the root
}


// Constructors-Destructors ---------------------------------------------------

//newNode()
// Creates and returns reference to a new Node object.
// Initializes next, prev and data fields
Node newNode(KEY_TYPE key_data, VAL_TYPE val_data) {
    Node N = (Node *)malloc(sizeof(NodeObj));
    
    // get size of key string
    int size_key_data = 0;
    for(int i=0; i < 300; i++) {
        if (key_data[i] == '\n' || key_data[i] == '\0') { // if char is '\n' or '\0'
            break;
        }
        size_key_data++; // increment size
    }
    
    // since key is a (char *) it must be malloc'd
    N->key = (char *)malloc(size_key_data+1); // +1 for null character
    
    // place each char from key into the key char array
    for(int i=0; i < sizeOfKey; i++) {
        N->key[i] = key_data[i];
    }
    N->key[size_key_data] = '\0'; // place null character at end of key char array
    
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
        free((*pN)->key);
        free(*pN);
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
    
    D->NIL = newNode("dummy", -1);
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

// Private Helper functions ---------------------------------------------------

// inOrderSucessor()
// Private function that returns a node's in-order successor
// An in-order successor is the left most node (smallest) of currNode's right subtree.
Node inOrderSucessor(Dictionary D, Node currNode);

// inOrderPredecessor()
// Private fucntion that returns a node's in-order predecessor.
// An in-order predecessor is the right most node (largest) of currNode's left subtree.
Node inOrderPredecessor(Dictionary D, Node currNode);

// getLeftMostChild()
// Private function to retrieve the left most child node of the given currNode
// If D is empty, returns NULL
Node getLeftMostChild(Dictionary D, Node currNode);

// getRightMostChild()
// Private function to retrieve the right most child node of the given currNode
// If D is empty, returns NULL
Node getRightMostChild(Dictionary D, Node currNode);
// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling size() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    return(D->size);
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling getUnique() on NULL Dictionary reference\n");
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
         fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
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
         fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    if (getUnique(D) == 1 && lookup(D, k) != VAL_UNDEF) {    // if D is only allowed unique keys and key already exits in D
        fprintf(stderr, "Dictionary Error: calling insert() with a duplicate key when Dictionary is set to unique\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToInsert = newNode(k, v);          // create new node with k,v
    Node y = NULL;
    Node x = D->root;
    
    while (x != NULL) {
        y = x;
        if (nodeToInsert->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    nodeToInsert->parent = y;                   // set the parent of the nodeToInsert
    if (y == NULL) {                            // if parent is null, nodeToInsert becomes the root
        D->root = nodeToInsert;                 // D was empty
    } else if (nodeToInsert->key < y->key) {    // if nodeToInsert's key is less than its parent's key
        y->left = nodeToInsert;                 // set as left child of parent
    } else {                                    // if nodeToInsert's key is greater than its parent key
        y->right = nodeToInsert;                // set as right child of parent
    }
}

// Transplant()
// Replaces Node u's key and value data with Node v's key and value data
// Only used as a helper function to delete()
void Transplant(Dictionary D, Node u, Node v) {
    if (u->parent == NULL) {
        D->root = v;
    } else if (u->parent == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    if (lookup(D, k) == VAL_UNDEF) { // D does not contain a pair whose key is k
        fprintf(stderr, "Dictionary Error: calling delete() on non-existent key\n");
        exit(EXIT_FAILURE);
    }
    
    // Find the node to delete in D
    Node currNode = D->root;
    while (currNode != NULL) {
        if (k > currNode->key) {            // k is larger than currNode's key
            currNode = currNode->right;     // move to currNode's right child
        } else if (k < currNode->key) {     // k is smaller than currNode's key
            currNode = currNode->left;      // move to currNode's left child
        } else {                            // k == currNode's key
            break;
        }
    }
    
    // Reached here, then currNode contains the key k
    Node nodeToDelete = currNode;
    
    if (nodeToDelete->left == NULL) {                       // nodeToDelete has no left child
        Transplant(T, nodeToDelete, nodeToDelete->right);   // replace nodeToDelete with its right child
    } else if (nodeToDelete->right == NULL) {               // nodeToDelete has no right child
        Transplant(T, nodeToDelete, nodeToDelete->left);    // replace nodeToDelete with its left child
    } else {                    //
        Node y = TreeMinimum(nodeToDelete->right);          //
        if (y->parent != nodeToDelete) {
            Transplant(D, y, y->right);
            y->right = nodeToDelete->right;
            y->right->parent = y;
        }
        Transplant(D, nodeToDelete, y);
        y->left = nodeToDelete->left;
        y->left->parent = y;
    }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling beginForward() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling beginReverse() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling currentKey() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling currentVal() on NULL Dictionary reference\n");
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
         fprintf(stderr, "Dictionary Error: calling next() on NULL Dictionary reference\n");
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
         fprintf(stderr, "Dictionary Error: calling prev() on NULL Dictionary reference\n");
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
         fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
}

