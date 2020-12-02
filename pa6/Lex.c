/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Lex.c
* Client module for the Dictionary ADT
*/
/*
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#define MAX_LEN 300


int main(int argc, const char * argv[]) {

    FILE *in, *out;

    // check command line for correct number of arguments
    // argv[0] = Lex, argv[1] = in file, argv[2] = out file
    
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
    
    
    // hardcoding the filename (testing):
    in = fopen("in1.txt", "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", "input.txt"); // print error message to stderr
        exit(1);
    }
    out = fopen("out1.txt", "w");
    if(out==NULL) {
        printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
        exit(1);
    }
    // end (testing)
    
    
    // grab each line from file and insert key, val into dict
    // line = key
    // line number = val
    
    Dictionary D = newDictionary(0); // create a non-unique dictionary
    int line_count = 1; // start at 1 so first line is line 1
    char *line = NULL;
    line = (char *)malloc(MAX_LEN);
    
    while(fgets(line, MAX_LEN, in) != NULL) {
        int line_length = (int)strlen(line);
        
        if (line[line_length-1] == '\n') {  // if last char of line is '\n'
            line[line_length-1] = '\0'; // replace '\n' with null terminator
        } else {  // if no '\n' add a null terminator at end of line
            line[line_length] = '\0';
        }
        
        insert(D, line, line_count); // insert key = line, val = line_count into D
        line_count++;
    }
    // when getline is finished, it returns 0 (false) and while exits
    
    fclose(in);
    free(line);
    
    // print out the keys in order
    int numKeys = size(D);
    beginForward(D);
    
    for(int i=0; i < numKeys; i++) {
        fprintf(out, "%s", (char*)currentKey(D));
        if (i != numKeys-1) {   // if not at last print
            fprintf(out, "\n");
        }
        next(D);
    }
    
    freeDictionary(&D);
    fclose(out);
    
    return 0;
}

*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>

#include "Dictionary.h"

#define FIRST_TEST Empty_size
#define MAXSCORE 54

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e {
  Empty_size = 0,
  Insert_size,
  Delete_size,

  Empty_traverse,
  Empty_makeEmpty,
  NonEmpty_makeEmpty,

  BeginForward_value,
  BeginReverse_value,
  Next_value,
  Prev_value,
  Insert_value,
  Delete_value,
  Loopup_value,

  NonUnique_size,
  NonUnique_insert,
  NonUnique_delete,
  NonUnique_beginForward,
  NonUnique_beginReverse,

  NUM_TESTS,
};

char *testName(int test) {
  if (test == Empty_size) return "Empty_size";
  if (test == Insert_size) return "Insert_size";
  if (test == Delete_size) return "Delete_size";

  if (test == Empty_traverse) return "Empty_traverse";
  if (test == Empty_makeEmpty) return "Empty_makeEmpty";
  if (test == NonEmpty_makeEmpty) return "NonEmpty_makeEmpty";

  if (test == BeginForward_value) return "BeginForward_value";
  if (test == BeginReverse_value) return "BeginReverse_value";
  if (test == Next_value) return "Next_value";
  if (test == Prev_value) return "Prev_value";
  if (test == Insert_value) return "Insert_value";
  if (test == Delete_value) return "Delete_value";
  if (test == Loopup_value) return "Loopup_value";

  if (test == NonUnique_size) return "NonUnique_size";
  if (test == NonUnique_insert) return "NonUnique_insert";
  if (test == NonUnique_delete) return "NonUnique_delete";
  if (test == NonUnique_beginForward) return "NonUnique_beginForward";
  if (test == NonUnique_beginReverse) return "NonUnique_beginReverse";

  return "";
}

uint8_t runTest(Dictionary *pA, Dictionary *pB, int test) {
  Dictionary A = *pA;
  Dictionary B = *pB;
  switch(test) {
    case Empty_size:
      {
        if (size(A) != 0) return 1;
        return 0;
      }
    case Insert_size:
      {
        insert(A, "a", 1);
        insert(A, "b", 2);
        insert(A, "c", 3);
        insert(A, "e", 5);
        if (size(A) != 4) return 1;
        return 0;
      }
    case Delete_size:
      {
        insert(A, "c", 3);
        insert(A, "a", 1);
        insert(A, "b", 2);
        delete(A, "a");
        if (size(A) != 2) return 1;
        insert(A, "e", 5);
        delete(A, "c");
        if (size(A) != 2) return 2;
        return 0;
      }
    case Empty_traverse:
      {
        if (beginForward(A) != VAL_UNDEF) return 1;
        if (beginReverse(A) != VAL_UNDEF) return 2;
        if (currentVal(A) != VAL_UNDEF) return 3;
        if (currentKey(A) != KEY_UNDEF) return 4;
        return 0;
      }
    case Empty_makeEmpty:
      {
        makeEmpty(A);
        if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF || size(A) != 0) return 1;
        return 0;
      }
    case NonEmpty_makeEmpty:
      {
        insert(A, "c", 3);
        insert(A, "b", 2);
        insert(A, "a", 1);
        beginForward(A);
        makeEmpty(A);
        fprintf(stdout, "%s\n", currentKey(A));
        fprintf(stdout, "%d\n", currentVal(A));
          
        if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF || size(A) != 0) return 1;
        return 0;
      }
    case BeginForward_value:
      {
        insert(A, "d", 1);
        insert(A, "b", 5);
        insert(A, "c", 16);
        insert(A, "f", 176);
        insert(A, "e", 3214);
        if (beginForward(A) != 5 || currentVal(A) != 5) return 1;
        delete(A, "b");
        if (beginForward(A) != 16 || currentVal(A) != 16) return 2;
        return 0;
      }
    case BeginReverse_value:
      {
        insert(A, "d", 1);
        insert(A, "b", 5);
        insert(A, "c", 16);
        insert(A, "f", 176);
        insert(A, "e", 3214);
        if (beginReverse(A) != 176 || currentVal(A) != 176) return 1;
        delete(A, "f");
        if (beginReverse(A) != 3214 || currentVal(A) != 3214) return 1;
        return 0;
      }
    case Next_value:
      {
        insert(A, "a", 1);
        insert(A, "b", 5);
        insert(A, "c", 16);
        insert(A, "d", 176);
        insert(A, "e", 3214);
        beginForward(A);
        next(A);
        next(A);
        if (strcmp(currentKey(A), "c") != 0 || currentVal(A) != 16) return 1;
        next(A);
        next(A);
        next(A);
        if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF) return 2;
        return 0;
      }
    case Prev_value:
      {
        insert(A, "a", 1);
        insert(A, "b", 5);
        insert(A, "e", 3214);
        beginReverse(A);
        prev(A);
        if (strcmp(currentKey(A), "b") != 0 || currentVal(A) != 5) return 1;
        prev(A);
        prev(A);
        if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF) return 2;
        return 0;
      }
    case Insert_value:
      {
        insert(A, "a", 1);
        insert(A, "b", 5);
        insert(A, "e", 10);
        beginReverse(A);
        insert(A, "h", 15);
        insert(A, "f", 20);
        insert(A, "i", 100);
        if (strcmp(currentKey(A), "e") != 0 || currentVal(A) != 10) return 1;
        beginReverse(A);
        prev(A);
        prev(A);
        if (strcmp(currentKey(A), "f") != 0 || currentVal(A) != 20) return 2;
        return 0;
      }
    case Delete_value:
      {
        insert(A, "d", 1);
        insert(A, "b", 5);
        insert(A, "a", 10);
        insert(A, "c", 15);
        insert(A, "f", 20);
        insert(A, "e", 25);
        insert(A, "g", 30);
        beginForward(A);
        delete(A, "a");
        if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF) return 1;
        beginReverse(A);
        delete(A, "d");
        if (strcmp(currentKey(A), "g") != 0 || currentVal(A) != 30) return 2;
        return 0;
      }
    case Loopup_value:
      {
        if (lookup(A, "f") != VAL_UNDEF) return 1;
        insert(A, "a", 1);
        insert(A, "b", 5);
        insert(A, "e", 10);
        insert(A, "h", 15);
        insert(A, "f", 20);
        insert(A, "i", 100);
        if (lookup(A, "f") != 20) return 2;
        delete(A, "f");
        if (lookup(A, "f") != VAL_UNDEF) return 3;
        return 0;
      }
    case NonUnique_size:
      {
        insert(B, "d", 2);
        insert(B, "d", 5);
        insert(B, "d", 1);
        if (size(B) != 3) return 1;
        delete(B, "d");
        if (size(B) != 2) return 2;
        return 0;
      }
    case NonUnique_insert:
      {
        insert(B, "d", 2);
        insert(B, "d", 5);
        if (lookup(B, "d") != 2) return 1;
        insert(B, "d", 1);
        if (lookup(B, "d") != 2) return 2;
        return 0;
      }
    case NonUnique_delete:
      {
        insert(B, "d", 2);
        insert(B, "d", 5);
        delete(B, "d");
        if (lookup(B, "d") != 5) return 1;
        return 0;
      }
    case NonUnique_beginForward:
      {
        insert(B, "d", 2);
        insert(B, "d", 5);
        insert(B, "d", 1);
        if (beginForward(B) != 2) return 1;
        next(B);
        if (currentVal(B) != 5) return 2;
        return 0;
      }
    case NonUnique_beginReverse:
      {
        insert(B, "d", 2);
        insert(B, "d", 5);
        insert(B, "d", 1);
        if (beginReverse(B) != 1) return 1;
        prev(B);
        if (currentVal(B) != 5) return 2;
        return 0;
      }
  }
  return 255;
}

void segfault_handler(int signal) { // everyone knows what this is
  testStatus = 255;
  longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
  if (disable_exit_handler) return; // allow this to be disabled
  testStatus = 255;
  longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
  testStatus = 255;
  longjmp(test_crash, 3);
}

int main (int argc, char **argv) {
  if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./ModelDictionaryTest"));
    exit(1);
  }

  printf("\n"); // more spacing
  if (argc == 2) printf("\n"); // consistency in verbose mode

  testsPassed = 0;
  disable_exit_handler = 0;
  atexit(exit_attempt_handler);
  signal(SIGSEGV, segfault_handler);
  //signal(SIGTERM, abrupt_termination_handler); // dangerous
  //signal(SIGINT, abrupt_termination_handler);
  //signal(SIGFPE, abrupt_termination_handler);
  //signal(SIGABRT, abrupt_termination_handler);
  for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
    Dictionary A = newDictionary(1);
    Dictionary B = newDictionary(0);
    testStatus = runTest(&A, &B, i);
    freeDictionary(&A);
    freeDictionary(&B);
    uint8_t fail_type = setjmp(test_crash);
    if (argc == 2) { // it's verbose mode
      printf("Test %s: %s", testName(i), testStatus == 0 ? "PASSED" :
          "FAILED");
      if (testStatus == 255) {
        printf(": due to a %s\n", fail_type == 1 ? "segfault" : fail_type == 2 ?
            "program exit" : "program interruption");
        printf("\nWARNING: Program will now stop running tests\n\n");
        break;
      } else if (testStatus != 0) {
        printf(": test %d\n", testStatus);
      } else {
        printf("\n");
      }
    }
    if (testStatus == 0) {
      testsPassed++;
    }
  }

  disable_exit_handler = 1;

  uint8_t totalScore = testsPassed*3;

  if (argc == 2 && testStatus != 255) printf("\nYou passed %d out of %d tests\n", testsPassed,
      NUM_TESTS);
  else if (testStatus == 255) {
    totalScore = 10; // charity points
    if (argc == 2) printf("Receiving charity points because your program crashes\n");
  }
  printf("\nYou will receive %d out of %d possible points on the ListTests\n\n",
      totalScore, MAXSCORE);
  exit(0);
  return 0;
}
