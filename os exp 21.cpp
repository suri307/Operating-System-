#include <stdio.h>

int main() {
    int b[10], p[10], alloc[10], i, j, nb, np;

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
        alloc[i] = -1;
    }

    for (i = 0; i < np; i++) {
        int worstIdx = -1;
        for (j = 0; j < nb; j++) {
            if (b[j] >= p[i]) {
                if (worstIdx == -1 || b[j] > b[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            alloc[i] = worstIdx;
            b[worstIdx] -= p[i];
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

