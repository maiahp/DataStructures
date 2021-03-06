/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Dictionary.c
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
} DictionaryObj;


// Constructors-Destructors ---------------------------------------------------

//newNode()
// Creates and returns reference to a new Node object.
// Initializes next, prev and data fields
Node newNode(KEY_TYPE key_data, VAL_TYPE val_data) {
    Node N = malloc(sizeof(NodeObj));
    
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
    for(int i=0; i < size_key_data; i++) {
        N->key[i] = key_data[i];
    }
    N->key[size_key_data] = '\0'; // place null character at end of key char array
    
    N->val = val_data;
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
    if (unique != 1 && unique != 0) {
        fprintf(stderr, "Dictionary Error: calling newDictionary() with an invalid entry for unique\n");
        exit(EXIT_FAILURE);
    }
    Dictionary D = malloc(sizeof(DictionaryObj));
    D->size = 0;
    D->unique = unique;
    D->currNode = NULL;
    D->NIL = newNode("dummy", -1);
    D->root = D->NIL; // point root to the NIL Node
    return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD) {
    if (pD != NULL && *pD != NULL) {
        if ((*pD)->size != 0) {
            makeEmpty(*pD);
        }
        freeNode(&((*pD)->NIL));   // free dummy NIL node
        free(*pD); // delete heap memory
        *pD = NULL; // pD points to null
    }
}

// Private Helper functions ---------------------------------------------------

// getLeftMostChild()
// Private function to retrieve the left most child node of the given currNode
Node getLeftMostChild(Dictionary D, Node currNode) {
    // note:
    // because this fcn is only called inside of local in Dictionary.c file, no need for null Dict check, all other fcns do this already
    if (size(D) == 0) {
        return D->NIL;
    }
    
    while (currNode->left != D->NIL) {  // traverse through all left children
        currNode = currNode->left;
    }
    return currNode;     // the left most leaf of branch starting at currNode
}

// getRightMostChild()
// Private function to retrieve the right most child node of the given currNode
// If D is empty, returns NULL
Node getRightMostChild(Dictionary D, Node currNode) {
    if (size(D) == 0) {
        return D->NIL;
    }
    
    while (currNode->right != D->NIL) {  // traverse through all right children
        currNode = currNode->right;
    }
    return currNode;     // the right most leaf of branch starting at currNode
}

// inOrderSucessor()
// Private function that returns a node's in-order successor
// An in-order successor is the left most node (smallest) of currNode's right subtree.
Node inOrderSucessor(Dictionary D, Node currNode) {
    if (currNode->right != D->NIL) {
        return getLeftMostChild(D, currNode->right);
    }
    Node parent = currNode->parent;
    while(parent != D->NIL && currNode != parent->left) {   // is it parent->left?????
        currNode = parent;
        parent = parent->parent;
    }
    return parent;
}

