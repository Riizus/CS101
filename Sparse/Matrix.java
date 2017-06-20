//---------------------------------------------//
//
//   Riise Kennard, riakenna@ucsc.edu          //
//   CMPS101 PA3
//
//   Matrix.java
//
//   Matrix ADT for Sparce.java
//
//
//---------------------------------------------//

class Matrix{

   private class Entry{
      // Fields
      int col;
      double data;
      
            
      // Constructor
      Entry(int col, double data) { 
         this.col = col;
         this.data = data;
      }
      
      // compareTo()
      // returns 1 if this col # is greater than objects's
      // 0 if equal and -1 if less than
      int compareTo(Entry x){
         if (this.col > x.col){
            return 1;
         } else if (this.col == x.col){
            return 0;
         } else {
            return -1;
         }
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         if (!(x instanceof Entry)){
            throw new RuntimeException("Matrix Error: equals() called on invalid type");
         } 
         Entry Ent = (Entry) x;
         return (this.col==Ent.col);
      }
      
      // toString()
      // returns the column and data as an ordered pair
      public String toString(){
         return "(" + this.col+", "+this.data+")";
      }
   }
   
   // Fields
   int size;
   int capacity;
   List[] Rows;
   

   // Constructor

   // Matrix() 
   // Makes a new n x n zero Matrix. pre: n>=1
   Matrix(int n){
      if( n < 1){
         throw new RuntimeException(
            "Matrix error: trying to create empty matrix");
      }
      this.size = n;
      Rows = new List[n];
      for (int i = 0; i < n; i++){
         Rows[i] = new List();
      }
   }
   
   // Access functions
   
   
   // int getSize() 
   // Returns n, the number of rows and columns of this Matrix
   int getSize(){
      return this.size;
   }
   
   // int getNNZ() 
   // Returns the number of non-zero entries in this Matrix
   int getNNZ(){
      return this.capacity;
   }
   
   // getEntry()
   // Returns data from entry in list at specified column.
   // Returns 0 if no Entry is found
   // Also leaves cursor of this list at that element.
   double getEntry(List L, int C){
      if (L.length()== 0){
         return 0;
      }
      for (L.moveFront(); L.index() >= 0; L.moveNext()){
         Entry Ent = (Entry) L.get();
         if (Ent.col == C){
            return Ent.data;
         }
      }
      return 0;
   }
   
   // public boolean equals(Object x) 
   // overrides Object's equals() method
   public boolean equals(Object x){
      if (!(x instanceof Matrix)){
          throw new RuntimeException("Matrix Error: equals() called on invalid type");
      } 
      Matrix Mat = (Matrix) x;
      if (this.size != Mat.getSize() || this.capacity != Mat.getNNZ()){
         return false;
      }
      boolean Check = true;
      List OG;
      int i;
      for(OG = Rows[i = 0]; Check && i < size; OG = Rows[i++]){
         List MatList = Mat.Rows[i];
         Check = OG.equals(MatList);
      }
      return Check;
   }
   
   
   // Manipulation procedures
   
   
   // void makeZero() 
   // sets this Matrix to the zero state
   void makeZero(){
      this.capacity = 0;
      for (int i=0; i < this.size; i++){
         if (Rows[i] == null){
             Rows[i] = new List();
         } else{
             Rows[i].clear();
         }
      }
   }
   
