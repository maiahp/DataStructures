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
    frontDummy = temp1;
    backDummy = temp2;
    
    // connect front & back dummy
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    
    // cursor lies initially lies in between front & back dummy
    pos_cursor = 0;
    
    // set beforeCursor & afterCursor
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    
    // set number of elements
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    // the copy constructor should copy contents of L into "this"
    
    // First create an empty list which is "this"
    Node *temp1 = new Node(-1);
    Node *temp2 = new Node(-2);
    
    // set front and back dummy     // NOTE TOOK OUT this->
    frontDummy = temp1;
    backDummy = temp2;
    
    // connect front & back dummy
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    
    // cursor lies initially lies in between front & back dummy
    pos_cursor = 0;
    
    // set beforeCursor & afterCursor
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    
    // set number of elements
    num_elements = 0;
    
    // if copying an empty List, return an empty list
    if (L.frontDummy->next == L.backDummy) {
        return;
    }
    
    // load elements of L into this
    this->moveFront();
    Node* curr_of_L = L.frontDummy->next;
    
    while(curr_of_L != L.backDummy) {
        int data_of_L = curr_of_L->data;
        insertAfter(data_of_L);
        this->moveNext();
        curr_of_L = curr_of_L->next;
    }
    
    // cursor of copy list "this" should be the same as L
    afterCursor = L.afterCursor;
    beforeCursor = L.beforeCursor;
    pos_cursor = L.pos_cursor;
}