// inOrderPredecessor()
// Private fucntion that returns a node's in-order predecessor.
// An in-order predecessor is the right most node (largest) of currNode's left subtree.
Node inOrderPredecessor(Dictionary D, Node currNode) {
    if (currNode->left != D->NIL) {
        return getRightMostChild(D, currNode->left);
    }
    Node parent = currNode->parent;
    while(parent != D->NIL && currNode != parent->right) {
        currNode = parent;
        parent = parent->parent;
    }
    return parent;
}

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
    while (currNode != D->NIL) {      // while currNode is not the dummy node
        KEY_TYPE currKey = currNode->key;
        if (KEY_CMP(k, currKey) < 0) { // k is less than currKey
            // move to left child of currNode
            currNode = currNode->left;
        } else if (KEY_CMP(k, currKey) > 0) { // k is greater than currKey
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
    
    while (x != D->NIL) {
        y = x;
        if (KEY_CMP(nodeToInsert->key, x->key) < 0) { // node to insert's key is less than x's key
            x = x->left;
        } else {
            x = x->right;
        }
    }
    nodeToInsert->parent = y;                   // set the parent of the nodeToInsert
    if (y == NULL) {                            // if parent is nil, nodeToInsert becomes the root
        D->root = nodeToInsert;                 // D was empty
        nodeToInsert->parent = D->NIL;          // set new root's parent to NIL
    } else if (KEY_CMP(nodeToInsert->key, y->key) < 0) {    // if nodeToInsert's key is less than its parent's key
        y->left = nodeToInsert;                 // set as left child of parent
    } else {                                    // if nodeToInsert's key is greater than its parent key
        y->right = nodeToInsert;                // set as right child of parent
    }
    
    // set the newly inserted node's children as nil
    nodeToInsert->right = D->NIL;
    nodeToInsert->left = D->NIL;
    D->size++;
}

// Transplant()
// Replaces Node u with Node v
// Only used as a helper function to delete()
void Transplant(Dictionary D, Node u, Node v) {
    if (u->parent == D->NIL) {  // if u's parent is nil, it is the root
        D->root = v;    // update D->root
    } else if (u == u->parent->left) { // if u is its parent's left child
        u->parent->left = v;    // replace u's parent's left's data with v
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
    
    // if there is only one node in D
    if (D->size == 1) {
        // delete the root
        Node nodeToDelete = D->root;  // node to delete is the root
        D->root = D->NIL;             // new root is NIL
        freeNode(&nodeToDelete);      // free node to delete
        nodeToDelete = NULL;          
        D->size--;
        D->currNode = NULL;           // since there are no nodes in D, reset D->currNode to NUL:
        return;
    }
    
    // More than one node in D, find the node to delete
    Node currNode = D->root;
    while (currNode != D->NIL) {
        if (KEY_CMP(k, currNode->key) > 0) {      // k is larger than currNode's key
            currNode = currNode->right;     // move to currNode's right child
        } else if (KEY_CMP(k, currNode->key) < 0) {  // k is smaller than currNode's key
            currNode = currNode->left;      // move to currNode's left child
        } else {                            // k == currNode's key
            break;
        }
    }
    
    // Reached here, then currNode contains the key k and is node to be deleted
    Node nodeToDelete = currNode;
    
    // if node to be deleted is the currNode in D, set currNode as NULL
    if (nodeToDelete == D->currNode) { // if D->currNode = node to delete, k
        D->currNode = NULL;     // set D->currNode as NULL
    }
    
    
    if (nodeToDelete->left == D->NIL) {                     // nodeToDelete has no left child
        Transplant(D, nodeToDelete, nodeToDelete->right);   // replace nodeToDelete with its right child
    } else if (nodeToDelete->right == D->NIL) {             // nodeToDelete has no right child
        Transplant(D, nodeToDelete, nodeToDelete->left);    // replace nodeToDelete with its left child
    } else {       // node has both its children or none
        Node y = getLeftMostChild(D, nodeToDelete->right);
        if (y->parent != nodeToDelete) {
            Transplant(D, y, y->right);     // if y's right is NIL, will replace y with NIL
            y->right = nodeToDelete->right;
            y->right->parent = y;
        }
        Transplant(D, nodeToDelete, y);
        y->left = nodeToDelete->left;
        y->left->parent = y;
    }
    
    // delete the node
    freeNode(&nodeToDelete);
    nodeToDelete = NULL;
    D->size--;
    
    // delete all connections made in D->NIL node
    D->NIL->left = NULL;
    D->NIL->parent = NULL;
    D->NIL->right = NULL;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling makeEmpty() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    
    if (size(D) == 0) { // if the tree is empty, do nothing
        return;
    }
    
    Node root = D->root;
    while(root != D->NIL) {
        delete(D, D->root->key);    // keep deleting the root node
        root = D->root;         // currNode is the root
    }
    D->root = D->NIL;
    D->currNode = NULL; // set currNode as NULL
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
    if (size(D) == 0) { // if size of D is 0, return VAL_UNDEF
        return VAL_UNDEF;
    }
    // to begin forward traverse
    // the first node returned is the smallest node in the dict
    // this is the left mode node from the root
    Node smallest = getLeftMostChild(D, D->root);
    D->currNode = smallest; // update currNode
    return(smallest->val);
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
    if (size(D) == 0) {     // if size of D is 0, return VAL_UNDEF
        return VAL_UNDEF;
    }
    // to begin reverse traverse
    // the first node returned is the largest node in the dict
    // this is the right mode node from the root
    Node largest = getRightMostChild(D, D->root);
    D->currNode = largest; // update currNode
    return(largest->val);
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling currentKey() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    
    if (D->currNode == NULL || D->currNode == D->NIL) {
        return KEY_UNDEF;
    }
    
    // return currNode's key
    return(D->currNode->key);
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
    if (D->currNode == NULL || D->currNode == D->NIL) {
        return VAL_UNDEF;
    }
    
    // return currNode's key
    return(D->currNode->val);
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
    // get the next IN ORDER node from D->currNode
    if (D->currNode == D->NIL) { // if currNode is nil
        return VAL_UNDEF;
    }
    Node next = inOrderSucessor(D, D->currNode); // get the successor
    D->currNode = next; // update the currNode to its successor
    return D->currNode->val;
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
    // get the previous IN ORDER node from D->currNode
    // get the next IN ORDER node from D->currNode
    if (D->currNode == D->NIL) { // if currNode is nil
        return VAL_UNDEF;
    }
    Node prev = inOrderPredecessor(D, D->currNode); // get the successor
    D->currNode = prev; // update the currNode to its successor
    return D->currNode->val;
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
    
    // in order tree traversal
    Node currNode = getLeftMostChild(D, D->root);      // currNode is the smallest, left most node in D
    Node largestNode = getRightMostChild(D, D->root);
    
    while(currNode != D->NIL) {
        if (currNode == NULL) {
            break;
        }
        // print the current node
        fprintf(out, KEY_FORMAT, currNode->key);
        fprintf(out, " ");
        fprintf(out, VAL_FORMAT, currNode->val);
        if (currNode != largestNode) {
            fprintf(out, "\n");
        }
        currNode = inOrderSucessor(D, currNode); // get next in order node
    }
}
