#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Define message structure
struct message {
    long msgType;
    char msgText[100];
};

int main() {
    key_t key = 1234; // Unique key for message queue
    int msgid;

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget failed");
        exit(1);
    }

    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process sends a message
        struct message msg;
        msg.msgType = 1; // Message type
        strcpy(msg.msgText, "Hello from Child Process!");
        msgsnd(msgid, &msg, sizeof(msg.msgText), 0);
        printf("Child: Message sent to queue.\n");
    } else {
        // Parent process receives the message
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.msgText), 1, 0);
        printf("Parent: Message received: %s\n", msg.msgText);

        // Destroy the message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}

