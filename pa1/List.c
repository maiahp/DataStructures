/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA1
* List.c
* Implementation file for List ADT
* The List ADT is a Doubly Linked List that includes a cursor for iteration. The cursor underscores up to one element in the List, and the default cursor state is "undefined".
*/

#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;     // references node at the front of list
    Node back;      // references back of list
    Node cursor;    // the node which is pointed to by cursor
    int index;      // the cursor index; starts at 0
    int length;     // number of elements; starts at 1
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Creates and returns a new Node.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees all heap memory associated with *pN, and sets
// *pN to NULL.
void freeNode(Node *pN) {
    if ((pN != NULL && *pN != NULL)) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Creates and returns a new empty List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;  // cursor is initially undefined
    L->length = 0;
    return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL) {
    if((pL != NULL) && (*pL != NULL)) {
        if (length(*pL) != 0) { // if the list has data, delete it first
            clear(*pL);
        }
        free(*pL);     // delete heap memory
        *pL = NULL;    // set pointer to the List to null
    }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->index); // index is either defined or -1
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // pre condition
        return(L->front->data);
    } else {
        printf("List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {  // pre condition
        return(L->back->data);
    } else {
        printf("List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0 && index(L) >= 0) { // pre condition
        return(L->cursor->data);
    } else {
        printf("List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on one or both NULL List references\n");
        exit(EXIT_FAILURE);
    }
    // Lists are in the same state when
    // A and B is the same list
    // the cursor position of A and B is the same
    
    int is_same = 1; // is same is 1 if true
    if (length(A) == length(B)) {
        if (index(A) == index(B)) {
            // iterate through both Lists A and B, checking for same node data
            Node currA = A->front;
            Node currB = B->front;
            while (currA != NULL && currB != NULL) {
                if (currA->data != currB->data) {
                    is_same = 0; // lists are not the same
                    break;
                } else {
                    currA = currA->next;
                    currB = currB->next;
                }
            }
        } else { // index of cursors not the same
            is_same = 0; // is same is false
        }
    } else { // lengths not equal
        is_same = 0; // is same is false
    }
    return is_same;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while(L->front != NULL) {
        deleteFront(L); // updates length of L and should set L's front and back to null
    }
    L->cursor = NULL;
    L->index = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // if L is non empty
        L->cursor = L->front;
        L->index = 0;
    } // if L is empty, do nothing
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // if L is non empty
        L->cursor = L->back;
        L->index = length(L)-1;
    } // if L is empty, do nothing
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((L->index >= 0) && (L->cursor != L->front)) { // when cursor is defined and not at front node
        // move cursor to previous node
        L->cursor = L->cursor->prev;
        L->index--;
    } else if (L->cursor == L->front){ // if cursor is at the front of the list
        // it becomes undefined
        L->cursor = NULL;
        L->index = -1;
    } // if cursor is undefined, do nothing
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((L->index >= 0) && (L->cursor != L->back)) { // cursor is defined and not at back
        // move cursor forward one node
        L->cursor = L->cursor->next;
        L->index++;
    } else if (L->cursor == L->back){ // cursor is at back of the list
        // it becomes undefined
        L->cursor = NULL;
        L->index = -1;
    }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToInsert = newNode(data);
    
    if (length(L) == 0) { // L is initially empty
        L->front = nodeToInsert;
        L->back = nodeToInsert;
        // cursor is not defined here because the list was empty, don't update
    } else { // L has elements
        nodeToInsert->next = L->front; // new node's next is L's front
        L->front->prev = nodeToInsert; // L's front's prev is new node
        L->front = nodeToInsert; // new front of L is the new node
        
        if (L->index >= 0) { // if the cursor is defined
            L->index++;  // cursor stays pointed to the same node, but its index is shifted +1
        }
    }
    L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node nodeToInsert = newNode(data);
    
    if (length(L) == 0) { // L is initially empty
        L->front = nodeToInsert;
        L->back = nodeToInsert;
        // cursor is not defined because the list was empty, don't update
    } else { // L has elements
        nodeToInsert->prev = L->back; // new node's prev is L's back
        L->back->next = nodeToInsert; // L's back's next is new node
        L->back = nodeToInsert; // new back of L is the new node
        // if cursor is defined, it will stay at same node and index will have correct value
    }
    L->length++;
}

