//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA1                                                                #
//   List.java                                                                  #
//   ADT for Lex.java. Doubley-linked list with cursor to traverse it.          #
//   Comes with constructors, manipulation procedures, and access functions.    #
//                                                                              #
//------------------------------------------------------------------------------#

class List{

   private class Node{
      // Fields
      int data;
      Node next;
      Node prev;
            
      // Constructor
      Node(int data) { 
          this.data = data; 
          next = null; 
          prev = null; 
      }
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Node x){
         return (this.data==x.data);
      }
   }

   // Fields
   private Node front;
   private Node back;
   public Node cursor;
   private int cursorIndex;
   private int length;

   // Constructor
   List() { 
      this.clear();
   }


   // Access Functions --------------------------------------------------------

   // isEmpty()
   // Returns true if this List is empty, false otherwise.
   boolean isEmpty() { 
      return length==0; 
   }

   // length()
   // Returns length of this List.
   int length() { 
      return length; 
   }
   
   // index()
   // Returns index of current cursor element, if none returns -1
   int index() {
       if( cursor == null ){
         return -1;
       }
       return cursorIndex;
   }

   // front() 
   // Returns front element.
   // Pre: !this.isEmpty()
   int front(){
      if( this.isEmpty() ){
         throw new RuntimeException(
            "List Error: front() called on empty List");
      }
      return front.data;
   }
   
   // back() 
   // Returns back element.
   // Pre: !this.isEmpty()
   int back(){
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: back() called on empty List");
      }
      return back.data;
   }
   
   // get() 
   // Returns element at cursor if defined.
   // Pre: !this.isEmpty()
   int get(){
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: get() called on empty List");
      } else if (cursor == null){
         throw new RuntimeException("List Error: get() called on undefined cursor");
      }
      return cursor.data;
   }
   
   // equals()
   // Overrides Object's equals() method.  Returns true if L is a List storing
   // the same integer sequence as this List, false otherwise.
   public boolean equals(List L){
      Node N = this.front;
      Node M = L.front;
      boolean eq = (this.length==L.length);
      while( eq && N!=null ){
         eq = N.equals(M);
         N = N.next;
         M = M.next;
      }
      return eq;
   }

   // Manipulation Procedures -------------------------------------------------

   // clear()
   // Resets this List to its original empty state.
   void clear(){
      front = back = null; 
      cursor = null;
      cursorIndex = -1;
      length = 0; 
   }

   // moveFront() 
   // If List is non-empty, places the cursor under the front element,
   // otherwise does nothing.
   void moveFront(){
      if (this.isEmpty()){
          throw new RuntimeException("List Error: moveFront() called on empty List");
      }
      cursor = front;
      cursorIndex = 0; 
   }
	
   // moveBack() 
   // If List is non-empty, places the cursor under the back element,
   // otherwise does nothing.
   void moveBack(){
       if (this.isEmpty()){
           throw new RuntimeException("List Error: moveBack() called on empty List");
       }
       cursor = back;
       cursorIndex = length - 1; 
   }
	
   // movePrev()
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void movePrev(){
      if (this.isEmpty()){
          throw new RuntimeException("List Error: movePrev() called on empty List");
      } else if (cursor == null){
          return;
      } else if (cursor == front){
          cursor = null;
      } else {
          cursor = cursor.prev; 
      }
      cursorIndex--;
   }

   // moveNext()
   // If cursor is defined and not at back, moves cursor one step toward
   // back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void moveNext(){
      if (this.isEmpty()){
          throw new RuntimeException("List Error: moveNext() called on empty List");
      } else if (cursor == null){
          return;
      } else if (cursor == back){
          cursor = null;
      } else {
          cursor = cursor.next; 
      }
      cursorIndex++;
   }
   
   // prepend()
   // Inserts data to front of this List.
   void prepend(int data){
      Node N = new Node(data);
      if( this.isEmpty() ) { 
         front = back = N;
      }else{ 
         N.next = front;
         front.prev = N;
         front = N; 
      }
      if (cursor != null){
          cursorIndex++;
      }
      length++;
   }
   
   // append()
   // Inserts data to back of this List.
   void append(int data){
      Node N = new Node(data);
      if( this.isEmpty() ) { 
         front = back = N;
      }else{ 
         back.next = N;
         N.prev = back;
         back = N; 
      }
      length++;
   }
   
   // insertBefore()
   // Insert new element before cursor.
   // Pre: length()>0, index()>=0
   void insertBefore(int data){
      Node N = new Node(data);
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: insertBefore() called on empty List");
      } else if (cursor == null){
         throw new RuntimeException("List Error: insertBefore() called on undefined cursor");
      } else{
         N.prev = cursor.prev;
         N.next = cursor;
         if (cursor.prev != null){
             cursor.prev.next = N;
         } else {
             front = N;
         }
         cursor.prev = N;
         length++;
         cursorIndex++;
      }
   }
   
   // insertAfter()
   // Insert new element after cursor.
   // Pre: length()>0, index()>=0
   void insertAfter(int data){
      Node N = new Node(data);
      if( this.isEmpty() ){
         throw new RuntimeException("List Error: insertAfter() called on empty List");
      } else if (cursor == null){
         throw new RuntimeException("List Error: insertAfter() called on undefined cursor");
      } else if (cursor == back){
         append(data);       
      } else{ 
         N.prev = cursor;
         N.next = cursor.next;
         cursor.next = N;
         length++;
      }
   }
   
   // deleteFront()
   // Deletes front element from this List.
   // Pre: !this.isEmpty()
   void deleteFront(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: deleteFront() called on empty List");
      } if (cursor == front){
         cursor = null;
         cursorIndex--;
      }
      if(this.length>1){
         front = front.next;
      } else{
         front = back = null;
      }
      length--;
      if (cursor != null){
         cursorIndex--;
      }
   }
   
 
   
   // deleteBack()
   // Deletes back element from this List.
   // Pre: !this.isEmpty()
   void deleteBack(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: deleteBack() called on empty List");
      }
      if (cursor == back){
         cursor = null;
         cursorIndex = -1;
      }
      back = back.prev;
      back.next = null;
      length--;
   }
   
   // delete()
   // Deletes cursor element from this List if it exists.
   // Pre: !this.isEmpty()
   void delete(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: delete() called on empty List");
      } else if (cursor == null){
         throw new RuntimeException("List Error: delete() called on undefined cursor");
      } else if (cursor == front){
          deleteFront();
      } else if (cursor == back) {
          deleteBack();
      } else {
        cursor.prev.next = cursor.next;
        cursor.next.prev = cursor.prev;
        cursor = null;
        cursorIndex = -1;
        length--;
      }
   }


   // Other Functions ---------------------------------------------------------

   // toString()
   // Overides Object's toString() method.
   public String toString(){
      StringBuffer sb = new StringBuffer();
      Node N = front;
      while(N!=null){
         sb.append(" ");
         sb.append(N.toString());
         N = N.next;
      }
      return new String(sb);
   }


   // copy()
   // Returns a new List identical to this List.
   List copy(){
      List L = new List();
      Node N = this.front;

      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   }

   // concat()
   // Returns a new List which is the concatenation of
   // this list followed by L. The cursor in the new List
   // is undefined, regardless of the states of the cursors
   // in this List and L. The states of this List and L are
   // unchanged.
   List concat(List L){
      List tempThis = this.copy();
      List tempL = L.copy();
      if (tempThis.back != null){
         if (tempL.front != null){
            tempThis.back.next = tempL.front;
            tempL.front.prev = tempThis.back;
            tempThis.back = tempL.back;
            return tempThis;
         } else {return this;}
      } else {return L;}
   }
}