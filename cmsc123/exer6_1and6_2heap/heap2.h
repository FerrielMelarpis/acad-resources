/*
Exercise 6.2: Insert and Delete in Heap/Priority Queues
April 27, 2012
Fill up the following function definitions for HEAP. You are not allowed to change the parameters nor the return types of all the functions.
*/

#include<stdio.h>

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void restore_heap(int * heap, int index, int heap_size){

}

void heap_insert(int *heap, int heap_size, int x){

}

void extract_max(int *heap, int heap_size){

}

void heap_sort(int *heap, int heap_size){

}

void display_array(int *array, int heap_size){
	for(i = 0; i < heap_size; i++){
		printf("%d ", array[i]);
	}
		printf("\n");
}

void view(int *heap, int index, int tabs, int heap_size){
	int i;
	if((heap!=NULL) && (index<=heap_size)){
		view(heap, (index*2)+1, tabs+1, heap_size);
		for(i = 0; i < tabs; i++) printf("\t");
		
		printf("%2i\n", heap[index-1]);
		view(heap, index*2, tabs+1, heap_size);
	}
}
