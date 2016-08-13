/*
	©Ferriel Lisandro B. Melarpis
	 University of the Philippines Los Baños
	 CAS BSCS
	 2012-01065
	 CMSC 21 UV - 5L
*/ 

/*A program that computes for combination of numbers*/
#include <stdio.h>

int nCr(int n, int r){/* a recursive function that computes for combination given n and r in the formula nCr*/
	
		if(n == r || r == 0) // base case of the problem
		return 1; 
		else
		return nCr(n-1, r-1) + nCr(n-1, r); /* returns the combination of the previous 2 numbers in pascal triangle*/
}

int main(){
	
	int n, r, result;
	printf("Enter input value for n: ");
	scanf("%d", &n); // takes value for n in nCr
	printf("Enter input value for r: ");
	scanf("%d", &r); // takes value for r in nCr
	if(n < r){
		printf("Math Error!\n"); 
	}else{
	result = nCr(n, r);
	printf("%d\n", result);
	}
}





/*
	0	1	2	3	4
0	1
1	1	1
2	1	2	1
3	1	3	3	1
4	1	4	6	4	1
*/
