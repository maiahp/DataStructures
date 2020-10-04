/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA1
* Lex.c
* Client module for the List ADT
*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

int main(int argc, const char * argv[]) {
    List L = newList();
    append(L, 2);
    prepend(L, 1);
    
    freeList(&L);
}
