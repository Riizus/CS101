import java.io.*;
import java.util.Scanner;

class Sparse{
	public static void main(String[] args) throws IOException{
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] token = null;

		// checks correct number of args
		if( args.length<2){
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		int Size = 0;
		int ACap= 0;
		int BCap= 0;
		int row = 0;
		int column = 0;
		double val = 0;
		
		// reads in Matrix information
		if(in.hasNextLine()){
			line = in.nextLine()+" ";
			token = line.split("\\s+");
			Size = Integer.parseInt(token[0]);
			ACap = Integer.parseInt(token[1]);
			BCap = Integer.parseInt(token[2]);
            
		}
        
		// creates matrices
		Matrix A = new Matrix(Size);
		Matrix B = new Matrix(Size);
		
        // Initialize A
		for( int i = 0; i < ACap; i++){
			if ( in.hasNextLine()){
				line = in.nextLine();
				while ( line.isEmpty() && in.hasNextLine()){
					line = in.nextLine();
				}
				line  += " ";
				token = line.split("\\s+");
				row = Integer.parseInt(token[0]);
				column = Integer.parseInt(token[1]);
				val = Double.parseDouble(token[2]);
			}
			A.changeEntry(row,column,val);
		}
        
		// Initialize B
        for ( int i = 0; i < BCap; i++){
			if(in.hasNextLine()){
				line = in.nextLine();
				while(line.isEmpty() && in.hasNextLine()){
					line = in.nextLine();
				}
				line += " ";
				token = line.split("\\s+");
				row = Integer.parseInt(token[0]);
				column = Integer.parseInt(token[1]);
				val = Double.parseDouble(token[2]);
            }
            B.changeEntry(row,column,val);
         }
        
         // Prints to the output file as specified
         Matrix temp;
         out.println("A has "+A.getNNZ()+" non-zero entries:");
         out.println(A.toString());
         if(A.getNNZ() != 0){
            out.println();
         }
         
         out.println("B has "+B.getNNZ()+" non-zero entries:");
         out.println(B.toString());
         if(B.getNNZ() != 0){
            out.println();
         }

         out.println("(1.5)*A =");
         temp = A.scalarMult(1.5);
         out.println(temp.toString());
         if(temp.getNNZ() != 0){
			out.println();
         } 

		out.println("A+B =");
		temp = A.add(B);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}
        
		out.println("A+A =");
		temp = A.add(A);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}

		out.println("B-A =");
		temp = B.sub(A);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		} 
        
		out.println("A-A =");
		temp = A.sub(A);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}
        
		out.println("Transpose(A) =");
		temp = A.transpose();
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}

		out.println("A*B =");
		temp = A.mult(B);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}
        
		out.println("B*B =");
		temp = B.mult(B);
		out.println(temp.toString());
		if(temp.getNNZ() != 0){
			out.println();
		}
        
		//close files
		in.close();
		out.close();
	}	
}
