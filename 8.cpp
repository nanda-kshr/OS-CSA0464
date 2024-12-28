#include <stdio.h>


void roundRobin(int n, int at[], int bt[], int quant) {
    int i, temp[n], wt = 0, tat = 0, count = 0, sum = 0, y = n;
    float avg_wt, avg_tat;

    for (i = 0; i < n; i++) {
        temp[i] = bt[i];
    }

    printf("\n Process No \t\t Burst Time \t\t Turn Around Time \t Waiting Time\n");


    for (sum = 0, i = 0; y != 0;) {
        if (temp[i] <= quant && temp[i] > 0) {
            sum += temp[i];
            temp[i] = 0;
            count = 1;
        } else if (temp[i] > 0) {
            temp[i] -= quant;
            sum += quant;
        }

        if (temp[i] == 0 && count == 1) {
            y--; 
            printf(" Process No[%d] \t\t %d \t\t\t %d \t\t\t %d\n", 
                i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            
            wt += sum - at[i] - bt[i];
            tat += sum - at[i];       
            count = 0;
        }


        if (i == n - 1) {
            i = 0;
        } else if (at[i + 1] <= sum) {
            i++;
        } else {
            i = 0;
        }
    }


    avg_wt = (float)wt / n;
    avg_tat = (float)tat / n;

    printf("\n Average Turn Around Time: \t%.2f", avg_tat);
    printf("\n Average Waiting Time: \t\t%.2f\n", avg_wt);
}


int main() {
    int NOP, i, quant;

    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);

    int at[NOP], bt[NOP];

    for (i = 0; i < NOP; i++) {
        printf("\nEnter the Arrival and Burst time of Process[%d]:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
    }


    printf("Enter the Time Quantum for the processes: ");
    scanf("%d", &quant);

    roundRobin(NOP, at, bt, quant);

    return 0;
}