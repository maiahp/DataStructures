/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA2
* BigIntegerTest.c
* Test module for the Big Integer ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"

int main(){
    printf("BigInteger Testing\n\n");

    char str1[] = "123456";
    char str2[] = "99999999";
    char str3[] = "-111111111111";
    char str4[] = "150005000005500000901070400003";
    char str5[] = "-102030405060";
    char str6[] = "123456";

    BigInteger A, B, C, D, E, F, G;

    A = stringToBigInteger(str1);
    B = stringToBigInteger(str2);
    C = stringToBigInteger(str3);
    D = stringToBigInteger(str4);
    E = stringToBigInteger(str5);
    F = stringToBigInteger(str6);

    printf("A is: ");
    printBigInteger(stdout, A);
    printf("\nB is: ");
    printBigInteger(stdout, B);
    printf("\nC is: ");
    printBigInteger(stdout, C);
    printf("\nD is: ");
    printBigInteger(stdout, D);
    printf("\nE is: ");
    printBigInteger(stdout, E);
    printf("\nF is: ");
    printBigInteger(stdout, F);
    printf("\nG is uninitialized.");

    // testing Negate() and sign()
    printf("\n\nThe sign of B is: %d", sign(B));
    printf("\nNegate B: ");
    negate(B);
    printBigInteger(stdout, B);
    printf("\nThe new sign of B is: %d", sign(B));

    // testing compare() and equals()
    printf("\n\ncompare(A, A) returns: %d", compare(A,A));
    printf("\ncompare(A, F) returns: %d", compare(A, F));
    printf("\ncompare(A, C) returns: %d", compare(A, C));
    printf("\ncompare(E, F) returns: %d", compare(E, F));
    printf("\n\nequals(B, B) returns: %d", equals(B, B));
    printf("\nequals(A, F) returns: %d", equals(A, F));

    // testing makeZero()
    printf("\n\nCalling makeZero(B): ");
    makeZero(B);
    printf("\nB is: ");
    printBigInteger(stdout, B);
    printf("\nThe sign of B is: %d", sign(B));

    // testing copy()
    printf("\n\nCalling copy(C) and saving into G: ");
    G = copy(C);
    printf("\nG is: ");
    printBigInteger(stdout, G);

    // testing add()
    printf("\n\nTesting add(): ");
    printf("\nA + C = ");
    add(G, A, C);
    printBigInteger(stdout, G);

    // testing sum()
    printf("\n\nTesting sum(): ");
    printf("\nD + F = ");
    G = sum(D, F);
    printBigInteger(stdout, G);

    // testing subtract()
    printf("\n\nTesting subtract(): ");
    printf("\nA - C = ");
    subtract(G, A, C);
    printBigInteger(stdout, G);

    // testing diff()
    printf("\n\nTesting diff(): ");
    printf("\nD - F = ");
    G = diff(D, F);
    printBigInteger(stdout, G);

    // testing multiply()
    printf("\n\nTesting multiply(): ");
    printf("\nA * C = ");
    multiply(G, D, F);
    printBigInteger(stdout, G);

    // testing prod()
    printf("\n\nTesting diff(): ");
    printf("\nD - F = ");
    G = prod(D, F);
    printBigInteger(stdout, G);
    printf("\n\n");
     
     
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
     
    printf("\nDone.\n");

    return 0;
    
     
}


