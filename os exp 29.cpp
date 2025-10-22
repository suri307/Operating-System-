#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5  // Buffer size

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty; // Counts empty slots
sem_t full;  // Counts filled slots
pthread_mutex_t mutex; // Mutual exclusion

void* producer(void* arg) {
    int item, i;
    for (i = 0; i < 10; i++) {
        item = i + 1;
        sem_wait(&empty);       // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);        // Signal filled slot
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item, i;
    for (i = 0; i < 10; i++) {
        sem_wait(&full);        // Wait for filled slot
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d at %d\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);       // Signal empty slot
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // Initialize empty slots
    sem_init(&full, 0, 0);     // Initialize full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

