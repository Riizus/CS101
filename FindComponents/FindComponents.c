//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA4                                                                #
//   Findpath.c                                                                      #
//   Uses List.c ADT to read in a file of strings, sort the indexes and         #
//   print the strings in order to the designated file.                         #
//                                                                              #
//------------------------------------------------------------------------------#

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char *argv[]){
    
   if( argc <= 2 ){
      printf("FindPath: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   
   FILE* in;
   FILE* out;
   char* token;
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
   int EdgeC;
   Graph OG;
   
   if(fgets(line,MAX_LEN,in) == NULL){
      printf("Error: file input error");
      exit(1);
   }
   else{
      token = strtok(line," \n");
      EdgeC = atoi(token);
      OG = newGraph(EdgeC);
      token = strtok(NULL,"\n");	
   }
   
   while (fgets(line, MAX_LEN, in) != NULL){
      int A = 0;
      int B = 0;
      
      token = strtok(line," \n");
      A = atoi(token);
      token = strtok(NULL," \n");
      B = atoi(token);
      if (A == 0 && B == 0){
         break;
      }
      addArc(OG, A, B);
   }
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, OG);
   fprintf(out, "\n");
   
   SCC(OG);
  
   int Count = getCycles(OG);
   fprintf(out, "G contains ");
   if (Count == 0){
       fprintf(out, "no strongly connected components.\n");
   } else {
      int i, Vert;
      fprintf(out, "%d strongly connected components:\n", Count);
      for (i = 1; i <= Count; i++){
         fprintf(out, "Component %d : ", i);
         List Comp = getPones(OG, i);
         if ( length(Comp) > 0) {
            moveFront(Comp);
            while ( Index(Comp) >= 0){
               Vert = get(Comp);
               moveNext(Comp);
               fprintf(out, "%d ", Vert);
            }
         }
         freeList(&Comp);
         fprintf(out, "\n");
      }
   }
   
   freeGraph(&OG);
    
   /* close files */
   fclose(in);
   fclose(out);
   return(0);
}
