#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 10

int *init_array(int n){
	int *a;
	a = (int *)malloc(n*sizeof(int));
}

void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void input(int a[],int n){
	int i;
	
	srand(time(NULL));
	
	for(i = 0; i < n; i++){
		a[i] = n-i;
	}
	
	for(i = 0; i < n; i++){
		swap(&a[i], &a[rand()%n]);
	}
}

void output(int a[], int n){
	int i;
	
	for(i = 0; i < n; i++){
		printf("%3i ",a[i]);
	}
	printf("\n");
}

void shsort(int a[], int n){//shell sort
	int i, j, hk, d;
	
	for (hk = n/2; hk > 0; hk /= 2){
        for(d = 0; d < hk; d++){
            for(i = d+hk; i < n; i += hk){
                for(j = i; j > d; j -= hk){
                    if (a[j-hk] > a[j])
                       swap(&a[j-hk], &a[j]);
                    else
                        break;
                }
            }
        }
    }
}

void isort(int a[], int n){//insertion sort
	int i, j;
	
	for(i = 1; i < n; i++){
		for(j = i; j > 0; j--){
			if(a[j-1] > a[j])
				swap(&a[j-1], &a[j]);
			else break;
		}
	}

}

void ssort(int a[], int n){//selection sort
	int i, j;
	
	for(i = 0; i < n-1; i++){
		for(j = i+1; j < n; j++){
			if(a[i] > a[j])
				swap(&a[i], &a[j]);
		}
	}
}

void bsort(int a[], int n){//bubble sort
	int i, j;
	
	for(i = 0; i < n-1; i++){
		for(j = 0; j < n-i-1; j++){
			if(a[j] > a[j+1])
				swap(&a[j], &a[j+1]);
		}
	}
}

void merge(int a[],int n){
	int *temp,i ,j ,k;

	if(n > 1){
		temp = (int *)malloc(n*sizeof(int));
		
		for(i = 0, j = n/2, k = 0; k < n; k++)
			temp[k] = ((i < n/2 && a[i] < a[j]) || j >= n) ? a[i++]:a[j++];
		
		memcpy(a, temp, n*sizeof(int));
		if(temp!=NULL) free(temp);
	}
}

void msort(int a[], int n){//merge sort
	if(n > 1){
		msort(a, n/2);
		msort(&a[n/2], n-(n/2));
		merge(a, n);
	}
}

int partition(int a[], int n){
	int i, j, pivot = 0;
	
	if(n > 1){
		i = 1,j = n-1;
		while(i <= j){
			while(i <= j && a[i] < a[0])
				i++;
			while(a[j] > a[0]) 
				j--;
			
			if(i < j) swap(&a[i], &a[j]);
		}
		if(j){
			swap(&a[0], &a[j]);
			pivot = j;
		}
	}
	return pivot;
}

void myqsort(int a[], int n){//quick sort
	int pivot;
	if(n > 1){
		pivot = partition(a, n);
		myqsort(a, pivot);
		myqsort(&a[pivot+1], n-pivot-1);
	}
}

int leftChild(int i){
	return 2 * i + 1;
}

int rightChild(int i){
	return 2 * i + 2;
}
 
void percolateDown(int a[], int root, int bottom) {
	int maxChild;
 
	maxChild = (rightChild(root) <= bottom && a[leftChild(root)] < a[rightChild(root)])? rightChild(root):leftChild(root);
	if(maxChild > bottom || a[root] >= a[maxChild]) return;
	swap(&a[root], &a[maxChild]);	
	percolateDown(a, maxChild, bottom);	
}

void heapsort(int a[], int n) {//heap sort
	int i;

	for (i = (n/2)-1; i >= 0; i--) {
		percolateDown(a, i, n - 1);
	}
 
	for (i = n-1; i >= 1; i--) {
		swap(&a[0], &a[i]);
		percolateDown(a, 0, i - 1);
	}
}


main(){
	int *a;
	clock_t start, end;
	double cpu_time_used;

	a = init_array(N);
	input(a, N);
	printf("Input:\n");
   output(a, N);
	start = clock();
	bsort(a, N);//change this part for the sorting algorithm
	end = clock();
	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("Output:\n");
	output(a, N);
	printf("\nTOTAL CPU TIME USED: %0.2f\n",cpu_time_used);
	
	if(a != NULL) free(a);
}

