#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>

#define N 5

void *Producer();
void *Consumer();

//Shared Variables
int count = 0;
int buffer[N];

void *Producer(void *a){
	int item, in=0;

	while(1){
		item = rand()%N;
		while(count == N);

		buffer[in] = item;
		printf("Producer: %i %i\n", in, item);
		in = (in + 1) % N;
		count++;
		sleep(rand()%5);
	}
}

void *Consumer(void *a){
	int out=0, item;

	while(1){
		while(count == 0);

		item = buffer[out];
		printf("Consumer: %i %i\n", out, item);
		out = (out + 1) % N;
		count--;
		sleep(rand()%5);
	}
}
