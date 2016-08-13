/*
  (c)Ferriel Lisandro B. Melarpis
	CMSC 21 UV-5L
	2012-01065
	CAS BSCS
	University Of The Philippines Los Banos
	"Knowledge is Free.We are anonymous.We are Legion"
	 								
	 								-Anonymous
	 								
	"People should not be afraid of their government, government should be afraid of their people"
	 								
	 								-V for Vendetta
	(echos lang yan ma'am haha :D)
*/

//A program that computes for the Multiplication of two Matrices that applies the usage of 2d dynamic array

#include <stdio.h>
#include <stdlib.h>

// Declaring structure that contains a double pointer for creating dynamic array and its number of rows and columns
typedef struct{
    int **m;
    int row;
    int col;
}matrix;
// Function that prints the elements in the matrix 
void printMatrix(int **p, int r, int c){
    int i, j;
    for(i=0;i<r;i++){
        putchar('\t');
        for(j=0;j<c;j++){
            printf("%d\t", p[i][j]);
        }
        putchar('\n');
    }
}

//main
int main(){
    matrix a, b, c;
    int i, j, k;
    //inputs for the first matrix
    printf("First Matrix\n"); 
    printf("Enter number of rows : ");
    scanf("%d", &a.row);
    printf("Enter number of columns : ");
    scanf("%d", &a.col);
    //inputs for the second matrix
    printf("Second Matrix\n");
    printf("Enter number of rows : ");
    scanf("%d", &b.row);
    printf("Enter number of columns : ");
    scanf("%d", &b.col);
	// initializing the 2d dynamic array for the first matrix
    a.m = (int**)malloc(sizeof(int*)*a.row);
    if(a.m != NULL){
        for(i=0;i<a.row;i++){
            a.m[i] = (int*)malloc(sizeof(int)*a.col);
        }
    }
    // initializing the 2d dynamic array for the first matrix
    b.m = (int**)malloc(sizeof(int*)*b.row);
    if(b.m != NULL){
        for(i=0;i<b.row;i++){
            b.m[i] = (int*)malloc(sizeof(int)*b.col);
        }
    }
	// checking the matrices if valid for multiplication
	if(a.col != b.row){
        printf("The Matrices cannot be multiplied.\n");
        exit(0);
    }else{
    	   printf("The Matrices can be multiplied.\n");
       	// input elements for the first matrix
        for(i=0;i<a.row;i++){
		   for(j=0;j<a.col;j++){
		       printf("Enter value for matrix1[%d][%d] : ", i, j);
		       scanf("%d", &a.m[i][j]);
		   }
	    }
		
	    // input elements for the second matrix
	    	for(i=0;i<b.row;i++){
		   for(j=0;j<b.col;j++){
		       printf("Enter value for matrix2[%d][%d] : ", i, j);
		       scanf("%d", &b.m[i][j]);
		   }
	    }
	    //prints the first matrix
	    printMatrix(a.m, a.row, a.col);
		//prints the second matrix
	    printMatrix(b.m, b.row, b.col);
		// initialize the third matrix for the resultant of the multiplication
	    c.m = (int**)malloc(sizeof(int*)*a.row);
	    if(c.m != NULL){
		   for(i=0;i<a.row;i++){
		       c.m[i] = (int*)malloc(sizeof(int)*b.col);
		   }
	    }
	    
		   c.row = a.row;
		   c.col = b.col;
		   //initialize the value of the resultant matrix to 0
		   for(i=0;i<c.row;i++){
		       for(j=0;j<c.col;j++){
		           c.m[i][j] = 0;
		       }
		   }
		   // multiply the two matrices
		   for(i=0;i<a.row;i++){
		       for(j=0;j<b.col;j++){
		           for(k=0;k<a.col;k++){
		               c.m[i][j] += a.m[i][k] * b.m[k][j];
		           }
		       }
		   }
        printf("The product of the Matrices :\n");
        //prints the resultant matrix
        printMatrix(c.m, c.row, c.col);
    }
	
	
    for(i=0;i<a.row;i++){
        free(a.m[i]); // free the memory for the pointer of the arrays
    }
    for(i=0;i<b.row;i++){
        free(b.m[i]); // free the memory for the pointer of the arrays
    }
    for(i=0;i<c.row;i++){
        free(c.m[i]); // free the memory for the pointer of the arrays
    }

    free(a.m); //free the memory for the pointer of pointer of the arrays
    free(b.m); //free the memory for the pointer of pointer of the arrays
    free(c.m); //free the memory for the pointer of pointer of the arrays
    return 0; //returns 0 when the program successfully terminates
}
