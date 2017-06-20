// Riise Kennard
// CMPS101: Graph.c
// Graph ADT for PA4. Represents vertices and edges of a graph
// as an array of Lists, also performs operations on
// these graphs.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"


typedef struct GraphObj{
   List *Nabrz;
   List *Pones;
   int *Culrz;
   int *Rentz;
   int *Disco;
   int *Fini;
   int Vertices;
   int Edges;
   int Cycles;
}GraphObj;


/*** Constructors-Destructors ***/

Graph newGraph(int n){

   Graph New = malloc(sizeof(struct GraphObj));
    
   New->Nabrz = calloc(n + 1, sizeof(List));
   New->Pones = calloc(n + 1, sizeof(List));
   New->Culrz = calloc(n + 1, sizeof(int));
   New->Disco = calloc(n + 1, sizeof(int));
   New->Fini = calloc(n + 1, sizeof(int));
   New->Rentz = calloc(n + 1, sizeof(int));
   New->Vertices = n;
   New->Edges = 0;
   New->Cycles = 0;
   
   for (int i = 0; i <= n; ++i){
      New->Nabrz[i] = newList();
      New->Pones[i] = newList();
      New->Culrz[i] = WHITE;
      New->Rentz[i] = NIL;
   }
   return New;
}

void freeGraph(Graph *pG){
      for (int i = 0; i <= (*pG)->Vertices; ++i){
         freeList(&((*pG)->Nabrz[i]));
         freeList(&((*pG)->Pones[i]));
      }
      free((*pG)->Nabrz);
      free((*pG)->Pones);
      free((*pG)->Culrz);
      free((*pG)->Rentz);
      free(*pG);
      *pG = NULL;
}


/*** Access functions ***/

int getOrder(Graph G){
   return G->Vertices;
}

int getSize(Graph G){
   return G->Edges;
}

int getCycles(Graph G){
   return G->Cycles;
}

int getParent(Graph G, int u){
   if (u < 1 || u > G->Vertices){
      printf("Graph Error: getParent() called on index out of range\n");
      exit(1);
   }
   return G->Rentz[u];
}

int getDiscover(Graph G, int u){
   if (u < 1 || u > G->Vertices){
      printf("Graph Error: getDiscover() called on index out of range\n");
      exit(1);
   }
   return G->Disco[u];
}

int getFinish(Graph G, int u){
   if (u < 1 || u > G->Vertices){
      printf("Graph Error: getFinish() called on index out of range\n");
      exit(1);
   }
   return G->Fini[u];
}

List getPones(Graph G, int u){
   if (G->Culrz[1] == WHITE){
       printf("SSC Not Called yet");
       return NULL;
   }else if (u < 1 || u > G->Cycles){
      printf("Graph Error: getPones() called on index out of range\n");
      exit(1);
   }
   return copyList(G->Pones[u]);
}


/*** Manipulation procedures ***/

void makeNull(Graph G){
   for(int i = 1; i <= G->Vertices; i++) {
     clear(G->Nabrz[i]);
   }
}

void addEdge(Graph G, int u, int v){
   if (u < 1 || u > G->Vertices || v < 1 || v > G->Vertices){
      printf("Graph Error: addEdge() called on index out of range\n");
      exit(1);
   }
   addArc(G, u, v);
   addArc(G, v, u);
   G->Edges--;
}

void addArc(Graph G, int u, int v){
   if (u < 1 || u > G->Vertices || v < 1 || v > G->Vertices){
      printf("Graph Error: addArc() called on index out of range\n");
      exit(1);
   }

   List L = G->Nabrz[u];
   if (length(L) > 0){
      moveFront(L);
   }
   while (Index(L) > -1 && v > get(L)){
      moveNext(L);
   }
   if (Index(L) >= 0){
      insertBefore(L, v);
   } else {
      append(L, v);
   }
   G->Edges++;
}

