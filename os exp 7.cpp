#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    // Input burst times
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process P%d: ", p[i].pid);
        scanf("%d", &p[i].burstTime);
    }

    // Sort processes based on burst time (Shortest Job First)
    struct Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].burstTime > p[j].burstTime) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate waiting time
    p[0].waitingTime = 0;
    for (i = 1; i < n; i++) {
        p[i].waitingTime = p[i - 1].waitingTime + p[i - 1].burstTime;
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
    }

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    // Calculate average waiting and turnaround time
    float totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}

