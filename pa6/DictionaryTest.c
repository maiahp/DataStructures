/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA5
* DictionaryTest.c
* Test module for the Dictionary ADT
*/

#include <stdio.h>
#include "Dictionary.h"

int main() {
    printf("Dictionary Test\n\n");
    
    printf("Creating a non-unique Dictionary D\n");
    Dictionary D = newDictionary(0);
    
    printf("Inserting into D.\n\n");
    insert(D, "one", 1);
    insert(D, "two", 2);
    insert(D, "three", 3);
    insert(D, "four", 4);
    insert(D, "five", 5);
    insert(D, "six", 6);
    insert(D, "seven", 7);
    insert(D, "eight", 8);
    insert(D, "nine", 9);
    insert(D, "ten", 10);
    insert(D, "eleven", 11);
    insert(D, "twelve", 12);
    insert(D, "thirteen", 13);
    insert(D, "thirteen", 14);
    insert(D, "fourteen", 15);
    insert(D, "fifteen", 16);
    insert(D, "sixteen", 17);
    insert(D, "seventeen", 18);
    insert(D, "eighteen", 19);
    insert(D, "nineteen", 20);
    insert(D, "twenty", 21);
    insert(D, "twenty", 22);
    insert(D, "twenty one", 23);
    insert(D, "twenty two", 24);
    insert(D, "twenty three", 25);
    insert(D, "twenty four", 26);
    insert(D, "twenty five", 27);
    insert(D, "twenty six", 28);
    insert(D, "twenty seven", 29);
    insert(D, "twenty eight", 30);
    
    printf("The Dictionary D is: \n");
    printDictionary(stdout, D);
    printf("\n\n");
    
    printf("The size of D is %d\n", size(D));
    
    if (getUnique(D) == 0) {
        printf("Unique: 0 (false)\n\n");
    } else {
        printf("Unique: 1 (true)\n\n");
    }
    
    printf("Testing lookup():\n");
    printf("Key: 'seventeen' has the Value: %d\n", lookup(D, "seventeen"));
    printf("Key: 'twenty eight' has the Value: %d\n", lookup(D, "twenty eight"));
    printf("Key: 'one' has the Value: %d\n", lookup(D, "one"));
    printf("Key: 'zero', which does not exist, has the Value: %d\n", lookup(D, "zero"));
    
    printf("\nDeleting Key: 'seventeen' from D\n");
    delete(D, "seventeen");
    printf("D is now: \n");
    printDictionary(stdout, D);

    printf("\n\nDeleting Key: 'thirteen' from D\n");
    delete(D, "thirteen");
    printf("D is now: \n");
    printDictionary(stdout, D);
    
    
    printf("\n\nTesting forward traversal.\n");
    printf("%d\n", beginForward(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("The current key is: %s\n", currentKey(D));
    printf("The current value is: %d\n", currentVal(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("%d\n", next(D));
    printf("The current key is: %s\n", currentKey(D));
    printf("The current value is: %d\n", currentVal(D));
    
   
   
    printf("\n\nTesting reverse traversal.\n");
    printf("%d\n", beginReverse(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("The current key is: %s\n", currentKey(D));
    printf("The current value is: %d\n", currentVal(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
    printf("%d\n", prev(D));
   
    printf("\n\nTesting makeEmpty():\n");
    makeEmpty(D);
    printf("The Dictionary D is now: \n");
    printDictionary(stdout, D);
    
    printf("\n\nInserting into D\n");
    insert(D, "one", 1);
    insert(D, "two", 2);
    insert(D, "three", 3);
    insert(D, "four", 4);
    
    printf("D is now:\n");
    printDictionary(stdout, D);
    
    printf("\n\nCalling freeDictionary()");
    freeDictionary(&D);
    
    printf("\n\nDone.\n\n");
    
    return 0;
}



