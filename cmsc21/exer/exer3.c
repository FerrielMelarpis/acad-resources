/*
	Author: Ferriel Lisandro B. Melarpis
	Section: CMSC 21 UV-5L
	Student NUmber: 2012-01065

*/
#include <stdio.h>
#include <stdlib.h>

void inputArray(int *p, int n){// gets the input from the user
	int i;
	for(i=0;i<n;i++){
		printf("Enter value of a[%d] : ", i);
		scanf("%d", (p+i));
	}
}

void outputArray(int *p, int n){// prints the value of the elements in the array
	int i;
	for(i=0;i<n;i++){
		printf("Value of a[%d] = %d\n", i, *(p+i));
	}
}

void findMinimum(int *p, int n){// prints the minimum element in the array
	int i, min;
	min = p[0];
	for(i=1;i<n;i++){
		if(min > p[i]){
			min = p[i];
		}
	}
	printf("\nMinimum element in the array is %d.\n", min);
}

void findMaximum(int *p, int n){// prints the maximum elements in the array
	int i, max;
	max = p[0];
	for(i=1;i<n;i++){
		if(max < p[i]){
			max = p[i];
		}
	}
	printf("\nMaximum element in the array is %d.\n", max);
}

void findMean(int *p, int n){// prints the average of the elements in the array
	int i;
	float sum=0, mean;
	for(i=0;i<n;i++){
		sum+=p[i];
	}
	mean = sum/n;
	printf("\nThe mean of the array is %f.\n", mean);
}

int main(){
	int *a, size;
	
	printf("Enter array size:");
	scanf("%d", &size);
	
	a=(int*) malloc(size*sizeof(int));
	
	inputArray(a,size);
	outputArray(a,size);
	
	findMinimum(a, size);
	findMaximum(a, size);
	findMean(a, size);
	
	free(a);
}
