#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;  // Mutex variable

void* process(void* arg) {
    pthread_mutex_lock(&lock);  // Lock section
    printf("\nProcess %d is entering the critical section...", *(int*)arg);
    sleep(1);
    printf("\nProcess %d is leaving the critical section.", *(int*)arg);
    pthread_mutex_unlock(&lock);  // Unlock section
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int p1 = 1, p2 = 2, p3 = 3;

    pthread_mutex_init(&lock, NULL);  // Initialize mutex

    pthread_create(&t1, NULL, process, &p1);
    pthread_create(&t2, NULL, process, &p2);
    pthread_create(&t3, NULL, process, &p3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);  // Destroy mutex
    return 0;
}

