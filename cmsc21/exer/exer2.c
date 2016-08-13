/*
POINTERS AND PARAMETERS PASSING
Ferriel Lisandro B. Melarpis
2012-01065
CAS BSCS
University Of The Philippines Los Banos
*/


#include <stdio.h>

void input(int *a, int *b ,int *c){ // takes the value of the numbers
	printf("Enter value of first number : ");
	scanf("%d", a);
	printf("Enter value of second number : ");
	scanf("%d", b);
	printf("Enter value of third number : ");
	scanf("%d", c);
}

void output(int a, int b, int c){ // prints the value of the numbers
	
	printf("%d,\t%d,\t%d\t\n", a, b ,c);
	
}

void swap(int *p, int *q){ // swaps the value of the two parameters
	*p = *p + *q;
	*q = *p - *q;
	*p = *p - *q;
}

void sort(int *a, int *b, int *c){ // sorts the numbers in ascending order
	if(*a >= *b && *b >= *c){
		swap(a, c);
	}else if(*a >= *b && *b <= *c){
		if(*a >= *c){
			swap(a, c);
			if(*a >= *b){
				swap(a, b);
			}
		}
	}else if(*a <= *b && *b >= *c){
		swap(b, c);
	}
}

int main(){ //main function
	int a, b, c;
	
	input(&a, &b, &c); // takes input of the program
	output(a, b, c); // prints the input
	sort(&a, &b, &c); // sorts the input
	output(a, b, c); // prints the output of the program

}
