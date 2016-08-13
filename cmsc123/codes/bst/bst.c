#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "bst.h"

#define N 10

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

main(){
	bst_node *root = NULL;
	int i, a[N];
	
	for(i = 0; i < N; i++){
		a[i] = i+1;
	}
	
	//randomize
	srand(time(NULL));
	for(i = 0; i < N; i++){
		swap(&a[i], &a[rand()%N]);
	}
	
	for(i = 0; i < N; i++){
		insert_value(&root, a[i]);
		view(root, 0);
		printf("--------------Inserted %i--------------\n", a[i]);
		getc(stdin);
	}
	
	for(i = 0; i < N; i++){
		delete_node(&root, a[i]);
		view(root, 0);
		printf("--------------Deleted %i--------------\n", a[i]);
		getc(stdin);
	}
}