// Destructor
List::~List() {
    if (isEmpty() == false) {
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
bool List::isEmpty() {
    return(this->num_elements == 0);
}

// size()
// Returns the size of this List.
int List::size() {
    return(this->num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position() {
    return(this->pos_cursor);
}


// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    this->pos_cursor = 0;                       // pos of cursor is 0
    this->beforeCursor = this->frontDummy;      // set beforeCursor to be frontDummy
    this->afterCursor = this->frontDummy->next; // set afterCursor to be first elem in list
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack() {
    this->pos_cursor = this->size();            // pos of cursor is size()
    this->afterCursor = this->backDummy;        // set afterCursor to be backDummy
    this->beforeCursor = this->backDummy->prev; // beforeCursor is last elem in list
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext() {
    if (this->position() >= this->size()) {
        cerr << "List Error: calling peekNext() when there is no next element\n";
        exit(1);
    }
    return(this->afterCursor->data);  // return data of elem after cursor
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev() {
    if (this->position() <= 0) {
        cerr << "List Error: calling peekPrev() when there is no previous element\n";
        exit(1);
    }
    return(this->beforeCursor->data);  // return data of elem after cursor
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext() {
    if (this->position() >= this->size()) {
        cerr << "List Error: calling moveNext() when there is no next element\n";
        exit(1);
    }
    int data = this->afterCursor->data;   // save data of after cursor to return
    this->beforeCursor = this->beforeCursor->next;
    this->afterCursor = this->afterCursor->next;
    this->pos_cursor++;
    return data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev() {
    if (this->position() <= 0) {        // cursor is at position 0
        cerr << "List Error: calling movePrev() when there is no previous element\n";
        exit(1);
    }
    int data = beforeCursor->data;         // data to return
    this->beforeCursor = this->beforeCursor->prev;
    this->afterCursor = this->afterCursor->prev;
    this->pos_cursor--;
    return data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x) {
    // Note: X BECOMES AFTER CURSOR
    Node* temp = new Node(x);
    
    //Node bc = &(this->beforeCursor);
    //Node ac = &(this->afterCursor);
    
    // ERROR HERE: does not change frontDummy and backDummy's next and prevs
    // only updates beforeCursor & afterCursor's next and prev
    
    this->beforeCursor->next = temp;
    this->afterCursor->prev = temp;
    temp->prev = beforeCursor;
    temp->next = afterCursor;

    this->afterCursor = temp; // afterCursor is updated to point to new node
    this->num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x) {
    // Note: X BECOMES BEFORE CURSOR
    // the cursor must be moved forward, in order to make x the beforeCursor
    Node *temp = new Node(x);
    this->beforeCursor->next = temp;
    this->afterCursor->prev = temp;
    temp->prev = beforeCursor;
    temp->next = afterCursor;

    this->beforeCursor = temp;
    this->num_elements++;
    
    // move cursor to next place (afterCursor doesn't change)
    this->pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter() {
    if (this->position() >= this->size()) {
        cerr << "List Error: calling eraseAfter() when cursor is at end of list\n";
        exit(1);
    }
    Node* nodeToDelete = this->afterCursor;
    this->beforeCursor->next = this->afterCursor->next;
    this->afterCursor->next->prev = this->beforeCursor;
    this->afterCursor = this->afterCursor->next; // update afterCursor
    delete nodeToDelete;
    this->num_elements--;
    // cursor is at correct position, don't update
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (this->position() <= 0) {
        cerr << "List Error: calling eraseBefore() when cursor is at front of list\n";
        exit(1);
    }
    // note:
    // to delete element before the cursor
    // the cursor must move one backwards
    // its afterCursor stays the same element
    Node* nodeToDelete = this->beforeCursor;
    this->afterCursor->prev = this->beforeCursor->prev;
    this->beforeCursor->prev->next = this->afterCursor;
    this->beforeCursor = this->beforeCursor->prev; // update beforeCursor
    this->pos_cursor--; // update cursor to be at correct place
    delete nodeToDelete;
    this->num_elements--;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x) {
    // start from current cursor position
    while (this->position() < this->size()-1) { // while cursor is not at backDummy
        if (this->afterCursor->data == x) { // compare x with elem after the cursor
            this->moveNext(); // if x found, place cursor after x
            return(this->position());
        }
        this->moveNext(); // x is not found, move cursor forward
    }
    // if while exits, we have not found x
    this->moveBack();
    return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x) {
    // start from current cursor position
    while (this->position() > 0) {
        if (this->beforeCursor->data == x) {
            this->movePrev();
            return(this->position());
        }
        this->movePrev(); // x not found, move cursor forward
    }
    // if while exits, we have not found x
    this->moveFront();
    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup() {
    // start at front of list
    Node* i = this->frontDummy->next;
    Node* j;
    while (i != this->backDummy) {
        j = i->next;
        while (j != this->backDummy) {
            if (i->data == j->data) { // datas are the same
                Node* temp = j;
                // delete j, it is the duplicate
                j->prev->next = j->next;
                j->next->prev = j->prev;
                delete temp;
                temp = nullptr;
                this->num_elements--;
                
                if (pos_cursor > num_elements) {
                    // if pos_cursor is out of range after deletion
                    // then we ammend the cursor to be at back position
                    this->moveBack();
                }
                //break;
            }
            j = j->next;
        }
        i = i->next;
    }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    this->moveFront();
    while(this->afterCursor != this->backDummy) {
        this->eraseAfter();
        this->moveFront();
    }
    // note: cursors are updated in eraseAfter and pos_cursor will be 0
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L) {
    List result;
    
    // traverse "this"
    Node* curr = this->frontDummy->next;
    while(curr != this->backDummy) {
        result.insertAfter(curr->data);
        
        result.moveNext();
        curr = curr->next;
    }
    
    // traverse L
    Node* currL = L.frontDummy->next;
    while(currL != L.backDummy) {
        result.insertAfter(currL->data);
        result.moveNext();
        currL = currL->next;
    }
    
    result.moveFront(); // update result's cursor to front
    return(result);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
string List::to_string() {
    // don't use cursor to traverse, we want to preserve cursor
    string s = "(";
    int count = 1;
    Node* curr = this->frontDummy->next;
    while (curr != this->backDummy) {
        s += std::to_string(curr->data);
        if (count < num_elements) {
            s+= ", ";
            count++;
        }
        curr = curr->next;
    }
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    
    while(eq && N != nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L ) { // i removed 'friend' here make sure this is ok
        return stream << L.List::to_string();
        //return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ) { // i removed 'friend' here make sure this is ok
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if( this != &L ){ // not self assignment
        this->clear();
        
        Node* currL = L.frontDummy->next;
        while(currL != L.backDummy) {
            this->insertAfter(currL->data);
            this->moveNext();
            currL = currL->next;
        }
        
        // cursor of L should be cursor of this
        this->pos_cursor = L.pos_cursor;
        this->beforeCursor = L.beforeCursor;
        this->afterCursor = L.afterCursor;
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}
