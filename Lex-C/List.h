// Bradley Bernard, bmbernar@ucsc.edu
// CS 101: PA2
// July 7, 2015
// $Id: List.h,v 1.3 2015-07-07 16:26:36-07 - - $

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

int index(List L);

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

void delete(List L);


void printList(FILE* out, List L);

List copyList(List L);

List concatList(List A, List B);


#endif