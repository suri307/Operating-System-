#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;         // Semaphore for writers
pthread_mutex_t mutex; // Mutex for readers
int readcount = 0; // Number of active readers
int data = 0;      // Shared data

void* writer(void* arg) {
    int writer_id = *(int*)arg;
    sem_wait(&wrt); // Writer wants exclusive access
    data++;
    printf("\nWriter %d is writing data = %d", writer_id, data);
    sleep(1);
    printf("\nWriter %d finished writing.", writer_id);
    sem_post(&wrt); // Release access
    return NULL;
}

void* reader(void* arg) {
    int reader_id = *(int*)arg;
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt); // First reader locks writer
    pthread_mutex_unlock(&mutex);

    printf("\nReader %d is reading data = %d", reader_id, data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt); // Last reader releases writer
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t rtid[5], wtid[2];
    int r[5] = {1, 2, 3, 4, 5}, w[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&wtid[0], NULL, writer, &w[0]);
    pthread_create(&rtid[0], NULL, reader, &r[0]);
    pthread_create(&rtid[1], NULL, reader, &r[1]);
    pthread_create(&wtid[1], NULL, writer, &w[1]);
    pthread_create(&rtid[2], NULL, reader, &r[2]);

    for (int i = 0; i < 2; i++)
        pthread_join(wtid[i], NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(rtid[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}

