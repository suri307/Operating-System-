#include <stdio.h>

int main() {
    int n, i, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], remainingTime[n], waitingTime[n], turnaroundTime[n];
    int totalTime = 0;

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainingTime[i] = burstTime[i]; // initialize remaining time
        waitingTime[i] = 0; // initialize waiting time
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    int t = 0; // Current time
    int done;

    printf("\nGantt Chart:\n|");

    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0;
                if (remainingTime[i] > timeQuantum) {
                    t += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                    printf(" P%d |", i + 1);
                } else {
                    t += remainingTime[i];
                    waitingTime[i] = t - burstTime[i];
                    remainingTime[i] = 0;
                    printf(" P%d |", i + 1);
                }
            }
        }
    } while (!done);

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    // Display results
    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate averages
    float totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}

