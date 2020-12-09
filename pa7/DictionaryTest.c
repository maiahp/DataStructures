/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* DictionaryTest.c
* Test Client for Dictionary ADT
* 
*/

#include <stdio.h>
#include "Dictionary.h"


int main() {
    printf("Dictionary Test\n\n");
    
    printf("Creating a non-unique Dictionary D\n");
    Dictionary D = newDictionary(0);
    
    int val = 1;
    int* val_ptr = &val;
    
    printf("Inserting into D.\n\n");
    insert(D, "one", val_ptr);
    insert(D, "two", val_ptr);
    insert(D, "three", val_ptr);
    insert(D, "four", val_ptr);
    insert(D, "five", val_ptr);
    insert(D, "six", val_ptr);
    insert(D, "seven", val_ptr);
    insert(D, "eight", val_ptr);
    insert(D, "nine", val_ptr);
    insert(D, "ten", val_ptr);
    insert(D, "eleven", val_ptr);
    insert(D, "twelve", val_ptr);
    insert(D, "thirteen", val_ptr);
    insert(D, "thirteen", val_ptr);
    insert(D, "fourteen", val_ptr);
    insert(D, "fifteen", val_ptr);
    insert(D, "sixteen", val_ptr);
    insert(D, "seventeen", val_ptr);
    insert(D, "eighteen", val_ptr);
    insert(D, "nineteen", val_ptr);
    insert(D, "twenty", val_ptr);
    insert(D, "twenty", val_ptr);
    insert(D, "twenty one", val_ptr);
    insert(D, "twenty two", val_ptr);
    insert(D, "twenty three", val_ptr);
    insert(D, "twenty four", val_ptr);
    insert(D, "twenty five", val_ptr);
    insert(D, "twenty six", val_ptr);
    insert(D, "twenty seven", val_ptr);
    insert(D, "twenty eight", val_ptr);
    
    printf("Printing Pre-Order: \n");
    printDictionary(stdout, D, "pre");
    printf("\n\n");
    
    printf("Printing In-Order: \n");
    printDictionary(stdout, D, "in");
    printf("\n\n");
    
    printf("Printing Post-Order: \n");
    printDictionary(stdout, D, "post");
    printf("\n\n");
    
    printf("The size of D is %d\n", size(D));
    
    printf("D is Unique: ");
    if (getUnique(D) == 0) {
        printf("False");
    } else {
        printf("True");
    }
    printf("\n\n");
    
    printf("Testing lookup():\n");
    int* value = lookup(D, "seventeen");
    int v = *value;
    printf("Key: 'seventeen' has the Value: %d\n\n", v);
    
    val_ptr = lookup(D, "twenty eight");
    v = *value;
    printf("Key: 'twenty eight' has the Value: %d\n", v);
    
    printf("Deleting Key: 'seventeen' from D\n\n");
    delete(D, "seventeen");
    printf("D is now (In-Order): \n");
    printDictionary(stdout, D, "in");

    printf("\nDeleting Key: 'five' from D\n");
    delete(D, "five");
    printf("D is now (In-Order): \n");
    printDictionary(stdout, D, "in");
    
    printf("\nTesting forward traversal.\n");
    beginForward(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    printf("\nThe current key is: %s", currentKey(D));
    val_ptr = currentVal(D);
    val = *val_ptr;
    printf("\nThe current value is: %d", val);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    next(D);
    printf("\nThe current key is: %s", currentKey(D));
    val_ptr = currentVal(D);
    val = *val_ptr;
    printf("\nThe current value is: %d", val);
   
    printf("\n\nTesting reverse traversal.\n");
    beginReverse(D);
    prev(D);
    prev(D);
    prev(D);
    prev(D);
    prev(D);
    prev(D);
    prev(D);
    prev(D);
    printf("\nThe current key is: %s", currentKey(D));
    val_ptr = currentVal(D);
    val = *val_ptr;
    printf("\nThe current value is: %d", val);
   
    printf("\n\nTesting makeEmpty():\n");
    makeEmpty(D);
    printf("The Dictionary D is now (In-Order): \n");
    printDictionary(stdout, D, "in");
    printf("\n\n");
    
    printf("Calling freeDictionary()");
    freeDictionary(&D);
    
    printf("\n\nDone.\n\n");
    
    return 0;
}



