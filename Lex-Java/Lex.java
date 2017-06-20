
//------------------------------------------------------------------------------#
//   Riise Kennard, riakenna@ucsc.edu                                           #
//   CS 101: PA1                                                                #
//   Lex.java                                                                   #
//   Uses List.java ADT to read in a file of strings, sort the indexes and      #
//   print the strings in order to the designated file.                         #
//                                                                              #
//------------------------------------------------------------------------------#


import java.io.*;
import java.util.Scanner;


class Lex {
   public static void main(String[] args) throws IOException{
   
      Scanner in = null;
      PrintWriter out = null;
      
      int lineCount = 0;
      String[] words;
      
      List list = new List();
      
      
      // Checks for correct number of arguments
      if(args.length != 2){
         System.err.println("Usage: Lex, wrong number of arguments");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      // Count the number of lines
      while( in.hasNextLine() ){
         lineCount++;
         in.nextLine();
      }
       
      in.close();
      in = null;

      words = new String[lineCount];
      in = new Scanner(new File(args[0]));

      // Put all lines of the file into the String array
      int j = 0;
      while(in.hasNextLine()) {
         words[j++] = in.nextLine();
      }
      in.close();
      
      list.append(0);
      
      //sorts each word in the list individually
      for (int i = 1; i < words.length; i++){
         String temp = words[i];
         
         //sets cursor at front of list
         list.moveFront();
         
         
         while (list.cursor != null && temp.compareTo(words[list.get()]) >= 0){
             list.moveNext();
         }
         if (list != null){
            if (list.cursor != null){
               list.insertBefore(i);
            } else {
               list.append(i);
            }
         }
      }
      
      //Move cursor to front
      list.moveFront();
       
      // Loop through List to print out lines in the correct order
      while(list.index() >= 0) {
         out.println(words[list.get()]);
         list.moveNext();
      }
      
      out.close();
   }
}
