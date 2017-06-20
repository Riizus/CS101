// Riise Kennard, riakenna@ucsc.edu
// CS 101: PA4
// Nov 9, 2016

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


typedef struct listObj* List;

List newList(void);

void freeList(List* pL);


int length(List L);

int Index(List L);

int front(List L);

int back(List L);

int get(List L);

int equals(List A, List B);


void clear(List L);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int data);

void append(List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);

void deleteBack(List L);

void deleteNext(List L);

void deletePrev(List L);

void delete(List L);


void printList(FILE* out, List L);

List copyList(List L);

List reverseList(List L);

List concatList(List A, List B);


#endif