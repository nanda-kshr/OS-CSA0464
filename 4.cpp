#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input Burst Time for each process
    printf("\nEnter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("p%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Assign process numbers
    }

    // Sort processes based on Burst Time using Selection Sort
    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j; // Find the process with the smallest burst time
        }
        // Swap Burst Time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process numbers
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate Waiting Time
    wt[0] = 0; // Waiting time for the first process is 0
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j]; // Accumulate burst times of previous processes
        }
        total += wt[i];
    }
    avg_wt = (float)total / n; // Average Waiting Time

    // Calculate Turnaround Time
    total = 0; // Reset total for Turnaround Time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i]; // Turnaround Time = Burst Time + Waiting Time
        total += tat[i];
    }
    avg_tat = (float)total / n; // Average Turnaround Time

    // Display Results
    printf("\nProcess\t Burst Time \tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("p%d\t\t %d\t\t %d\t\t %d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}