/*************************************************
WARNING TO THE STUDENT:

YOU WILL ONLY EDIT THE H FILE, NOT THIS ONE!!!

NO CHANGES SHOULD BE DONE ON THIS FILE
EXCEPT
*************************************************/

#include<stdio.h>
#include "DFS.h" //minimum spanning tree library

#define numvert_used 6 //number of vertices used for exercise



int main(){
	AdjList * AM = NULL; //for the adjacency list
	VISITED * visit = NULL; //for the visited list
	AdjList * adjptr = NULL; //adjacency list
	int popped; //popped node

	visit = createVISITED(numvert_used);
	AM = createAdjList(numvert_used);
	
											//maxnum_vertex is declared in DFS.h
	if ((visit == NULL) || (AM == NULL) || (numvert_used > maxnum_vertex)){
		printf("Eng eng!!!! Nothing to do!\n");
	
	}//if
	else{
		visit = init(visit);
	
	
	
		//FIRST STEP: insert values in the adjacency List
		AM= insertAdj(AM, 0, 4, 34);
		
		AM= insertAdj(AM, 0, 2, 49);
		AM= insertAdj(AM, 0, 1, 31);
		
		AM= insertAdj(AM, 1, 3, 9);
		AM= insertAdj(AM, 1, 2, 16);
		AM= insertAdj(AM, 1, 0, 31);
		
		AM= insertAdj(AM, 2, 5, 19);
		AM= insertAdj(AM, 2, 4, 8);
		AM= insertAdj(AM, 2, 3, 22);
		AM= insertAdj(AM, 2, 1, 16);
		AM= insertAdj(AM, 2, 0, 49);
		
		AM= insertAdj(AM, 3, 5, 20);
		AM= insertAdj(AM, 3, 2, 22);
		AM= insertAdj(AM, 3, 1, 9);
		
		AM= insertAdj(AM, 4, 2, 8);			
		AM= insertAdj(AM, 4, 0, 34);

		AM= insertAdj(AM, 5, 3, 20);
		AM= insertAdj(AM, 5, 2, 19);
		
		//check if graph is correctly represented!
		printList(AM);

		//start node visiting 
		pushOperand(0);
		
		while(isEmpty() == FALSE){
			popped = popStack();
			//printf("POPPED: %d\n", popped);
			if (isVisited(visit, numvert_used, popped) == FALSE){
				visit = markVISITED(visit, numvert_used, popped);
				nextAdj(AM, popped);
			}//if node is not yet visited then visit it
		}//while
		
		printVisited(visit);
		
		AM = destroyAdjList(AM, numvert_used);
		if(AM == NULL) printf("Adjacency List destroyed!\n");

		visit = destroyVISITED(visit);
		if(visit == NULL) printf("Visited List destroyed!\n");	
	}//else
	

return (0);
}//end of function
