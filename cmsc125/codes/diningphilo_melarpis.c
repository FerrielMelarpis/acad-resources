/*
 * Ferriel Lisandro B. Melarpis
 * 2012-01065
 * CAS BSCS
 * CMSC 125 Exercise 6 : Semaphores in Dining Philosophers Problem
 * Solution : initialize all states of philosophers to THINK
 * In order to EAT a philosoper needs to be in HUNGRY state
 * then he checks for his neighbors if they are eating.
 * 
 * NOTE: The order in which the philosopher will pick up 
 * the chopstick does not matter
 */
#include <stdio.h> 	// standard I/O functions
#include <pthread.h>	// PTHREADS
#include <semaphore.h>	// SEMAPHORES
#define N 5
#define THINK 9
#define EAT 8
#define HUNGRY 7
// This method will be performed by each philosopher
void * Philosophize(void * id);
// submethods
void pickup_chopsticks(int); // picking up both chopsticks
void drop_chopsticks(int); // dropping both copsticks
void check(int); // checking if neighbors are eating

int flag[5] = {THINK, THINK, THINK, THINK, THINK};
// Chopsticks: Shared resources
sem_t chopstick[N];
sem_t mutex;
int main()
{
	int i;
	// Create 5 PHILOSOPHER 
	pthread_t philo[N];
	// Initialize lock
	sem_init(&mutex, 0, 1);

	// Initialize Semaphores
	for(i=0; i<N; i++){
		sem_init(&chopstick[i], 0, 0);
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

void * Philosophize(void * id){
	int ID = (int) id;

	while(1){

		// THINKING phase
		printf("P%d is thinking...\n", ID);
		srand(time(NULL));
		sleep(rand()%5+1);
		// pickup the left and right chopsticks
		pickup_chopsticks(ID);		
		// EATING phase
		printf("P%d is eating...\n", ID);
		sleep(rand() % 5 + 1);
		// drop both chopsticks
		drop_chopsticks(ID);

	}

}
// function for picking up chopsticks
void pickup_chopsticks(int i) {
	sem_wait(&mutex); // lock 
	flag[i] = HUNGRY;
	check(i);
	sem_post(&mutex); // unlock
	sem_wait(&chopstick[i]); // eat if checked
}
// function for dropping chopsticks
void drop_chopsticks(int i) {
	sem_wait(&mutex); // lock
	check((i+4) % 5); // check left neighbor
	check((i+1) % 5); // check right neighbor
	sem_post(&mutex); // unlock
}
// function for checking if neighbors are NOT EATING
void check(int i) {
	if(flag[i] == HUNGRY && flag[(i - 1) % 5] != EAT && flag[(i + 1) % 5] != EAT) {
		flag[i] = EAT; // set state to EAT
		sem_post(&chopstick[i]); 
	}
}
