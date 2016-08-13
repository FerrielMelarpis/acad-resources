#include <stdio.h>
#include <time.h>		// time()
#include <math.h>		// srand() and rand()
#include <pthread.h>	// PTHREADS
#include <semaphore.h>	// SEMAPHORES
#define N 5

// This method will be performed by each philosopher
void * Philosophize(void * id);

// Chopsticks: Shared resources
sem_t chopstick[N];

int main()
{
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
	
	pthread_exit(NULL);
	
	return 0;
}

// Generous philosophers algorithm
void * Philosophize(void * id){
	int ID = (int) id;
	int right_chopstick;
	while(1){
		right_chopstick = -1;
		while(!right_chopstick){
			// 1. THINK for a while
			printf("P%d is thinking...\n", ID);
			srand(time(NULL));
			sleep(rand()%3+1);
			
			// 2. PICK-UP left chopstick
			sem_wait(&chopstick[ID]);
			printf("P%d is picking up chopstick %d on his left.\n", ID, ID);
			
			// 3. PICK-UP right chopstick
			right_chopstick = sem_wait(&chopstick[(ID + 4) % 5]);
			if(right_chopstick == 0)
				printf("P%d is picking up chopstick on his right.\n", ID, (ID + 4) % 5);
			else{
				// drop left chopstick and give it to the philosopher in the left
				sem_post(&chopstick[ID]);
			}
		}
		
		// 4. EAT for a while 
		printf("P%d is eating...\n", ID);
		sleep(rand()%3+1);
		
		
		// 5. RELEASE left chopstick
		sem_post(&chopstick[ID]);
		printf("P%d is releasing chopstick %d on his left.\n", ID, ID);
		
		// 6. RELEASE right choptick
		sem_post(&chopstick[(ID+4)%5]);
		printf("P%d is releasing chopstick %d on his right.\n", ID, (ID + 4) % 5);
		
	}
	
}