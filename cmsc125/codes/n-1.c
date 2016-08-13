#include <stdio.h> 	// standard I/O functions
#include <pthread.h>	// PTHREADS
#include <semaphore.h>	// SEMAPHORES
#define N 5

void * Philosophize(void * id);

sem_t chopstick[N];

int main() {
	int i;
	// Create 5 PHILOSOPHER 
	pthread_t philo[N];
	
	// Initialize Semaphores
	for(i=0; i<N; i++){
		sem_init(&chopstick[i], 0, 1);
	}
	
	// CREATE PHILOSOPHER threads
	for(i=0; i<N; i++){
		pthread_create(&philo[i], NULL, Philosophize, (void *)i);
	}

	// JOIN PHILOSOPHER threads
	for(i=0; i<N; i++){
		pthread_join(philo[i], NULL);
	}

	return 0;
}
// N-1 algorithm
void * Philosophize(void * id) {
	int ID = (int) id;
	while(1){
		srand(time(NULL));
		// 1. THINK for a while
		printf("P%d is thinking...\n", ID);
		sleep(rand() % 5 + 1);
		if(ID == N-1) {
			// 2. PICK-UP right chopstick
			sem_wait(&chopstick[(ID + 4) % 5]);
			printf("P%d is picking up chopstick %d on his right.\n", ID, (ID + 4) % 5);
			// 3. PICK-UP left chopstick
			sem_wait(&chopstick[ID]);
			printf("P%d is picking up chopstick %d on his left.\n", ID, ID);
		} else {
			// 2. PICK-UP left chopstick
			sem_wait(&chopstick[ID]);
			printf("P%d is picking up chopstick %d on his left.\n", ID, ID);

			// 3. PICK-UP right chopstick
			sem_wait(&chopstick[(ID + 4) % 5]);
			printf("P%d is picking up chopstick %d on his right.\n", ID, (ID + 4) % 5);
		}
		// 4. EAT for a while 
		printf("P%d is eating...\n", ID);
		sleep(rand() % 5 + 1);


		// 5. RELEASE left chopstick
		sem_post(&chopstick[ID]);
		printf("P%d is releasing chopstick %d on his left.\n", ID, ID);

		// 6. RELEASE right choptick
		sem_post(&chopstick[(ID+4)%5]);
		printf("P%d is releasing chopstick %d on his right.\n", ID, (ID + 4) % 5);

	}
}