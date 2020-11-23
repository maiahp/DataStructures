/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA5
* Shuffle.cpp
* Client module for the List ADT
*/

/*
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
*/
#include <iostream>
#include <string>
#include "List.h"


using namespace std;
int main(int argc, const char * argv[]) {
    
    cout << "Testing List" << endl << endl;
    cout << "Creating List l" << endl << endl;
    
    List l, A, B, C;
    
    int count = 1;
    l.moveFront();
    while(count <= 10) {
        l.insertBefore(count);
        count++;
    }
    cout << "List l is: " << endl;
    cout << l << endl << endl;
    cout << l << endl;
    
    // testing peekNext() and moveNext()
    cout << "Testing peekNext() and moveNext()" << endl;
    l.moveFront();
    while(l.position() < l.size()) {
        int data = l.peekNext();
        cout<< data << endl;
        l.moveNext();
    }
    cout<<endl<<endl<<endl;
    
    
    // testing peekPrev()
    cout << "Testing peekNext() and moveNext()" << endl;
    l.moveBack();
    while(l.position() > 0) {
        int data = l.peekPrev();
        cout<< data << endl;
        l.movePrev();
    }
    cout<<endl<<endl<<endl;
    
    
    // testing eraseAfter
    cout << "Moving cursor to position 3" << endl;
    cout << "Calling eraseAfter()" << endl;
    l.moveFront();
    for(int i=1; i<=3; i++) {
        l.moveNext();
    }
    l.eraseAfter();
    cout<< "List l is: " << endl;
    cout << l << endl;
    
    cout<<endl<<endl;
    
    
    // testing eraseBefore
    cout<<"Moving cursor to position 7" << endl;
    cout << "Calling eraseBefore()" << endl;
    l.moveFront();
    for(int i=1; i<=7; i++) {
        l.moveNext();
    }
    l.eraseBefore();
    cout<< "List l is: " << endl;
    cout << l << endl;
    
    cout<<endl<<endl;
    
    
    // testing findNext
    cout<< "Testing findNext() and eraseBefore()" << endl;
    cout<< "Creating List A" << endl << endl;
    
    count = 1;
    A.moveFront();
    while(count <= 10) {
        A.insertBefore(count);
        count++;
    }
    A.insertAfter(5);
    A.moveNext();
    A.insertAfter(3);
    A.moveNext();
    A.insertAfter(2);
    
    cout << "List A is: " << endl;
    cout << A << endl << endl;
    
    cout << "Calling findNext() with integer 5" << endl;
    A.moveFront();
    A.findNext(5);
    cout<< "Cursor is at position " << A.position() << endl;
    cout<< "Calling eraseBefore() to delete element with integer 5"<< endl << endl;
    A.eraseBefore();
    
    cout << "List A is: " << endl;
    cout << A << endl;

    cout<<endl<<endl;
    
    
    // testing findPrev
    cout<< "Testing findPrev() and eraseAfter()" << endl;
    
    cout << "List A is: " << endl;
    cout << A << endl << endl;
    
    cout << "Calling findPrev() with integer 10" << endl;
    A.moveBack();
    A.findPrev(10);
    cout<< "Cursor is at position " << A.position() << endl;
    cout<< "Calling eraseAfter() to delete element with integer 10"<< endl << endl;
    A.eraseAfter();
    
    cout << "List A is: " << endl;
    cout << A << endl;

    cout<<endl<<endl;
    
    
    // testing clean up
    cout << "Inserting into A" << endl;
    A.moveFront();
    
    A.insertAfter(10);
    
    A.moveNext();
    A.moveNext();
    
    A.insertAfter(10);
    
    A.moveNext();
    A.moveNext();
    A.moveNext();
    A.moveNext();
    A.moveNext();
    
    A.insertAfter(10);
    A.insertAfter(3);
    A.insertAfter(5);
    A.insertAfter(5);
    
    cout << "List A is: " << endl;
    cout << A << endl << endl;
    
    cout << "Calling cleanup()" <<endl << endl;
    A.cleanup();
    
    cout << "List A is: " << endl;
    cout << A << endl;
    
    cout<<endl<<endl<<endl;
    
    
    // testing clear()
    cout << "Calling clear() on list A" << endl << endl;
    A.clear();
    cout << "List A is: " << endl;
    cout << A << endl;
    
    cout<<endl<<endl<<endl;
    
    
    // testing concat
    cout << "Inserting into A" << endl;
    
    count = 1;
    A.moveFront();
    while(count <= 7) {
        A.insertBefore(count);
        count++;
    }
    
    cout << "List A is: " << endl;
    cout << A << endl;
    
    cout << "Calling concat() to concat list A and list l" << endl << endl;
    B = A.concat(l);
    
    cout << "The concatenated list B is: " << endl;
    cout << B << endl;
    
    cout<<endl<<endl<<endl;
    
    
    // testing equals() and copy()
    cout << "Testing equals(), copy(), operator==() and operator=()" << endl;
    cout << "Creating list C which is a copy of A" << endl;
    C = A;
    cout << "List C is: " << endl;
    cout << C << endl;
    
    
    cout << "List l and A are the same: ";
    if (l == A) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    cout << "List A and C are the same: ";
    if (C == A) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    cout<<endl<<endl<<endl;
    
    cout<< "Done.\n";

    return 0;
}
