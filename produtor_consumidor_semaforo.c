#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#define NUMCONS		2
#define NUMPROD		2
#define BUFFERSIZE	1000
pthread_t cons[NUMCONS];
pthread_t prod[NUMPROD];
int buffer[BUFFERSIZE];
int currentidx;
pthread_mutex_t buffer_mutex;
sem_t buffer_full, buffer_empty;
void *consumidor(void *arg);
void *produtor(void *arg);

int main(int argc, char **argv) {
	int i; 
	time_t t;
	srand48(time(&t));
	currentidx = 0;
	pthread_mutex_init(&buffer_mutex, NULL);
	sem_init(&buffer_full, 0, 0);
	sem_init(&buffer_empty, 0, 0);
	for(i = 0; i < NUMCONS; i++) {
		pthread_create(&(cons[i]), NULL, consumidor, NULL);
	}
	for(i = 0; i < NUMPROD; i++) {
		pthread_create(&(prod[i]), NULL, produtor, NULL);
	}
	for(i = 0; i < NUMCONS; i++) {
		pthread_join(cons[i], NULL);
	}
	for(i = 0; i < NUMPROD; i++) {
		pthread_join(prod[i], NULL);
	}
}

void *produtor(void *arg) {
	int n;
	while(1) {
		n = (int) (drand48() * 1000.0);
		pthread_mutex_lock(&buffer_mutex);
		if(currentidx == BUFFERSIZE) {
			pthread_mutex_unlock(&buffer_mutex);
			sem_wait(&buffer_full);
		} else {
			buffer[currentidx++] = n;
			if(currentidx == 1) sem_post(&buffer_empty);
			pthread_mutex_unlock(&buffer_mutex);
			printf("Produzindo numero %d\n", n);
		}
		sleep((int) (drand48() * 4.0));
	}
}


void *consumidor(void *arg) {
	int n;
	while(1) {
		pthread_mutex_lock(&buffer_mutex);
		if(currentidx > 0) {
			n = buffer[--currentidx];
			if(currentidx == (BUFFERSIZE - 1))
				sem_post(&buffer_full);
			pthread_mutex_unlock(&buffer_mutex);
			printf("Consumindo numero %d\n", n);
		} else {
			pthread_mutex_unlock(&buffer_mutex);
			sem_wait(&buffer_empty);
		}
		sleep((int) (drand48() * 4.0));
	}
}



