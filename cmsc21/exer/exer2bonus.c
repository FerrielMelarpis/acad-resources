/*
POINTERS AND PARAMETERS PASSING
Ferriel Lisandro B. Melarpis
2012-01065
CAS BSCS
University Of The Philippines Los Banos
*/


#include <stdio.h>

void input(int a[], int n){ // takes the value of the numbers
	int i;
	for(i=0; i<n; i++){
	printf("Enter number[%d] : ", i+1);
	scanf("%d", &a[i]);
	}
}

void output(int a[], int n){ // prints the value of the numbers
	int i;
	for(i=0; i<n; i++){
	printf("%d\t", a[i]);
	}
	printf("\n\n");
}

void swap(int *p, int *q){ // swaps the value of the two parameters
	*p = *p + *q;
	*q = *p - *q;
	*p = *p - *q;
}

void sort(int a[], int n){ // sorts the numbers in ascending order
	int i, j;
	for(i=0; i<n; i++){
		for(j=i+1; j<n; j++){
			if(a[i] > a[j]){
				swap(&a[i],& a[j]);
			}
		}
	}
}

int main(){ //main function
	int a[100], n;
	printf("How many numbers are you going to sort? ");
	scanf("%d", &n);
	input(a, n); // takes input of the program
	output(a, n); // prints the input
	sort(a, n); // sorts the input
	output(a, n); // prints the output of the program

}
