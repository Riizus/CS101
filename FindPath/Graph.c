// Riise Kennard
// CMPS101: Graph.c
// Graph ADT for PA4. Represents vertices and edges of a graph
// as an array of Lists, also performs operations on
// these graphs.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define NIL 0
#define INF -1

typedef struct GraphObj{
   int Source;
   int Vertices;
   int Edges;
   List *Nabrz;
   int *Culrz;
   int *Rentz;
   int *Distnz;
}GraphObj;


/*** Constructors-Destructors ***/

Graph newGraph(int n){

   Graph New = malloc(sizeof(struct GraphObj));
    
   New->Nabrz = calloc(n + 1, sizeof(List));
   New->Culrz = calloc(n + 1, sizeof(int));
   New->Rentz = calloc(n + 1, sizeof(int));
   New->Distnz = calloc(n + 1, sizeof(int));
   New->Vertices = n;
   New->Source = NIL;
   New->Edges = 0;
   
   for (int i = 0; i <= n; ++i){
      New->Rentz[i] = NIL;
      New->Distnz[i] = INF;
      New->Nabrz[i] = newList();
      New->Culrz[i] = WHITE;
   }
   return New;
}

void freeGraph(Graph *pG){
      for (int i = 0; i <= (*pG)->Vertices; ++i){
         freeList(&((*pG)->Nabrz[i]));
      }
      free((*pG)->Nabrz);
      free((*pG)->Culrz);
      free((*pG)->Rentz);
      free((*pG)->Distnz);
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

int getSource(Graph G){
   
   return G->Source;
}

int getParent(Graph G, int u){
   if (u < 1 || u > G->Vertices){
      printf("Graph Error: getParent() called on index out of range\n");
      exit(1);
   }
   return G->Rentz[u];
}
int getDist(Graph G, int u){
   if(getSource(G) == NIL) {
      return INF;
   } else if (u < 1 || u > G->Vertices){
      printf("Graph Error: getDist() called on index out of range\n");
      exit(1);
   }
   return G->Distnz[u];
}

void getPath(List L, Graph G, int u){
   if (u < 1 || u > G->Vertices){
      printf("Graph Error: getPath() called on index out of range\n");
      exit(1);
   } else if (getSource(G) == NIL){
      printf("Graph Error: getPath() called without source\n");
      exit(1);
   } else if (G->Source == u){
      append(L, u);
   } else if (G->Rentz[u] == NIL){
      append(L, NIL);
   } else {
      getPath( L, G, G->Rentz[u]);
      if (back(L) != NIL){
         append(L, u);
      }
   }
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

void BFS(Graph G, int s){
    G->Source = s;
    for (int i = 1; i <= G->Vertices; i++){
        G->Rentz[i] = NIL;
        if (i == s){
            G->Culrz[i] = GRAY;
            G->Distnz[i] = 0;
        } else {
            G->Culrz[i] = WHITE;
            G->Distnz[i] = INF;
        }
    }
    List Queue = newList();
    append(Queue, s);
    while (length(Queue) >= 1){
        int x = front(Queue);
        deleteFront(Queue);
        List temp = G->Nabrz[x];
        if (length(temp) == 0){
            G->Culrz[x] = BLACK;
            continue;
        }
        int y;
        for (moveFront(temp); Index(temp) >= 0; moveNext(temp)){
            y = get(temp);
            if (G->Culrz[y] == WHITE){
                G->Culrz[y] = GRAY;
                G->Distnz[y] = G->Distnz[x] + 1;
                G->Rentz[y] = x;
                append(Queue, y);
            }
        }
        G->Culrz[x] = BLACK;
    }
    freeList(&Queue);
}

/*** Other operations ***/

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