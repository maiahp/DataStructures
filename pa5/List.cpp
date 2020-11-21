/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA5
* List.cpp
* Implementation file for List ADT
* The List ADT is a Doubly Linked List that includes a cursor for iteration. The elements themselves are not indexed; the cursor is a vertical bar standing between two elements, which cannot become undefined. A list containing n elements will have n+1 possible cursor positions: 0 signifying the front of the list, through n+1, the back.
*/

#include<iostream>
#include<string>
#include "List.h"

using namespace std;


// Private Constructor ----------------------------------------------------

List::Node::Node(int x) {   // "Node" is the constructor inside List, inside Node struct
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
    
    // note: The empty state is two sentinel nodes: front and back dummy(with random data), pointing at each other
    Node *temp1 = new Node(-1);
    Node *temp2 = new Node(-2);
    
    // set front and back dummy
    this->frontDummy = temp1;
    this->backDummy = temp2;
    
    // connect front & back dummy
    this->frontDummy->next = backDummy;
    this->backDummy->prev = frontDummy;
    
    // cursor lies initially lies in between front & back dummy
    this->pos_cursor = 0;
    
    // set beforeCursor & afterCursor
    this->beforeCursor = frontDummy;
    this->afterCursor = backDummy;
    
    // set number of elements
    this->num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    
    // First create an empty list
    Node *temp1 = new Node(-1);
    Node *temp2 = new Node(-2);
    
    // set front and back dummy
    this->frontDummy = temp1;
    this->backDummy = temp2;
    
    // connect front & back dummy
    this->frontDummy->next = backDummy;
    this->backDummy->prev = frontDummy;
    
    // cursor lies initially lies in between front & back dummy
    this->pos_cursor = 0;
    
    // set beforeCursor & afterCursor
    this->beforeCursor = frontDummy;
    this->afterCursor = backDummy;
    
    // set number of elements
    this->num_elements = 0;
    
    
    // load elements of L into this

}

// Destructor
List::~List() {
    if (isEmpty == false) {
        clear();
    }
    delete frontDummy;
    delete backDummy;
    frontDummy = nullptr;
    backDummy = nullptr;
    
}


// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool isEmpty() {
    return(this->num_elements == 0);
}

// size()
// Returns the size of this List.
int size() {
    return(this->num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int position() {
    return(this->pos_cursor);
}


// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void moveFront();

// moveBack()
// Moves cursor to position size() in this List.
void moveBack();

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int peekNext();

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int peekPrev();

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int moveNext();

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int movePrev();

// insertAfter()
// Inserts x after cursor.
void insertAfter(int x);

// insertBefore()
// Inserts x before cursor.
void insertBefore(int x);

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void eraseAfter();

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void eraseBefore();

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int findNext(int x);

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int findPrev(int x);

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void cleanup();

// clear()
// Deletes all elements in this List, setting it to the empty state.
void clear();

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List concat(const List& L);


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string to_string();

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool equals(const List& R);


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
friend std::ostream& operator<<( std::ostream& stream, List& L );

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
friend bool operator==( List& A, const List& B );

// operator=()
// Overwrites the state of this List with state of L.
List& operator=( const List& L );

};
