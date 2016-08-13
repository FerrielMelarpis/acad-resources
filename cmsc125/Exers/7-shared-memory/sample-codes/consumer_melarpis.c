/*
 * Ferriel Lisandro B. Melarpis
 * 2012-01065
 * CMSC 125 ST-8L
 * Exer 7 Shared Memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MY_KEY 1234
#define N 5

int main(){
	key_t key = MY_KEY;
	int segment_id;		/* shared-memory segment ID */
	int *shared_memory;
	int i;

	/* 1. Create a shared-memory segment of 10 integers
		0666 = (Reading + Writing) --> use for the 'client' process
	*/

	segment_id = shmget(key, 6*sizeof(int), 0666);
	
	if (segment_id < 0) {
	   	printf("shmget error\n");
	   	exit(1);
	}

	/* Now the shared-memory segment ID is stored in 'segment_id' */

	/* 2. Attach the shared-memory segment to the address space of this process */
	shared_memory = shmat(segment_id, NULL, 0);	/* mode 0 = read + write, mode 1 = read-only */

	if(shared_memory == (int *)-1){
  		printf("shmat error\n");
	   	exit(1);
	}

	/* Ouput the things written in the shared-memory */
    i = 0;
    while(1) {
        while(shared_memory[N] <= 0); // wait till the resource is not empty
	   	printf("Consumer: %d\n", shared_memory[i]);
        i = (i + 1) % N;
        shared_memory[N]--; // decrement counter
        sleep(rand() % N); // delay
    }
    return 0;
}
