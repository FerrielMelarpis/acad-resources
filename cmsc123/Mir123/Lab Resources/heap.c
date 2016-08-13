/********************************************************************************************
Author: 
Date: 
Program Description: 
********************************************************************************************/

#include<stdio.h>								//libraries
#include<stdlib.h>

typedef struct node{							//heap definition
   int max_heap_size;
   int size;
   int *elements;
}heap;	

int menu();
heap *create(int max);
void insertOnline(int x, heap *h);				//online insertion
void insertOffline();							//offline insertion
void printHeap();

main()											//main program
{
	heap *h=NULL;
	int choice;
	
	h = create(35);
	while((choice=menu())!=3){
		switch(choice){
			case 1: 
					  break;
			case 2: 	
		}
	}
}

int menu(){
	int choice;
	printf("\n   MENU     ");
	printf("\n[1] - Insert (Online)");
	printf("\n[2] - Insert (Offline)");
	printf("\n[3] - Exit");
	printf("\nYour choice: ");
	scanf("%i",&choice);
	return choice;
}

heap *create(int max){
	heap *h;

	h = (heap *)malloc(sizeof(heap));
	if(h==NULL)
		error("Out of space!");
	
  	h->elements = (int *)malloc(sizeof(int)*(max+1));
	if(h->elements==NULL)
		error("Out of space!");
			
	h->max_heap_size = max;
	h->size = 0;

	return h;
}

void insertOnline(int x, heap *h){
  int i;

	if(is_full(h))
		error("Full!");
	else{
	  	i = ++h->size;
		while(h->elements[i/2]<x){
			h->elements[i]=h->elements[i/2];
			i/=2;
		}
		h->elements[i]=x;
	}
}