/*****
Exercise by rnc recario, summer AY2008-09


Student task: complete the functions in this h file
*****/

/****
NAME: 
STUDENT NO: 
SECTION: 
DATE(MM-DD-YYY): 

PROGRAM DESCRIPTION: 
****/

//MINIMUM SPANNING TREE FOR AN UNDIRECTED GRAPH

//header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define namelength 3 //length of the actual vertex name
#define maxnum_vertex 10 //maximum number of vertices
#define INFINITY_ 999 //a representation of infinity
#define EMPTY 0 //obvious naman di ba?????
#define VERT_EMPTY "0\0"
#define STACK_LIMIT 256

typedef enum {FALSE, TRUE} boolean;

//adjacency list implementation
typedef struct _ArrayLinkedList{
	int vertvalue; //value or name of the vertex in terms of NUMBER; not to be confused with cost or weight
	int num_adj; //number of adjacent vertices; this is only zero for the "malloced" nodes in the list
	int cost; //cost or weight of the existent edge
	struct _ArrayLinkedList * adjacent; //array of adjacent vertices
} AdjList;

int STACKS[STACK_LIMIT]; //stack for DFS
typedef int VISITED; //dyanmic array for visited nodes... maximum size is numvertex
int slot=0; //first empty slot in VISITED array
int TOS =0; //top of stack

int NUMVERTEX; //number of vertices in the graph


/**********************
VISITED array functions
**********************/
VISITED * createVISITED(int numvertex){

}//end of function

VISITED * destroyVISITED(VISITED * temp){

}//end of function


VISITED * init(VISITED * temp){
	int ctr;
	
	for(ctr=0; ctr < NUMVERTEX; ctr++){
		temp[ctr] = -999;
	}//for
	
	return (temp);
}//end of function


//returns TRUE if already visited; FALSE if not. The value is searched in the visited array list.
boolean isVisited(VISITED * temp, int numvertex, int vertexname){

}//end of function

//put the node that is not yet visited.. use slot variable
VISITED * markVISITED(VISITED * temp, int numvertex, int vertexname){

}//end of function

void printVisited(VISITED * temp){
	int ctr;
	
	printf("VISITED: ");
	for(ctr =0; ctr < NUMVERTEX; ctr++){
		printf("%d ", temp[ctr]);
	}//for
	printf("\n\n");
}//end of function

/**********************
STACK array functions
**********************/
void pushOperand(int vertexname){

}//end of function

int popStack(){

}//end of function

void makeNull(){

}//end of function

int topOfStack(){
}//end of function

boolean isEmpty(){

}//end of function



/**********************
AdjList functions
**********************/
AdjList * createAdjList(int numvertex){

}//end of function

AdjList * destroyAdjList(AdjList * temp, int numvertex){
	int ctr;
	AdjList * ptr;
	
	for(ctr=0; ctr < numvertex; ctr++){
		ptr = temp[ctr].adjacent;
		while(temp[ctr].adjacent != NULL){
			ptr = ptr->adjacent;
			free(temp[ctr].adjacent);
			temp[ctr].adjacent = ptr;
		}//while
		temp[ctr].adjacent = NULL;
	}//for
	free(temp);
	temp = NULL;
	return (temp);
}//end of function

//insert a value in the adjacency list; adjTo is the index of the starting node, adjNode is the end... cost is the weight of the edge
//check if adjTo and adjNode are both less than numvertex and greater than zero (0)
AdjList * insertAdj(AdjList * list, int adjTo, int adjNode, int cost){
	AdjList * temp, * ptr;
	
	if (list == NULL){
		printf("cannot insert in a non-existent Adjacency List!\n");
		return (NULL);
	}//if
	else{//existent
		if (((adjTo < NUMVERTEX) && (adjNode < NUMVERTEX)) && ((adjTo >= 0) && (adjNode >= 0))){
			temp = (AdjList *)malloc(sizeof(AdjList));
			if (temp == NULL) printf("Cannot create a node! Aborting!\n");
			else{
				//initialize new node
				temp->adjacent = NULL;
				temp->vertvalue = adjNode;
				temp->cost = cost;
				
				if (list[adjTo].adjacent == NULL){
					//list is initially empty
					list[adjTo].adjacent = temp;
					temp= NULL;
					printf("\t Appended at vertex %d an adjacent vertex %d.\n", adjTo, adjNode);
					
				}//if
				else{//not empty
					ptr = list[adjTo].adjacent;
					list[adjTo].adjacent = temp;
					temp->adjacent = ptr;
					printf("\t Appended at vertex %d an adjacent vertex %d.\n", adjTo, adjNode);
				}//else
			
			}//else
		
		}//if
		else printf("Check input for insert! input value(s) not allowed!\n");
		
		return(list);
	}//else
}//end of function


//adjacent nodes are pushed into the stack
void nextAdj(AdjList * AM, int vertex){

}//end of function







//printing the resulting adjacency list
void printList(AdjList * list){
	int ctr1;
	boolean firsttime = TRUE;
	AdjList * next;
	
	printf("\n\n\n\n\n");
	printf("Adjacency List Representation \n");
	printf("------------------------------\n");

	for(ctr1=0; ctr1 < NUMVERTEX; ctr1++){
		next = list[ctr1].adjacent;
		while(next != NULL){
			if(firsttime == TRUE){
				printf("|| %d ||----> ", ctr1);
				firsttime = FALSE;
			}//if
			printf("|%d|%d|->", next->vertvalue, next->cost);
			next = next->adjacent;
		}//while
		printf("NULL\n");
		printf("\n\n");
		firsttime = TRUE;
	}//for
}//end of function


