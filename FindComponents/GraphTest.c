//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA4                                                                #
//   GraphTest.c                                                                #
//   Client Tests the Graph ADT                                                 #
//                                                                              #
//------------------------------------------------------------------------------#

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i = 8;
   List L = newList();
   Graph G = newGraph(i);

   /* Add directed edges to graph and print */
   addArc(G, 1, 2);
   addArc(G, 2, 3);
   addArc(G, 2, 5);
   addArc(G, 2, 6);
   addArc(G, 3, 4);
   addArc(G, 3, 7);
   addArc(G, 4, 3);
   addArc(G, 4, 8);
   addArc(G, 5, 1);
   addArc(G, 5, 6);
   addArc(G, 6, 7);
   addArc(G, 7, 6);
   addArc(G, 7, 8);
   addArc(G, 8, 8);
   printf("Original: \n");
   printGraph(stdout, G);
   printf("\n");

   
   // Make Trivial List
   for ( i = 1; i <= getOrder(G); ++i ) {
      append(L, i);
   }

   // Make Transpose and Print
   Graph OG = transpose(G);
   printf("Transpose: \n");
   printGraph(stdout, OG);
   printf("\n");
    
   // Run DFS and Show Vertex Fields
   printf("DFS with List: ");
   printList(stdout, L);
   printf("\n");
   DFS(G, L);
   for ( i = 1; i <= getOrder(G); ++i ) { 
      printf("Vert: %d, Rent: %d, Discover: %d, Finish: %d\n", i, getParent(G, i), getDiscover(G,i), getFinish(G,i));
   }
   printf("Output List: ");
   printList(stdout, L);
   printf("\n");
   printf("\n");
   
   
   // Run SCC and print components
   SCC(G);
  
   int Count = getCycles(G);
   printf("G contains ");
   if (Count == 0){
       printf("no strongly connected components.\n");
   } else {
      int i, Vert;
      printf("%d strongly connected components:\n", Count);
      for (i = 1; i <= Count; i++){
         printf("Component %d : ", i);
         List Comp = getPones(G, i);
         if ( length(Comp) > 0) {
            moveFront(Comp);
            while ( Index(Comp) >= 0){
               Vert = get(Comp);
               moveNext(Comp);
               printf("%d ", Vert);
            }
         }
         freeList(&Comp);
         printf("\n");
      }
   }

   // Free objects 
   freeGraph(&G);
   freeGraph(&OG);
   freeList(&L);

   return(0);
}

