// Riise Kennard, riakenna@ucsc.edu
// CS 101: PA4
// Nov 9, 2016

//-----------------------------------------------------------------------------
// Graph.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"

#define NIL 0
#define INF -1

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);

int getSize(Graph G);

int getCycles(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

List getPones(Graph G, int u);

/*** Manipulation procedures ***/

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void SCC(Graph G);

void DFS(Graph G, List S);

int DFSRecur(Graph G, int V, int time, List S);

/*** Other operations ***/

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);


#endif