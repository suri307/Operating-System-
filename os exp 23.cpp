#include <stdio.h>

int main() {
    int b[10], p[10], alloc[10];
    int nb, np, i, j;

    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i]);
        alloc[i] = -1;  // initialize allocation as not done
    }

    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (b[j] >= p[i]) {
                alloc[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, p[i]);
        if (alloc[i] != -1)
            printf("%d\n", alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

