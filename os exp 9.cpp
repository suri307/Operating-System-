#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
    // Key for shared memory
    key_t key = 1234;

    // Size of shared memory
    int shmsize = 1024;

    // Create shared memory segment
    int shmid = shmget(key, shmsize, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    char *sharedMemory = (char *)shmat(shmid, NULL, 0);
    if (sharedMemory == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process writes to shared memory
        char message[] = "Hello from Child Process!";
        strcpy(sharedMemory, message);
        printf("Child: Message written to shared memory.\n");
        // Detach shared memory
        shmdt(sharedMemory);
    } else {
        // Parent process waits for child to write
        sleep(1); // simple synchronization
        printf("Parent: Read from shared memory: %s\n", sharedMemory);
        // Detach and destroy shared memory
        shmdt(sharedMemory);
        shmctl(shmid, IPC_RMID, NULL); // remove shared memory
    }

    return 0;
}

