/* Using 'shmget' and 'shmat' - READS from the shared-memory 

		STEPS:
	1. Create a shared-memory segment
		SYNTAX: int shmget(key_t KEY, int sizeInBytes, int mode)
		RETURN: int segment_id --> shared-memory ID or -1 (ERROR)
			

	2. Attach shared-memory segment to the address sapce of a process
		SYNTAX: int* shmat(int segment_id, void* pointerLocationToAttach, int mode)
		RETURN: int* shared_memory --> pointer to shared memory segment or -1 (ERROR)

	3. Detach. If we're done with the shared-memory segment, we call shmdt to detach it
   		SYNTAX: int* shmdt (void* pointerLocationToAttach);     
		RETURN: 0 (SUCCESSFUL), -1 (ERROR)
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define MY_KEY 1234

main(){
	key_t key = MY_KEY;
	int segment_id;		/* shared-memory segment ID */
	int *shared_memory;
	int i;

	/* 1. Create a shared-memory segment of 10 integers
		0666 = (Reading + Writing) --> use for the 'client' process
	*/

	segment_id = shmget(key, 10*sizeof(int), 0666);
	
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
	for(i=0; i<10; i++){
		printf("%d\n", *shared_memory++);
	}

}
