//
//  BigInteger.c
//  pa2
//
//  Created by Maiah Pardo on 10/20/20.
//

#include "BigInteger.h"
#include "List.h"
#include <math.h>
#include <string.h>

#define POWER 9 // 1 <= POWER <= 9
#define BASE (long)(pow(10,POWER) + 0.01)

// prototypes --------------------------------------------------------------------------



// structs -----------------------------------------------------------------------------

// private BigInteger type
typedef struct BigIntegerObj{
    int sign; // 1, -1, or 0
    List magnitude;
} BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger() {
    BigInteger B = malloc(sizeof(BigIntegerObj)); // allocate space for BigInt Obj
    B->sign = 0; // no sign initially
    B->magnitude = newList(); // initialize new empty list
    return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN) {
    if ((pN != NULL && *pN != NULL)) {
        freeList(&((*pN)->magnitude));
        (*pN)->magnitude = NULL;
        free(*pN);
        *pN = NULL;
    }
}


// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N) {
    if (N == NULL) {
        fprintf(stderr, "BigInteger Error: calling sign() on NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "BigInteger Error: calling compare() on one or both NULL BigInteger references\n");
        exit(EXIT_FAILURE);
    }
    
    
    return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "BigInteger Error: calling equals() on one or both NULL BigInteger references\n");
        exit(EXIT_FAILURE);
    }
    
    int isEqual = 1;
    
    if (A->sign == B->sign) { // signs are equal
        if (length(A->magnitude) == length(B->magnitude)) { // lengths are equal
            // check to see if all elements match up (are equal)
            moveFront(A->magnitude);
            moveFront(B->magnitude);
            while(index(A->magnitude) >= 0) {
                // A and B magnitudes are the same length
                // so if A finished traversing, B has also finished
                if (get(A->magnitude) != get(B->magnitude)) {
                    isEqual = 0;
                    break;
                }
                moveNext(A->magnitude);
                moveNext(B->magnitude);
            }
        } else { // lengths of magnitudes are not equal
            isEqual = 0;
        }
    } else { // signs are not the same
        isEqual = 0;
    }
    
    return isEqual;
}


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N);

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N);


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s);

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N);

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B);

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B);

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B);

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B);

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);


// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N);
