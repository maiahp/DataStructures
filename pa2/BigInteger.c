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

#define POWER 5 // 1 <= POWER <= 9
#define BASE (long)(pow(10,POWER) + 0.01)

// prototypes --------------------------------------------------------------------------
void normalize(BigInteger);
void deleteLeadingZeros(BigInteger);


// structs -----------------------------------------------------------------------------

// private BigInteger type
typedef struct BigIntegerObj{
    int sign; // 1, -1, 0  (sign 0 means the number is 0)
    List magnitude; // front of list is LSD ---- back of list is MSD
                    // the true value of each list element = data * 10^n (n = its index in the list)
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
    
    int returnVal = 0;
    
    if (equals(A, B) == 1) { // catches the case if A and B are both 0
        returnVal = 0;
        
    } else { // A is not equal to B
        
        // case: If the sign of either A or B is zero
        // both signs cannot be 0, if they were, A = B, which would have been caught above
        if (sign(A) == 0 || sign(B) == 0) {
            if (sign(A) == 0) {
                if (sign(B) == 1) {
                    // A < B
                    returnVal = -1;
                } else { // sign(B) is -1
                    // A > B
                    returnVal = 1;
                }
            } else if (sign(B) == 0) {
                if (sign(A) == 1) {
                    // A > B
                    returnVal = 1;
                } else { // sign(A) is -1
                    // A < B
                    returnVal = -1;
                }
            }
        } else { // case: neither sign is 0
            if (sign(A) != sign(B)) { // signs are not the same
                if (sign(A) == 1) { // A is 1 so B is -1
                    // A > B
                    returnVal = 1;
                } else { // sign(A) is -1
                    // A < B
                    returnVal = -1;
                }
            } else { // case: A and B have the same sign
                
                // case: If A and B are both positive, the larger magnitude is larger
                if (sign(A) == 1) { // both signs are +1
                    
                    // check lengths - larger length is the larger num
                    if (length(A->magnitude) > length(B->magnitude)) {
                        // A > B
                        returnVal = 1;
                    } else if (length(A->magnitude) < length(B->magnitude)) {
                        // A < B
                        returnVal = -1;
                    } else {
                        // lengths are the same - check each element
                        
                        // traverse the lists from MSD (back) to LSD (front)
                        // the first digit to be larger is the larger number
                        moveBack(A->magnitude);
                        moveBack(B->magnitude);
                        
                        while (index(A->magnitude) >= 0) {
                            if (get(A->magnitude) > get(B->magnitude)) {
                                // A > B
                                returnVal = 1;
                            } else if (get(A->magnitude) < get(B->magnitude)) {
                                // A < B
                                returnVal = -1;
                            } else {
                                // the digits are equal, move to next element
                                movePrev(A->magnitude);
                                movePrev(B->magnitude);
                            }
                        }
                    }
                } else {  // case: If A and B are both negative, the smaller magnitude is larger
                    
                    // check lengths - smaller length is the larger num
                    if (length(A->magnitude) > length(B->magnitude)) {
                        // A < B
                        returnVal = -1;
                    } else if (length(A->magnitude) < length(B->magnitude)) {
                        // A > B
                        returnVal = 1;
                    } else {
                        // lengths are the same - check each element
                        moveBack(A->magnitude);
                        moveBack(B->magnitude);
                        
                        // traverse the lists from MSD (back) to LSD (front)
                        // the first digit to be larger is the larger number
                        while (index(A->magnitude) >= 0) {
                            if (get(A->magnitude) > get(B->magnitude)) {
                                // A < B
                                returnVal = -1;
                            } else if (get(A->magnitude) < get(B->magnitude)) {
                                // A > B
                                returnVal = 1;
                            } else {
                                // the digits are equal, move to next element
                                movePrev(A->magnitude);
                                movePrev(B->magnitude);
                            }
                        }
                    }
                }
            }
        }
    }
    return returnVal;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "BigInteger Error: calling equals() on one or both NULL BigInteger references\n");
        exit(EXIT_FAILURE);
    }
    // note: the case where a sign is 0 will still work
    
    int isEqual = 1;
    
    if (A->sign == B->sign) { // signs are equal
        if (length(A->magnitude) == length(B->magnitude)) { // lengths are equal
            // check to see if all elements match up (are equal)
            moveBack(A->magnitude);
            moveBack(B->magnitude);
            while(index(A->magnitude) >= 0) {
                // A and B magnitudes are the same length
                // so if A finished traversing, B has also finished
                if (get(A->magnitude) != get(B->magnitude)) {
                    isEqual = 0;
                    break;
                }
                movePrev(A->magnitude);
                movePrev(B->magnitude);
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
void makeZero(BigInteger N) {
    if (N == NULL) {
        fprintf(stderr, "BigInteger Error: calling makeZero() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    clear(N->magnitude); // delete all elements in magnitude
    N->sign = 0; // set sign as 0
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
    if (N == NULL) {
        fprintf(stderr, "BigInteger Error: calling negate() on a NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    N->sign = (N->sign * -1); // if sign is 0, it stays 0
}


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s) {
    
    // note:
    // iterate through entire string from right side (LSD) to left side (MSD)
    // we grab from LSD to MSD because the last grab may not have enough characters to = num POWER
    // starting from LSD to MSD-1, we grab string in portions of num POWER
    // leading zeros can be ignored (and will be ignored) ex: atol("006") = 6
    // if power == 2, 2 digits to an element, if power == 9, 9 digits to an element
    // The list looks like: LSD (front) ------- MSD (back)
    // the true value of each list element = data * 10^n (n = its index in the list)
    
    BigInteger B = newBigInteger();
    
    int stringLen = (int)strlen(s); // strlen starts at 1
    
    if (stringLen == 0) { // if string is "", number is 0
        return B;
    }
    
    // case: the optional signs '+' or '-' or neither at the beginning of s
    int hasSign;
    
    if (s[0] == '-') { // first element of string is '-'
        B->sign = -1;
        hasSign = 1;
    } else if (s[0] == '+') { // first elem of string is '+'
        B->sign = 1;
        hasSign = 1;
    } else { // no sign, num is positive
        B->sign = 1;
        hasSign = 0;
    }
    
    // iterate through string s
    int numElementsLeft; //  the num of elements left to insert into magnitude list
    int numCharsInLastElem; // the chars left over in the last element to insert - MSD place of s
    
    // Determine number of chars left over in the last partition of s
    if (hasSign == 0) { // if there is no sign in s
        numElementsLeft = stringLen/POWER; // number of partitions of s = (the length of s / num of chars in each grab)
        if (stringLen % POWER == 0) { // if there is no remainder, all partitions have equal num of chars
            numElementsLeft--;
        }
        numCharsInLastElem = stringLen - (numElementsLeft * POWER); // calculate number of chars in the last element
        
    } else { // s has a sign
        numElementsLeft = (stringLen - 1)/POWER; // -1 from stringLen because don't include the sign
        if ((stringLen-1) % POWER == 0) {
            numElementsLeft--;
        }
        numCharsInLastElem = stringLen - (numElementsLeft * POWER); // calculate number of chars in the last element
    }
    
    //printf("s is: %s\n", s);
    
    char* strElem = NULL; // holds POWER number of elements + 1 for the null terminator at the end
                          // for all insertions except for the last insertion (MSD)
    
    int i = stringLen-1; // total num chars in s, will count down to 0 when iterating through s
                       // start at right side (LSD and move to left side (MSD) of s)
    while (i >= 0) { // while still iterating through chars in s (i = stringLen to 0)
        
        if (numElementsLeft == 0) { // last grab of string s - grabbing the MSD (left side)
            
            strElem = (char *)malloc(numCharsInLastElem+1); // allocate space for the string element
            memset(strElem, '\0', numCharsInLastElem+1); // add null terminator character in last place
            
            // iterate through number of remaining chars
            // save into strElem
            int k = numCharsInLastElem-1;
            while (k >= 0) {
                strElem[k] = s[i];
                i--; // decrement index of s
                k--; // decrement num of chars remaining
            }
            
            // when while exits, strElem holds the last char (MSD of s)
            
            // strElem may contain a '-', or '+'
            // search for these and replace with a zero (a leading zero won't matter)
            if (strElem[0] == '-' || strElem[0] == '+') {
                strElem[0] = '0'; // replace with leading zero
            }
            
            //printf("s[%d] = %s\n", i, strElem); // testing
            
        } else { // we are not grabbing the last partition of s
                 // always grab number POWER of elements (+1 for null terminator) for each partition (each strElem)
            strElem = (char *)malloc(POWER+1);
            memset(strElem, '\0', POWER+1);
            
            int k = POWER-1; // k is num of chars we are grabbing for each strElem - k = POWER to 0
            while (k >= 0) { // while there are still chars to grab
                strElem[k] = s[i]; // save chars in s into strElem
                i--; // decrement index of s
                k--; // decrement num of chars to grab
            }
            
            //printf("s[%d] = %s\n", i, strElem); // testing
        }
        
        // if-else exits, finished grabbing and storing one partition of s into strElem

        numElementsLeft--; // decrement num elems left to grab from s
        
        long numToInsert = atol(strElem); // convert strElem to a long
        append(B->magnitude, numToInsert); // insert into magnitude
        
        free(strElem);
        strElem = NULL;
            
        }
    
    return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
    BigInteger copyN = newBigInteger();
    copyN->sign = N->sign;
    
    // note:
    // cannot use copyList() method here
    // copyList allocates space on heap for a new List
    // when calling newBigInteger(), space on heap is already allocated for a new list
    // save values from N to copyN
    
    moveFront(N->magnitude);
    while(index(N->magnitude) >= 0) {
        append(copyN->magnitude, get(N->magnitude)); // save curr data into copyN
        moveNext(N->magnitude);
    }
    return copyN;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
    if (S == NULL) {
        printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == A || S == B) {
        // then we have to free S but save its data
        BigInteger temp = sum(A, B);
        S->sign = sign(temp);
        
        freeList(&(S->magnitude)); // delete S's list
        S->magnitude = copyList(temp->magnitude); // must create a copy or when we free temp, this list will be null
        freeBigInteger(&temp);
        
    } else { // S is not A or B
        // delete S
        freeBigInteger(&S);
        
        // sum returns a new Big Integer which will now be S
        S = sum(A, B);
    }
    
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling sum() on one or both NULL List references\n");
        exit(EXIT_FAILURE);
    }
    
    /* NOTE:
     if A is the same Big Integer as B
     then it is the same reference, and whenever anything happens with A's cursor
     it will also move B's cursor, since A = B
     So A must be made into a copy
     So that we can use A and B = copyA
     */
    
    int A_equals_B = 0;
    if (A == B) { // A is the same reference as B
        A_equals_B = 1;
        B = copy(A); // copy returns a new BigInteger (must be freed later)
                     // B now points to a copy of A (not A itself)
    }
    
    BigInteger S = newBigInteger(); // S is the sum of A + B
    
    moveFront(A->magnitude);
    moveFront(B->magnitude);
    
    long sum = 0; // the addition of A and B's corresponding elements
    
    while(index(A->magnitude) >= 0 || index(B->magnitude) >= 0) {
        // if one list1 is longer than the other, it is as if adding (elem1 + 0)
        if (index(A->magnitude) >= 0) { // if A's cursor is defined
            sum += sign(A) * get(A->magnitude);
        }
        if (index(B->magnitude) >= 0) { // if B's cursor is defined
            sum += sign(B) * get(B->magnitude);
        }
        
        // add result to S magnitude list
        prepend(S->magnitude, sum);
        
        sum = 0;
        moveNext(A->magnitude);
        moveNext(B->magnitude);
    }
    
    if (A_equals_B == 1) { // if A and B were the same reference
        freeBigInteger(&B); // delete the copy's data
        B = A; // return B's value to its initial value, which is A
    }
    
    normalize(S);
    return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
    if (D == NULL) {
        printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    
    if (D == A || D == B) {
        // then we have to free D but save its data
        BigInteger temp = diff(A, B);
        D->sign = sign(temp);
        
        freeList(&(D->magnitude)); // delete D's list
        D->magnitude = copyList(temp->magnitude); // must create a copy or when we free temp, this list will be null
        freeBigInteger(&temp);
        
    } else { // D is not A or B
        // delete D
        freeBigInteger(&D);
        
        // diff returns a new Big Integer which will now be D
        D = diff(A, B);
    }
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling diff() on one or both NULL BigInteger references\n");
        exit(EXIT_FAILURE);
    }
    
    int A_equals_B = 0;
    if (A == B) { // A is the same reference as B
        A_equals_B = 1;
        B = copy(A); // copy returns a new BigInteger (must be freed later)
                     // B now points to a copy of A (not A itself)
    }
    
    BigInteger D = newBigInteger();
    
    moveFront(A->magnitude);
    moveFront(B->magnitude);
    
    long diff = 0; // the addition of A and B's corresponding elements
    
    while(index(A->magnitude) >= 0 || index(B->magnitude) >= 0) {
        // if one list1 is longer than the other, it is as if adding (elem1 + 0)
        if (index(A->magnitude) >= 0) { // if A's cursor is defined
            diff += sign(A) * get(A->magnitude);
        }
        if (index(B->magnitude) >= 0) { // if B's cursor is defined
            diff -= sign(B) * get(B->magnitude);
        }
        
        // add result to S magnitude list
        prepend(D->magnitude, diff);
        
        diff = 0;
        moveNext(A->magnitude);
        moveNext(B->magnitude);
    }
    
    if (A_equals_B == 1) { // if A and B were the same reference
        freeBigInteger(&B); // delete the copy's data
        B = A; // return B's value to its initial value, which is A
    }
    
    normalize(D);
    return D;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
    if (P == NULL) {
        printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    if (P == A || P == B) {
        // then we have to free P but save its data
        BigInteger temp = prod(A, B);
        P->sign = sign(temp);
        
        freeList(&(P->magnitude)); // delete P's list
        P->magnitude = copyList(temp->magnitude); // must create a copy or when we free temp, this list will be null
        freeBigInteger(&temp);
        
    } else { // P is not A or B
        // delete P
        freeBigInteger(&P);
        
        // prod returns a new Big Integer which will now be P
        P = prod(A, B);
    }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL) {
        printf("BigInteger Error: calling prod() on one or both NULL BigInteger references\n");
        exit(EXIT_FAILURE);
    }
    
    int A_equals_B = 0;
    if (A == B) { // A is the same reference as B
        A_equals_B = 1;
        B = copy(A); // copy returns a new BigInteger (must be freed later)
                     // B now points to a copy of A (not A itself)
    }
    
    // note:
    /*
     to multiply,
     must have two while loops: A * B
                  A1     A2     A3
               x  0      B1     B2
              ------------------------
                 B2A1   B2A2   B2A3
           B1A1  B1A2   B1A3     0
     0*A1  0*A2   0*A3     0     0
     
     ^ Now add up the result
     
     the lists look like (LSD)(front) ----- (MSD)(back)
     - so iteration goes from front to back for both
     
     multiply each element of B by all elements of A
     - so iterating B is the outer while loop
     - iterating A is the inner
     
     */
    
    BigInteger P = newBigInteger();
    
    if (sign(A) == sign(B)) { // both signs are + or -
        P->sign = 1; // sign of P is always + when both signs are the same
    } else { // signs are not the same
        P->sign = -1; // sign of P is always - when signs are not the same
    }
    
    BigInteger temp = newBigInteger();
    long product = 0;
    int shiftCount = 0; // after every row of multiplication
                            // A zero is added to the LSD place (front of list)
                            // for 0th row of multiplication, shift is 0
                            // for 1st row of multiplication, shift is 1 and so on
    
    moveFront(B->magnitude);
    while(index(B->magnitude) >= 0) {
        long B_data = get(B->magnitude);
        
        moveFront(A->magnitude);
        while(index(A->magnitude) >= 0) {
            long A_data = get(A->magnitude);
            
            product = B_data * A_data;
            prepend(temp->magnitude, product);
            
            moveNext(A->magnitude);
        }
        
        // when while exits, there is a row of multiplication done
        add(P, temp, P); // add temp with P and save it in P
        
        // once finished with a row of multiplication
        // add a zero to the LSD place (front of list) of B
        shiftCount++;
        
        int i = 0;
        while(i < shiftCount) {
            prepend(B->magnitude, (long)0);
            i++;
        }
        
        moveNext(B->magnitude);
    }
    
    
    if (A_equals_B == 1) { // if A and B were the same reference
        freeBigInteger(&B); // delete the copy's data
        B = A; // return B's value to its initial value, which is A
    }
    
    normalize(P);
    return P;
}

// normalize()
// Takes in a BigInteger and normalizes it with respect to its base.
void normalize(BigInteger B) {
    // if B has a sign, we do not update sign (its been in multiplcation)
    // have to double check that MSD place doesn't have a sign
    
    // if B has no sign, we give it a sign based on the MSD (if MSD is negative, entire thing is negative)
    
    
    // delete leading zeros in normalize - after the final number is done
}

// deleteLeadingZeros
// Removes the leading zeros in the Most Significant Digits place of the BigInteger.
void deleteLeadingZeros(BigInteger B) {
    
    // B's sign is 0 and B has no elements, then we do nothing
    if (B->sign == 0) {
        if (length(B->magnitude) == 0) {
            return;
        }
    }
    
    // start at MSD place in B's magnitude
    moveBack(B->magnitude);
    while (B->magnitude >= 0) {
        long elem = get(B->magnitude);
        if (elem == 0) {
            delete(B->magnitude); // deletes the current cursor elem
            moveBack(B->magnitude); // must reinitialize the cursor
        } else { // the first element that is not zero
            break;
        }
        movePrev(B->magnitude);
    }
    // if we have exited the while, all elements have been deleted (the BigInt is 0)
    B->sign = 0; // set sign to 0 since it was not already
}


// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N) {
    if (N == NULL) {
        fprintf(stderr, "BigIntegerError: calling printBigInteger() on NULL BigInteger reference\n");
        exit(EXIT_FAILURE);
    }
    
    if (sign(N) == 0) { // if N's magnitude is 0
        fprintf(out, "0");
        return;
    }
    if (N->sign == -1) { // if N's sign is -
        fprintf(out, "-");
    }
    
    // delete the leading zeros before printing
    
    // print MSD to LSD - print back to front
    moveBack(N->magnitude);
    while(index(N->magnitude) >= 0) {
        fprintf(out, "%0*ld", POWER, get(N->magnitude)); // POWER gets put in *
        movePrev(N->magnitude);
    }
}
