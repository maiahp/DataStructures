/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Dictionary.c
* Implementation file for Dictionary ADT
* The Dictionary ADT is an underlying Red Black Tree. A Dictionary maintains a set of pairs called key and value. The Dictionary contains a switch that determines whether or not it will accept duplicate keys.
*/

#include "Dictionary.h"
#define RED 1
#define BLACK 0

// Private type --------------------------------------------------------------
typedef struct NodeObj {
    KEY_TYPE key;
    VAL_TYPE val;
    int color;  // red or black
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
    int num = -1;
    D->NIL = newNode("dummy", &num); // must pass num as reference because val is int*
    D->NIL->color = BLACK; // nil node is always black
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
    while(parent != D->NIL && currNode != parent->left) {
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

// InOrderTreeWalk()
void InOrderTreeWalk(FILE *out, Dictionary D, Node x, Node lastNode) {
    if (x != D->NIL) {
        InOrderTreeWalk(out, D, x->left, lastNode);    // recur on left children
        fprintf(out, "%s", x->key);                    // print the key
        if (x != lastNode) {
            fprintf(out, "\n");
        }
        InOrderTreeWalk(out, D, x->right, lastNode);    // recur on right children
    }
}

// PreOrderTreeWalk()
void PreOrderTreeWalk(FILE *out, Dictionary D, Node x, Node lastNode) {
    if (x != D->NIL) {
        fprintf(out, "%s", x->key);     // print the key
        if (x != lastNode) {
            fprintf(out, "\n");
        }
        PreOrderTreeWalk(out, D, x->left, lastNode);     // recur on left children
        PreOrderTreeWalk(out, D, x->right, lastNode);    // recur on right children
    }
}

// InOrderTreeWalk()
void PostOrderTreeWalk(FILE *out, Dictionary D, Node x) {
    if (x != D->NIL) {
        PostOrderTreeWalk(out, D, x->left);     // recur on left children
        PostOrderTreeWalk(out, D, x->right);    // recur on right children
        fprintf(out, "%s", x->key);             // print key
        if (x != D->root) {     // the root is the last node to be printed
            fprintf(out, "\n");
        }
    }
}

// LeftRotate()
void LeftRotate(Dictionary D, Node x) {
    // set y
    Node y = x->right;
    
    // turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != D->NIL && y->left != NULL) {
        y->left->parent = x;
    }
    
    // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->NIL) {
        D->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    // put x on y's left
    y->left = x;
    x->parent = y;
}

// RightRotate()
void RightRotate(Dictionary D, Node x) {
    // set y
    Node y = x->left;
       
    // turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != D->NIL && y->right != NULL) {  // not necessary if using sentinal nil node
        y->right->parent = x;
    }
   
   // link y's parent to x
    y->parent = x->parent;
    if (x->parent == D->NIL) {
        D->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
   // put x on y's right
    y->right = x;
    x->parent = y;
}

// RB_InsertFixUp
// Fixes up the RB Tree after Insertion to preserve RBT Properties
void RB_InsertFixUp(Dictionary D, Node z) {
    Node y = NULL;
    
    while(1) {
        if (z->parent != D->NIL) {
            if (z->parent->color != RED)break;
        } else {
            break;
        }
        if (z->parent->parent == D->NIL)break;
        
        // conditions to continue:
        // currNode's parent's color exists and is red
        // currNode's grandparent exists
        
        if (z->parent == z->parent->parent->left) {             // pz is ppz's left child
            if (z->parent->parent == D->NIL)break;
            y = z->parent->parent->right;                       // y = ppz's right child (y is z's uncle)
            // note:
            // z = node to delete, y = z's uncle
            // reached here if pz is ppz's left child
            // case 1: uncle y is red
            // case 2: y's color is black and z is pz's right child
            // case 3: y's color is black
            if (y != D->NIL) {                                  // if uncle y is not NIL
                if (y->color == RED) {                          // y is red
                    z->parent->color = BLACK;                   // CASE 1
                    y->color = BLACK;                           // CASE 1
                    z->parent->parent->color = RED;             // CASE 1
                    z = z->parent->parent;                      // CASE 1
                } else {                                        // y is black
                    if (z == z->parent->right) {                // z is pz's right child
                        z = z->parent;                          // CASE 2
                        LeftRotate(D, z);                       // CASE 2
                    }
                    z->parent->color = BLACK;                   // CASE 3
                    z->parent->parent->color = RED;             // CASE 3
                    RightRotate(D, z->parent->parent);          // CASE 3
                }
            } else {                                            // If uncle y is NIL
                if (z == z->parent->right) {                    // z is pz's right child
                    z = z->parent;                              // CASE 2
                    LeftRotate(D, z);                           // CASE 2
                }
                z->parent->color = BLACK;                       // CASE 3
                z->parent->parent->color = RED;                 // CASE 3
                RightRotate(D, z->parent->parent);              // CASE 3
            }
            
        } else {                                                // pz is ppz's right child
            if (z->parent->parent == D->NIL)break;
            y = z->parent->parent->left;                        // y is ppz's left child (z's uncle)
            // note:
            // z = node to delete, y = z's uncle
            // reached here is pz is ppz's right child
            // case 4: uncle y is red
            // case 5: uncle y is black and z is pz's left child
            // case 6: uncle y is black
            if (y != D->NIL) {                                  // if y is not NIL
                if (y->color == RED) {                          // y is red
                    z->parent->color = BLACK;                   // CASE 4
                    y->color = BLACK;                           // CASE 4
                    z->parent->parent->color = RED;             // CASE 4
                    z = z->parent->parent;                      // CASE 4
                } else {                                        // y is black
                    if (z == z->parent->left) {                 // z is pz's left child
                        z = z->parent;                          // CASE 5
                        RightRotate(D, z);                      // CASE 5
                    }
                    z->parent->color = BLACK;                   // CASE 6
                    z->parent->parent->color = RED;             // CASE 6
                    LeftRotate(D, z->parent->parent);           // CASE 6
                }
            } else {                                            // If uncle y is NIL
                if (z == z->parent->left) {                     // z is pz's left child
                    z = z->parent;                              // CASE 5
                    RightRotate(D, z);                          // CASE 5
                }
                z->parent->color = BLACK;                       // CASE 6
                z->parent->parent->color = RED;                 // CASE 6
                LeftRotate(D, z->parent->parent);               // CASE 6
            }
        }
    }
    D->root->color = BLACK;                                     // color the root black

    /* Professor's Pseudo-Code that my code is modelled after
    Node z = currNode
    Node y;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;               // case 1
                y->color = BLACK;                       // case 1
                z->parent->parent->color = RED;         // case 1
                z = z->parent->parent;                  // case 1
            } else {
                if (z == z->parent->right) {
                    z = z->parent;                      // case 2
                    LeftRotate(D, z);                   // case 2
                }
                z->parent->color = BLACK;               // case 3
                z->parent->parent->color = RED;         // case 3
                RightRotate(D, z);                      // case 3
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;               // case 4
                y->color = BLACK;                       // case 4
                z->parent->parent->color = RED;         // case 4
                z = z->parent->parent;                  // case 4
            } else {
                if (z == z->parent->left) {
                    z = z->parent;                      // case 5
                    RightRotate(D, z);                  // case 5
                }
                z->parent->color = BLACK;               // case 6
                z->parent->parent->color = RED;         // case 6
                LeftRotate(D, z->parent->parent);       // case 6
            }
        }
    }
    D->root->color = BLACK;
     */
}

// RB_DeleteFixUp()
// Fixes up the RB Tree after Deletion to preserve RBT Properties
void RB_DeleteFixUp(Dictionary D, Node x) {
    // x = node to delete
    Node w = NULL;
    if (x == D->NIL)return;                             // if x, the node to delete, is nil, return
    while(x != D->root && x->color == BLACK) {          // while x is not root and x is black
        if (x == x->parent->left) {                     // if x is px's left child
            // note:
            // x is not root, x is black
            // x is px's left child
            // set w to be px's right child
            // case 1: if w is red
            // case 2: if w's children are both black
            // case 3: if w's children are NOT both black, w's right child is black
            // case 4: both w's children are NOT black
            w = x->parent->right;                       // set w to be px's right child
            if (w->color == RED) {                      // if w is red
                w->color = BLACK;                       // CASE 1
                x->parent->color = RED;                 // CASE 1
                LeftRotate(D, x->parent);               // CASE 1
                w = x->parent->right;                   // CASE 1
            }
      
            if (w->left != D->NIL && w->right != D->NIL) { // if one is null, both are null since tree is balanced
                if (w->left->color == BLACK && w->right->color == BLACK) {  // if both w's children are black
                    w->color = RED;                     // CASE 2
                    x = x->parent;                      // CASE 2
                } else {                                // both of w's children are NOT both black
                    if (w->right->color == BLACK) {     // w's right child is black
                        w->left->color = BLACK;         // CASE 3
                        w->color = RED;                 // CASE 3
                        RightRotate(D, w);              // CASE 3
                        w = x->parent->right;           // CASE 3
                    }
                    w->color = x->parent->color;        // CASE 4
                    x->parent->color = BLACK;           // CASE 4
                    w->right->color = BLACK;            // CASE 4
                    LeftRotate(D, x->parent);           // CASE 4
                    x = D->root;                        // CASE 4
                }
            } else { // this must be taken out
                //n->color = currNode->parent->color;
                //currNode->parent->color = BLACK;
                //n->right->color = BLACK;
                //RotateLeft(D, currNode->parent);
                x = D->root;
            }
            
        } else {
            // note:
            // x is not root, x is black
            // x is not px's left child (so x is px's right child)
            // set w to be px's left child
            // case 5: if w is red
            // case 6: if both w's children are black
            // case 7: w is black and w's left child is black
            // case 8: w is black
            w = x->parent->left;                            // set w to be px's left child
            if (w->color == RED) {                          // if w is red
                w->color = BLACK;                           // CASE 5
                x->parent->color = RED;                     // CASE 5
                RightRotate(D, x->parent);                  // CASE 5
                w = x->parent->left;                        // CASE 5
            }
            if (w->right == D->NIL || w->left == D->NIL || w->right == NULL || w->left == NULL) {  // if w has a nil (or null) child (must check this first bc w would not have a left child, therefore we don't color it's left child black!!! which is difference btwn this and the other case 8)
                w->color = x->parent->color;                // CASE 8 (but w has no children)
                x->parent->color = BLACK;                   // CASE 8 (but w has no children)
                RightRotate(D, x->parent);                  // CASE 8 (but w has no children)
                x = D->root;                                // CASE 8 (but w has no children)
            } else if (w->right->color == BLACK && w->left->color == BLACK) {   // w's children are both black
                w->color = RED;                             // CASE 6
                x = x->parent;                              // CASE 6
            } else {
                if (w->left->color == BLACK) {              // if w's left child is black
                    w->right->color = BLACK;                // CASE 7
                    w->color = RED;                         // CASE 7
                    LeftRotate(D, w);                       // CASE 7
                    w = x->parent->left;                    // CASE 7
                }
                w->color = x->parent->color;                // CASE 8
                x->parent->color = BLACK;                   // CASE 8
                w->left->color = BLACK;                     // CASE 8
                RightRotate(D, x->parent);                  // CASE 8
                x = D->root;                                // CASE 8
            }
        }
        x->color = BLACK;                  // color x black
    }
    
    /* Professor's pseudo-code that my code was modelled after
    Node x = currNode;
    Node w;
    while (x != D->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;                       // case 1
                x->parent->color = RED;                 // case 1
                LeftRotate(D, x->parent);               // case 1
                w = x->parent->right;                   // case 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                         // case 2
                x = x->parent;                          // case 2
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;             // case 3
                    w->color = RED;                     // case 3
                    RightRotate(D, w);                  // case 3
                    w = x->parent->right;               // case 3
                }
                w->color = x->parent->color;            // case 4
                x->parent->color = BLACK;               // case 4
                x->right->color = BLACK;                // case 4
                LeftRotate(D, x->parent);               // case 4
                x = D->root;                            // case 4
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                       // case 5
                w->parent->color = RED;                 // case 5
                RightRotate(D, x->parent);              // case 5
                w = x->parent->left;                    // case 5
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                         // case 6
                x = x->parent;                          // case 6
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;            // case 7
                    w->color = RED;                     // case 7
                    LeftRotate(D, w);                   // case 7
                    w = x->parent->left;                // case 7
                }
                w->color = x->parent->color;            // case 8
                x->parent->color = BLACK;               // case 8
                w->left->color = BLACK;                 // case 8
                RightRotate(D, x->parent);              // case 8
                x = D->root;                            // case 8
            }
        }
    }
    x->color = BLACK;
    */
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
    
    nodeToInsert->color = RED;  // set newly inserted node to be RED
    RB_InsertFixUp(D, nodeToInsert);
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
    // First find the node to be deleted
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
    
    // if node to be deleted is D->currNode, set currNode as NULL
    if (nodeToDelete == D->currNode) { // if D->currNode = node to delete, k
        D->currNode = NULL;     // set D->currNode as NULL
    }

    // deleting the nodeToDelete
    Node y = nodeToDelete;
    int y_original_color = y->color;
    Node x;
    
    if (nodeToDelete->left == D->NIL) {                     // nodeToDelete has no left child
        x = nodeToDelete->right;
        Transplant(D, nodeToDelete, nodeToDelete->right);   // replace nodeToDelete with its right child
    } else if (nodeToDelete->right == D->NIL) {             // nodeToDelete has no right child
        x = nodeToDelete->left;
        Transplant(D, nodeToDelete, nodeToDelete->left);    // replace nodeToDelete with its left child
    } else {       // node has both its children or none
        Node y = getLeftMostChild(D, nodeToDelete->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == nodeToDelete) {
            x->parent = y;
        } else {
            Transplant(D, y, y->right);
            y->right = nodeToDelete->right;
            y->right->parent = y;
        }
        Transplant(D, nodeToDelete, y);
        y->left = nodeToDelete->left;
        y->left->parent = y;
        y->color = nodeToDelete->color;
    }
    
    // delete all connections made in D->NIL node
    D->NIL->left = NULL;
    D->NIL->parent = NULL;
    D->NIL->right = NULL;
    
    if (y_original_color == BLACK) {
        RB_DeleteFixUp(D, x);
    }
    
    // delete the node
    freeNode(&nodeToDelete);
    nodeToDelete = NULL;
    D->size--;
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
    if (D->currNode == D->NIL) {    // if the current node is now NIL, then iteration has ended, return VAL_UNDEF
        return VAL_UNDEF;
    }
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
void printDictionary(FILE* out, Dictionary D, const char* ord) {
    if (D == NULL) {
         fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
     }
    // The last node to print for pre and in order is the right most node
    Node largestNode = getRightMostChild(D, D->root);
    
    if (strcmp(ord, "pre") == 0) {          // pre order tree traversal
        PreOrderTreeWalk(out, D, D->root, largestNode);
        
    } else if (strcmp(ord, "in") == 0) {    // in order tree traversal
        InOrderTreeWalk(out, D, D->root, largestNode);
        
    } else if (strcmp(ord, "post") == 0) {  // post order tree traversal
        // the last node to print is the root
        PostOrderTreeWalk(out, D, D->root);
    }
}