// insertBefore
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0 && index(L) >= 0) { // pre condition: L is not empty and cursor is defined
        if (index(L) == 0) { // cursor is at front of list
            prepend(L, data); // new node will be the front of the list
        } else { // cursor is at some place in list
            Node nodeToInsert = newNode(data);
            // insert before the cursor
            L->cursor->prev->next = nodeToInsert;
            nodeToInsert->prev = L->cursor->prev;
            nodeToInsert->next = L->cursor;
            L->cursor->prev = nodeToInsert;
            
            // index is updated +1
            L->index++;
        }
    } else { // the cursor is undefined
        printf("List Error: calling insertBefore() when cursor is undefined\n");
        exit(EXIT_FAILURE);
    }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if () {
        
        
        
    } else { // the cursor is undefined or list is empty
        printf("List Error: calling insertAfter() when cursor is undefined or list is empty.\n");
        exit(EXIT_FAILURE);
    }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // pre condition, L is not empty
        Node nodeToDelete = L->front;
        
        if (L->index != -1) { // case: if the cursor is defined
            if (L->cursor == L->front) { // if the cursor is the front element
                // it becomes undefined
                L->cursor = NULL;
                L->index = -1;
            } else { // the cursor is not at front element
                // cursor will point to correct node but index of cursor must be decremented
                L->index--;
            }
        }
        
        if (length(L) == 1) { // case: L has 1 element
            // delete the node and the list is empty
            L->front = NULL;
            L->back = NULL;
        } else { // case: L has more than one element
            Node newFront = L->front->next; // new front is element after front
            newFront->prev = NULL; // new front's prev is null
            L->front = newFront; // set L's front as new front
        }
        
        freeNode(&nodeToDelete);
        L->length--; // update length of L
    }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) { // pre condition, L is not empty
        Node nodeToDelete = L->back;
        
        if (L->index != -1) { // case: if the cursor is defined
            if (L->cursor == L->back) { // if cursor is the back element
                // it becomes undefined
                L->cursor = NULL;
                L->index = -1;
            } // if cursor is not the back element, we do nothing
        }
        
        if (length(L) == 1) { // case: L has 1 element
            // delete the node and the list is empty
            L->front = NULL;
            L->back = NULL;
        } else { // case: L has more than one element
            Node newBack = L->back->prev; // new back is back's prev
            newBack->next = NULL; // set new back's next as null
            L->back = newBack;
        }
        
        freeNode(&nodeToDelete);
        L->length--;
    }
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    
    if (length(L) > 0 && index(L) >= 0) { // pre condition, L is not empty and cursor defined
        
    }
    
}


// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL List reference.\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        // list is empty, do nothing
        return;
    }
    
    // can't use cursor to traverse, must preserve cursor
    Node currNode = L->front;
    while (currNode != NULL) {
        fprintf(out, "%d", currNode->data);
        if (currNode != L->back) { // to avoid an extra space when printing end of list
            fprintf(out, " ");
        }
        currNode = currNode->next;
    }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    List copyL = newList();
    
    Node currL = L->front;
    while (currL != NULL) {
        append(copyL, currL->data);
        currL = currL->next;
    }
    // cursor of copyL stays undefined
    return copyL;
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if ((A == NULL) || (B == NULL)) {
        printf("List Error: calling concatList() on one or both NULL List references\n");
        exit(EXIT_FAILURE);
    }
    
    List resultList = newList();
    
    // iterate through A and add to resultList
    Node currA = A->front;
    while (currA != NULL) {
        append(resultList, currA->data);
        currA = currA->next;
    }
    
    Node currB = B->front;
    while (currB != NULL) {
        append(resultList, currB->data);
        currB = currB->next;
    }
    
    // cursor of B stays undefined
    return resultList;
}



/*
 notes:
 bi-directional queue that includes a cursor to be used for iteration
 -cursor underscores a distinguished element or node
 -it is a valid state for cursor to be undefined, which is default state
 - two references, "front" and "back"
 - cursor is only used by the client to traverse the list in either direction
 -elements have indices from 0 to n-1, n=num elements
 -list module exports a List type only (not node type)
 
 - .c file contains: private non-exported struct called NodeObj and a pointer to that struct called Node
    - fields for int (data), two Node references (previous and next Nodes)
 - include constructor & destructor for node type
 - private non-exported struct ListObj should contain fields of type Node, referring to the front, back and cursor elements. also contains int field for length of a List, index of cursor element. When the cursor undefined, an appropriate value for the index field is -1
 
 - create separate file called ListTest to serve as a client test for List ADT. do not submit this file
 
 - have a Makefile which includes a clean target that removes Lex and any .o files. and creates an executable binary file called Lex, which is the main program. Compile operations: call the gcc compiler with the flag -std=c99. Test for leaks using valgrind on unix.ucsc.edu
-  README: include any comments of any help
 
 
 
 */
