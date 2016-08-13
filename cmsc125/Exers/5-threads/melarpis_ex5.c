/*
 * Ferriel Lisandro B. Melarpis
 * 2012-01065
 * CAS BS Computer Science
 * CMSC 125 ST-8L
 */
#include <stdio.h>
#include <pthread.h> // library for thread operation
#include <stdlib.h>
#include <math.h> // library for mathematical functions
#include <complex.h> // library for complex numbers representation
// global declarations
int a[3], isImag = 0;
float denom, ans1, ans2, disc, sum, diff;
float complex ans1i, ans2i, disci, sumi, diffi;
pthread_t t[6]; // threads
// 2a : funciton that computes the denominator (2a) in quadratic formula
void * denominator(void *arg1) {
	denom = (double)2*a[0];
	return NULL;
}
// sqrt(b^2-4ac) : funciton that computes the square root of the discriminant
void * discriminant_sqrt(void *args) {
   double discriminant = pow(a[1], 2.0) - (4.0 * a[0] * a[2]);
    if(discriminant >= 0)
	    disc = sqrt(discriminant);
    else { 
        isImag = 1;
        disci = sqrt(-discriminant) * I;
    }
	return NULL;
}
// -b + sqrt(b^2-4ac) : function that computes the larger numerator of quadratic formula
void * sum_numerator(void *arg1) {
    if(!isImag)
	    sum = (double)(-a[1]) + disc;
    else 
        sumi = (double)(-a[1]) + disci;
    
	return NULL;
}
// // -b - sqrt(b^2-4ac) : function that computes the smaller numerator of quadratic formula
void * difference_numerator(void *arg1) {
	if(!isImag)
        diff = (double)(-a[1]) - disc;
    else
        diffi = (double)(-a[1]) - disci;

	return NULL;
}
// // (-b (+/-) sqrt(b^2-4ac)) / 2a : function that computes the entire quadratic formula
void * quotient(void *arg1) {
	pthread_t p = pthread_self();
	if(pthread_equal(p, t[4])) {
        if(!isImag)
		    ans1 = sum/denom;
        else
            ans1i = creal(sumi)/denom + cimag(sumi)/denom * I;
	} else if(pthread_equal(p, t[5])){
        if(!isImag)
		    ans2 = diff/denom;
        else
            ans2i = creal(diffi)/denom + cimag(diffi)/denom * I;
	} else {
		fprintf(stderr, "Thread name not acceptable\n");
		exit(1);
	}
	return NULL;
}
// main
int main(int argc, char **argv) {
	if(argc != 4) {
		fprintf(stderr, "\x1b[41mUsage:\x1b[0m\x1b[31m %s <a> <b> <c>\x1b[0m\n", argv[0]);
		exit(1);
	} else if(argv[1] == 0) {
        fprintf(stderr, "\x1b[41m*** ERROR: \x1b[0m\x1b[31m The value of coefficient <a> should not be zero.\n");
        exit(2);
    }
	for(int i=0; i<3; i++) // convert arguments to integer
		a[i] = atoi(argv[i+1]);
	pthread_create(&t[0], NULL, denominator, NULL); // create first thread
	pthread_join(t[0], NULL); // wait till it finished
	pthread_create(&t[1], NULL, discriminant_sqrt, NULL); // create second thread
	pthread_join(t[1], NULL); // wait till it finished
	pthread_create(&t[2], NULL, sum_numerator, NULL); // create third thread
	pthread_join(t[2], NULL); // wait till it finished
	pthread_create(&t[3], NULL, difference_numerator, NULL); // create fourth thread
	pthread_join(t[3], NULL); // wait till it finished
	pthread_create(&t[4], NULL, quotient, NULL); // create fifth thread
	pthread_create(&t[5], NULL, quotient, NULL); // create sixth thread
    // once the answers are calculated by the thread 5 and 6 join them to main process
    pthread_join(t[4], NULL);
    pthread_join(t[5], NULL);
    if(!isImag) // if imaginary outputs
	    printf("\x1b[32mx1 = \x1b[0m%.2f\t\x1b[32mx2 = \x1b[0m%.2f\n", ans1, ans2);
    else // normal outputs
        printf("\x1b[32mx1 = \x1b[0m%.2f+%.2fi\t\x1b[32mx2 = \x1b[0m%.2f%.2fi\n", creal(ans1i), cimag(ans1i), creal(ans2i), cimag(ans2i));
	pthread_exit(NULL);
	return 0;
}// END