void SCC(Graph G){
   List input = newList();
   for (int i = 1; i <= G->Vertices; i++){
       append(input, i);
   }
   DFS(G, input);
   Graph OG = transpose(G);
   List Rev = reverseList(input);
   DFS(OG, Rev);
   int Count = 0;
   for (moveFront(Rev); Index(Rev) >= 0;){
       int Vert = get(Rev);
       if (OG->Rentz[Vert] == NIL){
           List OL = G->Pones[++Count];
           while (Index(Rev) != 0){
               Vert = get(Rev);
               append(OL, Vert);
               movePrev(Rev);
               deleteNext(Rev);
           }
           append(OL, front(Rev));
           moveNext(Rev);
           deleteFront(Rev);
       } else {
           moveNext(Rev);
       }
   }
   G->Cycles = Count;
   freeGraph(&OG);
   freeList(&Rev);
}



void DFS(Graph G, List S){
   int Length = length(S);
   int i, time = 1;
   if (Length == 0){
      printf("Graph Error: DFS called on empty List\n");
      exit(1);
   }
   for (; i <= G->Vertices; i++){
      G->Rentz[i] = NIL;
      G->Culrz[i] = WHITE;
   }
   moveFront(S);
   for (i = 1; i <= Length; i++){
      int Vert = get(S);
      if (G->Culrz[Vert] == WHITE){
         G->Culrz[Vert] = GRAY;
         G->Disco[Vert] = time++;
         time = DFSRecur(G, Vert, time, S);
      }
      moveNext(S);
      deleteFront(S);
   }
}

int DFSRecur(Graph G, int V, int time, List S){
   List OG = G->Nabrz[V];
   if (length(OG) != 0){
      for (moveFront(OG); Index(OG) >= 0; moveNext(OG)){
         int Vert = get(OG);
         if (G->Culrz[Vert] == WHITE){
            G->Rentz[Vert] = V;
            G->Culrz[Vert] = GRAY;
            G->Disco[Vert] = time++;
            time = DFSRecur(G, Vert, time, S);
         }
      }
   }
   G->Fini[V] = time++;
   G->Culrz[V] = BLACK;
   append(S, V);
   return time;
}

/*** Other operations ***/

Graph transpose(Graph G){
   Graph New = newGraph(G->Vertices);
   New->Edges = G->Edges;
   for (int i = 1; i <= G->Vertices; i++){
       List OG = G->Nabrz[i];
       if (length(OG) != 0){
           for (moveFront(OG); Index(OG) >= 0; moveNext(OG)){
               int Vert = get(OG);
               append(New->Nabrz[Vert], i);
           }
       }
   }
   return New;
}

Graph copyGraph(Graph G){
   Graph New = newGraph(G->Vertices);
   New->Edges = G->Edges;
   New->Cycles = G->Cycles;
   int i = 1;
   for (; i <= New->Cycles; i++){
       New->Pones[i] = copyList(G->Pones[i]);
   }
   for (int i = 1; i <= G->Vertices; i++){
      List OG = G->Nabrz[i];
      if (length(OG) != 0){
         for (moveFront(OG); Index(OG) >= 0; moveNext(OG)){
            int Vert = get(OG);
            append(New->Nabrz[i], Vert);
         }
      }
      New->Culrz[i] = G->Culrz[i];
      New->Disco[i] = G->Disco[i];
      New->Fini[i] = G->Fini[i];
      New->Rentz[i] = G->Rentz[i];
	}
	return (New);
}

void printGraph(FILE* out, Graph G){
    if(G == NULL) {
      printf("Graph Error: printGraph() called on NULL Graph reference\n");
      exit(1);
   }
   int i, temp;
   for (i = 1; i <= G->Vertices; i++){
      fprintf(out, "%d : ", i);
      List OG = G->Nabrz[i];
      if ( length(OG) > 0) {
         moveFront(OG);
         while ( Index(OG) >= 0){
            temp = get(OG);
            moveNext(OG);
            fprintf(out, " %d", temp);
         }
      }
      fprintf(out, "\n");
   }
}