   // Matrix copy()
   // returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
      if (this.capacity < 1){
         return (new Matrix(this.size));
      }
      Matrix New = new Matrix(this.size);
      for (int i = 0; i < size; i++){
         List OG = Rows[i].copy();
         if (!OG.isEmpty()){
            for (OG.moveFront(); OG.index() >= 0; OG.moveNext()){
                Entry Ent = (Entry) OG.get();
                New.Rows[i].append(Ent);
            }
         }
      }
      New.capacity = capacity;
      return New;
   }
   
   // void changeEntry(int i, int j, double x)
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
      if( (i > size || i <  1) || (j > size || j < 1)){
         throw new RuntimeException(
            "Matrix error: changeEntry() called on invalid index");
      }
      List RowCheck = Rows[i-1];
      if ( x == 0){
          if (getEntry(RowCheck, j) != 0){
              RowCheck.delete();
          }
      } else {
         Entry New = new Entry(j, x);
         if (RowCheck.isEmpty()){
             RowCheck.append(New);
             capacity++;
         } else {
            RowCheck.moveFront();
            for(;;){
               if (RowCheck.index() < 0){
                  RowCheck.append(New);
                  capacity++;
                  break;
               } else {
                  Entry Ent = (Entry) RowCheck.get();
                  if (New.compareTo(Ent) == 0){
                     Ent.data = x;
                     RowCheck.voidCurs();
                     break;
                  } else if (New.compareTo(Ent) < 0){
                     RowCheck.insertBefore(New);
                     capacity++;
                     RowCheck.voidCurs();
                     break;
                  } else{
                     RowCheck.moveNext();
                  }
               }
            }
         }
      }
   }
   
   // Matrix scalarMult(double x)
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
      if (capacity == 0){
         return this.copy();
      }
      Matrix New = new Matrix(this.size);
      for (int i = 0; i < size; i++){
         List OG = Rows[i];
         if (OG.length() == 0){
            continue;
         }
         List temp = New.Rows[i];
         for (OG.moveFront(); OG.index() >= 0 ; OG.moveNext()){
            Entry Ent = (Entry)OG.get();
            temp.append(new Entry( Ent.col, x * Ent.data));
         }
      }
      return New;
   }
   
   // Matrix add(Matrix M)
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M){
      if (this.size != M.getSize()){
         throw new RuntimeException("Matrix: add() called on different sized matricies");
      } else if (this.capacity == 0){
         return M.copy();
      } else if (M.getNNZ() == 0){
         return this.copy();
      }
      Matrix New = new Matrix(this.size);
      for (int i = 0; i < size; i++){
         List OG = Rows[i].copy();
         List addList = M.Rows[i].copy();
         if (OG.length() == 0){
            New.Rows[i] = addList;
            continue;
         } else if (addList.length() == 0){
            New.Rows[i] = OG;
            continue;
         }
         List temp = New.Rows[i];
         OG.moveFront();
         addList.moveFront();
         while ( OG.index() >= 0 && addList.index() >= 0){
            Entry Ent;
            Entry OE = (Entry) OG.get();
            Entry AE = (Entry) addList.get();
            if ( OE.compareTo(AE) == 0 ){
               Ent = new Entry(OE.col, OE.data + AE.data);
               OG.moveNext();
               addList.moveNext();
            } else if (OE.compareTo(AE) < 0){
               Ent = new Entry(OE.col,OE.data);
               OG.moveNext();
            } else {
               Ent = new Entry(AE.col, AE.data);
               addList.moveNext();
            } 
            if (Ent.data != 0){
               temp.append(Ent);
            }
         }
         Entry spillOver;
         while (OG.index() > 0){
             spillOver = (Entry) OG.get();
             temp.append(spillOver);
             OG.moveNext();
         }
         while (addList.index() > 0){
             spillOver = (Entry) addList.get();
             temp.append(spillOver);
             addList.moveNext();
         }
      
      }
      return New;
   }
   
   // Matrix sub(Matrix M)
   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M){
      if (this.size != M.getSize()){
         throw new RuntimeException("Matrix: sub() called on different sized matricies");
      } else if (this.capacity == 0){
         return M.copy();
      } else if (M.getNNZ() == 0){
         return this.copy();
      }
      Matrix New = new Matrix(this.size);
      for (int i = 0; i < size; i++){
         List OG = Rows[i].copy();
         List subList = M.Rows[i].copy();
         List temp = New.Rows[i];
         if (subList.length() == 0){
            New.Rows[i] = OG;
            continue;
         } else if (OG.length() != 0){
            OG.moveFront();
            subList.moveFront();
            while ( OG.index() >= 0 && subList.index() >= 0){
               Entry Ent;
               Entry OE = (Entry) OG.get();
               Entry SE = (Entry) subList.get();
               if ( OE.compareTo(SE) == 0 ){
                  Ent = new Entry(OE.col, OE.data - SE.data);
                  OG.moveNext();
                  subList.moveNext();
               } else if (OE.compareTo(SE) < 0){
                  Ent = new Entry(OE.col,OE.data);
                  OG.moveNext();
               } else {
                  Ent = new Entry(SE.col, -1* SE.data);
                  subList.moveNext();
               } 
               if (Ent.data != 0){
                  temp.append(Ent);
               }
            }
         } else {
             subList.moveFront();
         }
         Entry spillOver;
         while (OG.index() >= 0){
             Entry Ent = (Entry) OG.get();
             spillOver = new Entry(Ent.col, Ent.data);
             temp.append(spillOver);
             OG.moveNext();
         }
         while (subList.index() >= 0){
             Entry Ent = (Entry) subList.get();
             spillOver = new Entry(Ent.col, -1* Ent.data);
             temp.append(spillOver);
             subList.moveNext();
         }
      }
      return New;
   }
   
   // Matrix transpose()
   // returns a new Matrix that is the transpose of this Matrix
   Matrix transpose(){
      if (this.capacity == 0){
         return this.copy();
      }
      Matrix New = new Matrix(this.size);
      for (int i = 0; i < size; i++){
         List OG = Rows[i].copy();
         if (OG.length() >= 1){
            for ( OG.moveFront(); OG.index() >= 0; OG.moveNext()){ 
               Entry Ent = (Entry) OG.get();
               New.changeEntry(Ent.col, i+1, Ent.data);
            }
         }
      }
      return New;
   }
   
   // Matrix mult(Matrix M)
   // returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M){
      Matrix New = new Matrix(this.size);
      if (this.size != M.getSize()){
         throw new RuntimeException("Matrix: add() called on different sized matricies");
      } else if (this.capacity == 0 || M.getNNZ() == 0){
         return New;
      }
      Matrix MTran = M.transpose();
      for (int i = 0; i < size; i++){
         List OG = Rows[i].copy();
         if (OG.length() == 0){
             continue;
         }
         
         List DotList = New.Rows[i];
         for (int j = 1; j <= size; j++){
            List TL = MTran.Rows[j-1];
            if (TL.length() == 0){
               continue;
            }
            double Sum = 0;
            for (OG.moveFront(); OG.index() >= 0; OG.moveNext()){
               Entry Ent = (Entry) OG.get();
               Sum += Ent.data * getEntry(TL, Ent.col);
            }
            if (Sum != 0){
               DotList.append(new Entry(j, Sum));
            }
         }
      }
      return New;
   }

   // Other functions
   // public String toString() 
   // overrides Object's toString() method
   public String toString(){
      String Mat = "";
      for (int i = 0; i < size; i++){
         List OG = Rows[i];
         if (OG.length() == 0){
            continue;
         }
         String Line = (i+1)+": ";
         for(OG.moveFront(); OG.index() >= 0; OG.moveNext()){
            Line += OG.get().toString() + " ";
         }
         Mat += Line + "\n";
      }
      return Mat;
   }
}