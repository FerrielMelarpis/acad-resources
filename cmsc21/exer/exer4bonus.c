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
    int**  m;
    int col;
    int row;
} matrix;
// initializes the matrices to create a 2d dynamic array
void initializeMatrix(matrix *m){
    int i,j;
    m->m=(int **)malloc(sizeof(int*)*m->row);
    for(i=0;i<m->row;i++){
        m->m[i]=(int*)malloc(sizeof(int)*m->col);
    }
    for(i=0;i<m->row;i++){
        for(j=0;j<m->col;j++){
            m->m[i][j]=0;
        }
    }
}

// prints the matrices
void printMatrix(matrix *m){
    int i,j;
    for(i=0;i<m->row;i++){
        putchar('\t');
        for(j=0;j<m->col;j++){
            printf("%d\t", m->m[i][j]);
        }
        putchar('\n');
    }
}
// takes the number of rows and columns
void inputSize(matrix *m){
	int i,j;
     printf("Enter number of rows: ");
     scanf("%d",&(m->row));
     printf("Enter number of columns: ");
     scanf("%d",&(m->col));
	initializeMatrix(m);
}
// takes the elements of the matrices
void inputMatrix(matrix *m){
    int i,j;
    printf("Enter elements of the matrix: \n");
    for(i=0;i<m->row;i++){
        for(j=0;j<m->col;j++){
        	  printf("Enter value for matrix[%d][%d] : ", i, j);
            scanf("%d", &(m->m[i][j]));
        }
    }
}

// function that multiplies the matrices
int multiplyMatrix(matrix *a, matrix *b, matrix *c){
    	int i,j,k;
    	    c->row=a->row;
    	    c->col=b->col;
    	    initializeMatrix(c);
 	    for(i=0;i<a->row;i++){
            for(j=0;j<b->col;j++){
               for(k=0;k<a->col;k++){
               c->m[i][j]+=a->m[i][k]*b->m[k][j];
               }
            }
         }
   	return 0;
}
// function that makes the memories allocated for the matrices free.
void freedom(matrix a, matrix b, matrix c ){
	int i;
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
}

//main
int main(){
    	int result;
  	matrix a,b,c;
  	  inputSize(&a);
  	  inputSize(&b);
  	  if(b.row==a.col){
  	  printf("The matrices can be multiplied.\n");
  	  inputMatrix(&a);
  	  inputMatrix(&b);
  	  putchar('\n');
  	  printMatrix(&a);
  	  printMatrix(&b);
  	  result=multiplyMatrix(&a,&b,&c);
  	  putchar('\n');
  	  if(result==0){
  	     	printf("The product of the Matrices:\n");
  	   		printMatrix(&c);
  	 	}
  	 	freedom(a, b, c);
  	  	return result;
  	  }else{
  	  	printf("The matrices cannot be multiplied.\n");
  	  	exit(0);	  	//exits the program	
  	  }
}
