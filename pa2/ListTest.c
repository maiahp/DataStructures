/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA2
* ListTest.c
* Test module for the List ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    printf("List Test\n");
    List A = newList();
    List B = newList();
    List C = newList();
    List D = newList();

    // add values
    append(A, 98767898);
    append(A, 876);
    append(A, -55);
    prepend(B, 100);
    prepend(B, 789287834732847);
    prepend(B, -65);
    prepend(B, -147500050);

     
    printf("\nList A: ");
    printList(stdout, A);
    printf("\nList B: ");
    printList(stdout, B);
    printf("\n");

     
    // Testing insertAfter(), insertBefore(), set()
    moveFront(A);
    moveFront(B);
     
    printf("\n\nTesting insertAfter(): ");
    insertAfter(A, 123456);
    insertAfter(B, 123456);
    printf("\nA is: ");
    printList(stdout, A);
    printf("\nB is: ");
    printList(stdout, B);
     
    moveNext(A); moveNext(A);
    moveNext(B); moveNext(B);
     
    printf("\n\nTesting insertBefore(): ");
    insertBefore(A, 123456);
    insertBefore(B, 123456);
    printf("\nA is: ");
    printList(stdout, A);
    printf("\nB is: ");
    printList(stdout, B);
     
    movePrev(A);
    movePrev(B);
     
    set(A, 7);
    set(B, 9);
    printf("\n\nA is: ");
    printList(stdout, A);
    printf("\nB is: ");
    printList(stdout, B);
     
    // Testing front(), back(), and get()
    printf("\n\nFront of A is: %ld", front(A));
    printf("\nFront of B is: %ld", front(B));
    printf("\nBack of A is: %ld", back(A));
    printf("\nBack of B is: %ld", back(B));
     
    movePrev(A);
    movePrev(B); movePrev(B);
    printf("\nA: Value at index %d is: %ld", index(A), get(A));
    printf("\nB: Value at index %d is: %ld", index(B), get(B));
     
    // Testing deleteFront(), deleteBack(), delete()
    printf("\n\nCalling deleteFront() on A");
    deleteFront(A);
    printf("\nA is: ");
    printList(stdout, A);
     
    printf("\nCalling deleteBack() on A");
    deleteBack(A);
    printf("\nA is: ");
    printList(stdout, A);
     
    moveFront(A);
    moveNext(A);
    printf("\nCalling delete() on element in index %d in A.", index(A));
    delete(A);
    printf("\nA is: ");
    printList(stdout, A);
     
    // Testing copyList(), concatList()
    printf("\n\nCopying B into C: ");
    C = copyList(B);
    printf("\nC is: ");
    printList(stdout, C);
     
    printf("\n\nCalling concatList for A and B: ");
    D = concatList(A, B);
    printf("\nD is: ");
    printList(stdout, D);

    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);

    printf("\nDone.\n");
     
    return 0;
}

