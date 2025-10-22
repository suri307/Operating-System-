#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5;  // Buffer size
int x = 0;      // Item counter

void producer() {
    --mutex;
    ++full;
    --empty;
    x++;
    printf("\nProducer produces item %d", x);
    ++mutex;
}

void consumer() {
    --mutex;
    --full;
    ++empty;
    printf("\nConsumer consumes item %d", x);
    x--;
    ++mutex;
}

int main() {
    int n;
    printf("1. Producer\n2. Consumer\n3. Exit");
    while (1) {
        printf("\n\nEnter your choice: ");
        scanf("%d", &n);
        switch (n) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("\nBuffer is full!");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("\nBuffer is empty!");
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("\nInvalid choice!");
                break;
        }
    }
    return 0;
}

