#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;
int counter = 0;

// Function 1: Print Hello from Thread
void* helloThread(void* arg) {
    int id = *((int*)arg);
    printf("Hello from Thread %d\n", id);
    return NULL;
}

// Function 2: Increment counter with mutex
void* incrementCounter(void* arg) {
    int id = *((int*)arg);
    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("Thread %d incremented counter: %d\n", id, counter);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

// Function 3: Print square of a number
void* printSquare(void* arg) {
    int num = *((int*)arg);
    printf("Square of %d is %d\n", num, num*num);
    return NULL;
}

int main() {
    int choice;
    pthread_mutex_init(&lock, NULL);

    while(1) {
        printf("\n--- THREAD DEMO MENU ---\n");
        printf("1. Create Threads and Print Hello\n");
        printf("2. Thread Synchronization using Mutex\n");
        printf("3. Pass Arguments to Threads (Print Square)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 4) break;

        pthread_t t1, t2;
        int id1 = 1, id2 = 2;
        int num;

        switch(choice) {
            case 1:
                pthread_create(&t1, NULL, helloThread, &id1);
                pthread_create(&t2, NULL, helloThread, &id2);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                break;

            case 2:
                counter = 0;
                pthread_create(&t1, NULL, incrementCounter, &id1);
                pthread_create(&t2, NULL, incrementCounter, &id2);
                pthread_join(t1, NULL);
                pthread_join(t2, NULL);
                printf("Final counter value: %d\n", counter);
                break;

            case 3:
                printf("Enter number to find square: ");
                scanf("%d", &num);
                pthread_create(&t1, NULL, printSquare, &num);
                pthread_join(t1, NULL);
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    pthread_mutex_destroy(&lock);
    printf("Program exited.\n");
    return 0;
}

