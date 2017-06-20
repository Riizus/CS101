//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA2                                                                #
//   Lex.c                                                                      #
//   Uses List.c ADT to read in a file of strings, sort the indexes and         #
//   print the strings in order to the designated file.                         #
//                                                                              #
//------------------------------------------------------------------------------#

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"

#define MAX_LEN 255

int main(int argc, char* argv[]){
    
   if (argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
    
   FILE *in, *out;
   int lineCount = 0;
   char line[MAX_LEN];
    
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
    
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   while( fgets(line, MAX_LEN, in) != NULL)  {
      lineCount++;
   }
   
   fclose(in);
   in = fopen(argv[1], "r");
   int curs = 0;
    
   char words[lineCount][MAX_LEN];
    
   while (fgets(line, MAX_LEN, in) != NULL ){
      strcpy(words[curs++], line);
   }
   
   List list = newList();
   append(list, 0);

   //sorts each word in the list individually
   for (int i = 1; i < lineCount; i++){
      char *temp = words[i];
      
      //sets cursor at front of list
      moveFront(list);
      
      while (index(list) != -1 && strcmp(temp, words[get(list)]) >= 0){
         moveNext(list);

      }
      if (index(list) >= 0){
         insertBefore(list, i);
      } else {
         append(list, i);
      }
   }  
      
   //Move cursor to front
   moveFront(list);
    
   // Loop through List to print out lines in the correct order
   while(index(list) >= 0) {
      fprintf(out, "%s", words[get(list)]);
      moveNext(list);
   }
   freeList(&list);
}
