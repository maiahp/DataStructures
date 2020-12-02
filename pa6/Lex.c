/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Lex.c
* Client module for the Dictionary ADT
*/


#include <stdio.h>
#include "Dictionary.h"

int main(int argc, const char * argv[]) {
    Dictionary D = newDictionary(1);
    insert(D, "hallo", 1);
    insert(D, "there", 2);
    insert(D, "abc", 3);
    insert(D, "def", 4);
    
    lookup(D, "hallo");
    
    delete(D, "hallo");
    delete(D, "abc");
    delete(D, "def");
    delete(D, "there");
    // there is an issue when deleting "there"
    // for some reason, when D->root = D->NIL
    // D->root's parent is set to the "there" node
    // and still exists in allocated space AFTER "there" node is deleted
    freeDictionary(&D);
    
    return 0;
}
