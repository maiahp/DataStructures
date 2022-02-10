/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA1
* List.h
* Header file for List ADT
*/

#ifndef List_h
#define List_h
#define index cursorIndex
#define clear clearList

#include <stdio.h>
#include <stdlib.h>
#define LIST_ELEMENT long
#define LIST_ELEMENT_TOSTRING "%ld"

// Public Exported Type ---------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Creates and returns a new empty List.
List newList(void);

// freeList()
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L);

// back()
// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L);

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L);


// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, LIST_ELEMENT data);

// append()
// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, LIST_ELEMENT data);

// insertBefore
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT data);

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT data);

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// set()
// Overwrites the cursor element with x.
// Pre: length()>0, index()>=0
void set(List L, long x);


// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L);

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);

#endif /* List_h */
