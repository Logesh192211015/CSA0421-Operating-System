#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5 
#define EATING_TIME 2   
#define THINKING_TIME 1     

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *) arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);

        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d has picked up the left fork.\n", id);

        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d has picked up the right fork.\n", id);

        printf("Philosopher %d is eating...\n", id);
        sleep(EATING_TIME);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d has put down the right fork.\n", id);

        pthread_mutex_unlock(&forks[left]);
        printf("Philosopher %d has put down the left fork.\n", id);

        printf("Philosopher %d is thinking...\n", id);
        sleep(THINKING_TIME);
    }
}

int main() {
    int i;
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_init(&forks[i], NULL) != 0) {
            perror("pthread_mutex_init");
            exit(1);
        }
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_destroy(&forks[i]) != 0) {
            perror("pthread_mutex_destroy");
            exit(1);
        }
    }

    return 0;
}
