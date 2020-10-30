/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA2
* Arithmetic.c
* Client module for the Big Integer ADT
*/

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "BigInteger.h"

int main(int argc, const char * argv[]) {
    FILE *in, *out;

    if ( argc != 3 ) {
        fprintf(stderr, "Usage: %s <input file> <outputfile>\n", argv[0]);
        exit(1);
    }
    // open files for reading and writing
    in = fopen(argv[1], "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    /*
    // hardcoding the filename (testing):
    in = fopen("in1.txt", "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", "in1.txt"); // print error message to stderr
        exit(1);
    }
    out = fopen("out1.txt", "w");
    if(out==NULL) {
        printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
        exit(1);
    }
    // end (testing)
    */
    
    int strSize1, strSize2;
    char *bigIntStr1, *bigIntStr2;
    
    // grab first line of the file as an int
    fscanf(in, "%d\n", &strSize1); // %d\n means any \n will be ignored
    bigIntStr1 = (char *)malloc(strSize1+2); // create a string of size strSize1, +2 so that all characters are grabbed
    
    // grab second line of file as a string
    fscanf(in, "%s\n", bigIntStr1);
    
    
    // grab third line of file as an int
    fscanf(in, "%d\n", &strSize2);
    
    // grab fourth line of file as a string
    bigIntStr2 = (char *)malloc(strSize2+2);
    fscanf(in, "%s\n", bigIntStr2);
    
    fclose(in); // done reading in file
    
    
    BigInteger A, B, S, D, P, M, R;
    A = stringToBigInteger(bigIntStr1);
    B = stringToBigInteger(bigIntStr2);
    
    free(bigIntStr1);
    free(bigIntStr2);
    
    
    // compute the values
    
    // A
    printBigInteger(out, A);
    fprintf(out, "\n\n");
    
    // B
    printBigInteger(out, B);
    fprintf(out, "\n\n");
    
    // A + B
    S = sum(A, B);
    printBigInteger(out, S);
    fprintf(out, "\n\n");
    
    // A - B
    D = diff(A, B);
    printBigInteger(out, D);
    fprintf(out, "\n\n");
    freeBigInteger(&D);
    
    
    // A - A
    D = diff(A, A);
    printBigInteger(out, D);
    fprintf(out, "\n\n");
    
    // 3A - 2B
    P = stringToBigInteger("3");
    multiply(P, P, A); // P = 3A
    
    M = stringToBigInteger("2");
    multiply(M, M, B); // M = 2B
    
    D = diff(P, M);
    printBigInteger(out, D);
    fprintf(out, "\n\n");
    freeBigInteger(&P);
    freeBigInteger(&M);
    
    // AB
    P = prod(A, B);         
    printBigInteger(out, P);
    fprintf(out, "\n\n");
    freeBigInteger(&P);
    
    // A^2
    P = prod(A, A);
    printBigInteger(out, P);
    fprintf(out, "\n\n");
    freeBigInteger(&P);
    
    // B^2
    P = prod(B, B);
    printBigInteger(out, P);
    fprintf(out, "\n\n");
    freeBigInteger(&P);
    
    // 9A^4 + 16B^5
    P = prod(A, A); // P = A^2
    multiply(P, P, P); // P = A^2 * A^2 = A^4
    R = stringToBigInteger("9");
    multiply(P, P, R); // P = 9A^4
    
    M = prod(B, B); // M = B^2
    multiply(M, M, M); // M = B^2 * B^2 = B^4
    multiply(M, M, B); // M = B^4 * B = B^5
    R = stringToBigInteger("16");
    multiply(M, M, R); // M = 16B^5
    
    add(P, P, M); // P = 9A^4 + 16B^5
    printBigInteger(out, P);
    
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&S);
    freeBigInteger(&D);
    freeBigInteger(&P);
    freeBigInteger(&M);
    freeBigInteger(&R);
    
    fclose(out);
    return 0;
 
}


