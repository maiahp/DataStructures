/*
* Maiah Pardo, mapardo
* 2020 Fall CSE 101 PA6
* Order.c
* Client Module for Dictionary ADT
*/


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
    //in = fopen("in3.txt", "r");
    //if(in==NULL) {
    //    printf("Unable to open file %s for reading\n", "input.txt"); // print error message to stderr
    //    exit(1);
    //}
    //out = fopen("out3.txt", "w");
    //if(out==NULL) {
    //    printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
    //    exit(1);
    //}
    // end (testing)
    
    
    // grab each line from file and insert key, val into dict
    // line = key
    // line number = val
    
    Dictionary D = newDictionary(0); // create a non-unique dictionary
    char *line = NULL;
    line = (char *)malloc(MAX_LEN);
    int num = 1;
    int *num_ptr = &num;
    
    while(fgets(line, MAX_LEN, in) != NULL) {
        int line_length = (int)strlen(line);
        
        if (line[line_length-1] == '\n') {  // if last char of line is '\n'
            line[line_length-1] = '\0'; // replace '\n' with null terminator
        } else {  // if no '\n' add a null terminator at end of line
            line[line_length] = '\0';
        }
        
        insert(D, line, num_ptr); // insert key = line
                                  // normally we could give int* val = NULL since val doesn't matter and a pointer can be set to NULL
                                  // but dictionary VAL_UNDEF = NULL, so lookup() != val_undef condition in delete always fails
                                    
    }
    // when getline is finished, it returns 0 (false) and while exits
    
    fclose(in);
    free(line);
    
    fprintf(out, "******************************************************\nPRE-ORDER:\n******************************************************\n");
    printDictionary(out, D, "pre");
    
    fprintf(out, "\n\n\n******************************************************\nIN-ORDER:\n******************************************************\n");
    printDictionary(out, D, "in");
    
    fprintf(out, "\n\n\n******************************************************\nPOST-ORDER:\n******************************************************\n");
    printDictionary(out, D, "post");
    
    freeDictionary(&D); // note: freeList calls clearList()
    fclose(out);

    return 0;
}

// note: there is a shakespeare file and big.txt that contains blanks
// im not sure if the blanks should be counted in the outfile


/*
//-----------------------------------------------------------------------------
// WordFrequency.c
// Determines frequency of each word in a file.
//
// Usage:  WordFrequency <input file> <output file>
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Dictionary.h"

#define MAX_LINE_LEN 300


int main(int argc, char* argv[]){

   Dictionary D = newDictionary(1); // unique keys
   FILE* in = NULL;
   FILE* out = NULL;
   char delim[] = "\x20\n\t\r\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789"\
                  "\xE2\x80\x98\x94\x99\x9C\x9D\x25";
   char line[MAX_LINE_LEN];
   char** keyBuffer = NULL;
   int**  valBuffer = NULL;
   char* word;
   char* ch;
   int* p;
   int i, n=0;

    
   // check command line arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // open input file
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   // open output file
   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
    
    // hardcoding the filename (testing):
    in = fopen("infile1.txt", "r");
    if(in==NULL) {
        printf("Unable to open file %s for reading\n", "input.txt"); // print error message to stderr
        exit(1);
    }
    out = fopen("outfile1.txt", "w");
    if(out==NULL) {
        printf("Unable to open file %s for writing\n", "output.txt"); // print error message to stderr
        exit(1);
    }
    // end (testing)

   // read each line of input
   while( fgets(line, MAX_LINE_LEN, in) != NULL)  {
      
      // get each word on this line
      word = strtok(line, delim);
      while( word!=NULL ){ // there is another word
         
         // convert word to lower case
         for(ch=word; *ch!='\0'; ch++){
            *ch = tolower(*ch);
         }

         p = lookup(D, word);
         if( p==VAL_UNDEF ){ // this word is new
            n++;

            keyBuffer = realloc(keyBuffer, n*sizeof(KEY_TYPE));
            keyBuffer[n-1] = calloc(strlen(word)+1, sizeof(char));
            strcpy(keyBuffer[n-1], word);

            valBuffer = realloc(valBuffer, n*sizeof(VAL_TYPE));
            valBuffer[n-1] = malloc(sizeof(int));
            *valBuffer[n-1] = 1;

            insert( D, keyBuffer[n-1], valBuffer[n-1] );

         }else{ // this word has been seen already
            (*p)++;
         }

         // get next token
         word = strtok(NULL, delim);
      }
   }

   // print words and their frequencies
   fprintf(out, " word                frequency\n");
   fprintf(out, "-----------------------------------\n");
   for(p=beginForward(D); p!=VAL_UNDEF; p=next(D)) {
      fprintf(stdout, " %-20s%d\n", currentKey(D), *currentVal(D));
   }
   fprintf(stdout,"\n");

   // free resources
   freeDictionary(&D);
   for(i=0; i<n; i++){
      free(keyBuffer[i]);
      free(valBuffer[i]);
   }
   free(keyBuffer);
   free(valBuffer);
   fclose(in);
   fclose(out);

   return(0);
}
*/
