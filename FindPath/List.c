//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA2                                                                #
//   List.c                                                                     #
//   ADT for Lex.c. Doubley-linked list with cursor to traverse it.             #
//                                                                              #
//------------------------------------------------------------------------------#

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "List.h"

typedef struct NodeRef{
	int data;
	struct NodeRef* next;
	struct NodeRef* prev;
} NodeRef;

typedef NodeRef* Node;

typedef struct listObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} listObj;

// Constructors-Destructors ---------------------------------------------------

// newNode() 
// Creates Node and sets data
Node newNode(int data){
   Node New = malloc(sizeof(NodeRef));
   New->data = data;
   New->prev = New->next = NULL;
   return New;
}

void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

List newList(void){
   List New = malloc(sizeof(listObj));
   New->front = New->back = New->cursor = NULL;
   New->length = 0;
   New->index = -1;
   return New;
}

void freeList(List* pL) {
   if(pL != NULL && *pL != NULL) { 
      Node check = (*pL)->front; 
      while(check != NULL) {
         Node tmp = check;
         check = check->next;
         free(tmp);
      }
      free(*pL);
      *pL = NULL;
   }
}
// Access functions -----------------------------------------------------------
// length()
// returns length of list
int length(List L){
   if(L == NULL) {
      printf("List Error: length() called on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

// Index()
// Returns index of current cursor element, if none returns -1
int Index(List L){
   if(L == NULL) {
      printf("List Error: index() called on NULL List reference\n");
      exit(1);
   }
   return L->index;
}

// front()
// Returns front element.
int front(List L){
   if(L == NULL) {
      printf("List Error: front() called on NULL List reference\n");
      exit(1);
   }
   if(L->front == NULL) {
      printf("List Error: front() called on empty List\n");
      exit(1);
   }
   return L->front->data;
}

// back()
// Returns back element.
int back(List L){
   if(L == NULL) {
      printf("List Error: back() called on NULL List reference\n");
      exit(1);
   }
   if(L->back == NULL) {
      printf("List Error: back() called on empty List\n");
      exit(1);
   }
   return L->back->data;
}

// get()
// Returns element at cursor if defined.
int get(List L){
   if(L == NULL) {
      printf("List Error: get() called on NULL List\n");
      exit(1);
   }else if(L->back == NULL) {
      printf("List Error: get() called on empty List\n");
      exit(1);
   }else if(L->cursor == NULL) {
      printf("List Error: get() called on NULL cursor\n");
      exit(1);
   }
   return L->cursor->data;
}

// equals()
// Returns 1 if A is a List storing
// the same integer sequence as B, and 0 otherwise.
int equals(List A, List B){
   if(A == NULL || B == NULL) {
      printf("List Error: equals() called on NULL List\n");
      exit(1);
   }
   if (A->length != B->length){
      return 0;
   }
   Node ACheck = A->front;
   Node BCheck = B->front;
   
   while (ACheck != NULL){
      if (ACheck->data != BCheck->data){
         return 0;
      }
      ACheck = ACheck->next;
      BCheck = BCheck->next;
   }
   return 1;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets List to its original empty state.
void clear(List L){
   if(L == NULL) {
      printf("List Error: clear() called on NULL List\n");
      exit(1);
   }
   freeList(&L);
   L = newList();
}

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
   if(L == NULL) {
      printf("List Error: moveFront() called on NULL List\n");
      exit(1);
   }else if(L->front == NULL) {
      printf("List Error: moveFront() called on empty List\n");
      exit(1);
   }
   L->cursor = L->front;
   L->index = 0;
}

// moveFBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
   if(L == NULL) {
      printf("List Error: moveBack() called on NULL List\n");
      exit(1);
   }else if(L->back == NULL) {
      printf("List Error: moveBack() called on empty List\n");
      exit(1);
   }
   L->cursor = L->back;
   L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L){
   if(L == NULL) {
      printf("List Error: movePrev() called on NULL List\n");
      exit(1);
   }else if(L->front == NULL) {
      printf("List Error: movePrev() called on empty List\n");
      exit(1);
   } else if (L->cursor == NULL){
      return;
   } else if (L->cursor == L->front){
      L->cursor = NULL;
   } else {
      L->cursor = L->cursor->prev;
   } L->index--;
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if(L == NULL) {
      printf("List Error: moveNext() called on NULL List\n");
      exit(1);
   }else if(L->back == NULL) {
      printf("List Error: moveNext() called on empty List\n");
      exit(1);
   } else if (L->cursor == NULL){
      return;
   } else if (L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   } else {
      L->cursor = L->cursor->next;
      L->index++;
   }
}

// prepend()
// Inserts data to front of this List.
void prepend(List L, int data){
   if(L == NULL) {
      printf("List Error: prepend() called on NULL List\n");
      exit(1);
   } 
   Node New = newNode(data);
   if (L->front == NULL){
      L->front = L->back = New;
   } else {
      New->next = L->front;
      L->front->prev = New;
      L->front = New;
   }
   if (L->cursor != NULL){
      L->index++;
   }
   L->length++;
}


// append()
// Inserts data to back of this List.
void append(List L, int data){
   if(L == NULL) {
      printf("List Error: append() called on NULL List\n");
      exit(1);
   } 
   Node New = newNode(data);
   if (L->back == NULL){
      L->front = New;
      L->back = New;
   } else {
      L->back->next = New;
      New->prev = L->back;
      L->back = New;
   }
   L->length++;
}

// insertBefore()
// Insert new element before cursor.
void insertBefore(List L, int data){
   if(L == NULL) {
      printf("List Error: insertBefore() called on NULL List\n");
      exit(1);
   }else if(L->front == NULL) {
      printf("List Error: insertBefore() called on empty List\n");
      exit(1);
   }else if(L->cursor == NULL) {
      printf("List Error: insertBefore() called on NULL cursor\n");
      exit(1);
   }else if (L->cursor == L->front){
      prepend(L, data);
   }else {
      Node New = newNode(data);
      L->cursor->prev->next = New;
      New->prev = L->cursor->prev;
      New->next = L->cursor;
      L->cursor->prev = New;
      L->index++;
      L->length++;
   }
}

// insertAfter()
// Insert new element before cursor.
void insertAfter(List L, int data){
   if(L == NULL) {
      printf("List Error: insertAfter() called on NULL List\n");
      exit(1);
   }else if(L->back == NULL) {
      printf("List Error: insertAfter() called on empty List\n");
      exit(1);
   }else if(L->cursor == NULL) {
      printf("List Error: insertAfter() called on NULL cursor\n");
      exit(1);
   }else if (L->cursor == L->back){
      prepend(L, data);
   }else {
      Node New = newNode(data);
      New->prev = L->cursor;
      New->next = L->cursor->next;
      L->cursor->next->prev = New;
      L->cursor->next = New;
      L->length++;
   }
}

// deleteFront()
// Deletes front element from this List.
void deleteFront(List L){
   if(L == NULL) {
      printf("List Error: deleteFront() called on NULL List\n");
      exit(1);
   }else if(L->front == NULL) {
      printf("List Error: deleteFront() called on empty List\n");
      exit(1);
   }
   L->length--;
   if (L->cursor != NULL){
      L->index--;
   }
   if (L->cursor == L->front){
      L->cursor = NULL;
   }
   if (L->front == L->back){
       clear(L);
   } else {
      Node temp = L->front;
      L->front = L->front->next;
      L->front->prev = NULL;
      freeNode(&temp);
   }   
}

// deleteBack()
// Deletes back element from this List.
void deleteBack(List L){
   if(L == NULL) {
      printf("List Error: deleteBack() called on NULL List\n");
      exit(1);
   }else if(L->front == NULL) {
      printf("List Error: deleteBack() called on empty List\n");
      exit(1);
   }
   L->length--;
   if (L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   if (L->front == L->back){
       clear(L);
   } else {  
      Node temp = L->back;
      L->back = L->back->prev;
      L->back->next = NULL;
      freeNode(&temp);
   }
}

// delete()
// Deletes cursor element from this List if it exists.
void delete(List L){
   if(L == NULL) {
      printf("List Error: delete() called on NULL List\n");
      exit(1);
   }else if(L->back == NULL) {
      printf("List Error: delete() called on empty List\n");
      exit(1);
   }else if(L->cursor == NULL) {
      printf("List Error: delete() called on NULL cursor\n");
      exit(1);
   }else if(L->cursor == L->front){
      deleteFront(L);
   }else if(L->cursor == L->back){
      deleteBack(L);
   }else {
      Node temp = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor = NULL;
      L->index = -1;
      L->length--;
      freeNode(&temp);
   }
}

// Other operations -----------------------------------------------------------
//printList() 
// return the elements of L as a String pointed to by out, 
// formatted as a space-separated string
void printList(FILE* out, List L){
   if(length(L) == 0) {
      printf("List Error: printList() called on Empty List\n");
      exit(1);
   }
   for (moveFront(L); Index(L) >= 0; moveNext(L)){
      fprintf(out, "%d ", get(L));
   }
}

// copyList()
// Returns a new List identical to this List.
List copyList(List L){
   List New = newList();
   Node temp = L->front;
   
   while (temp != NULL){
      append(New, temp->data);
      temp = temp->next;
   }
   return New;
}

// concat()
// Returns a new List which is the concatenation of
// the two lists, A followed by B. The cursor in the new List
// is undefined The states of this List and L are
// unchanged.
List concatList(List A, List B){
   List AMoc = copyList(A);
   List BMoc = copyList(B);
   
   if (AMoc->back == NULL){
      return BMoc;
   } else if (BMoc->front == NULL){
      return AMoc;
   } else {
      AMoc->back->next = BMoc->front;
      BMoc->front->prev = AMoc->back;
      AMoc->back = BMoc->back;
      free(BMoc);
      return AMoc;
   }
}