#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "heap1.h"

#define heap_size 15


main(){
	int i, heap[heap_size];
	
	for(i = 0; i < heap_size; i++){
		heap[i] = i+1;
	}
	
	//randomize
	srand(time(NULL));
	for(i = 0; i < heap_size; i++){
		swap(&heap[i], &heap[rand()%heap_size]);
	}

	for(i = 0; i < heap_size; i++){
		printf("%d ", heap[i]);
	}
		printf("\n");
	
	view(heap, 1, 0, heap_size);
}

