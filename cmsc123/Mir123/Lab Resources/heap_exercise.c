#include<stdio.h>
#define size 10
#define minheapsize 1 //minimum size of a heap
#define exit 3

/**PROVIDE PROPER DOCUMENTATION**/

/****
NAME:
STUDENT NO:
SECTION:
DATE(MM-DD-YYY):

PROGRAM DESCRIPTION:
****/


typedef int Element_datatype;

typedef struct heap_struct{
	int maxheapsize; //maximum size of the created heap
	int numElem; //number of elements present in the heap
	Element_datatype *element; //pointer to a dynamic array of size maxheapsize
}Heap;

typedef enum {FALSE, TRUE} boolean; //for boolean functions

Heap * createPQ(int size){
}//end of function

//inserting in a heap
Heap * insertToHeap(Heap *h){}//end of function

//deleteing from a heap
Heap * deleteFromHeap(Heap *h){}//end of function

//checks if heap is empty; use TRUE or FALSE as return values
boolean isEmpty(Heap *h){}//end of function

//checks if heap is full; use TRUE or FALSE as return values
boolean isFull(Heap *h){}//end of function

//destroys a heap allocated
Heap * destroyHeap(Heap *h){}//end of function

//provides menu and interface
int getChoice(){
	int lchoice;
	
	printf("[1] Insert into heap\n");
	printf("[2] Delete from heap\n");
	printf("[3] Exit\n");
	printf("\n\tEnter choice: ");
	scanf("%d", &lchoice);

	return (lchoice);
}//end of function



/**MAIN**/
main(){
	int choice;
	Heap *heap;
	
	heap=NULL;
	
	heap = createPQ(size);
	
	
	if (heap == NULL){
		printf("No Heap created! Now get out of here!\n");	
	}
	else{
		while(1){
			choice = getChoice();
			if (choice == exit) {
				heap = destroyHeap(heap);
				printf("Successfully destroyed heap...\n");
				break;
			}//if
			else{
				switch (choice){
					case 1: break; // insert to a heap. CALL FUNCTION HERE
					case 2:	break; // delete from a call. FUNCTION HERE
					default: printf("Not in the choices!!!\n"); break;
				}//switch
			}//else
		}//while
	}//else
}//end of function