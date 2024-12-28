#include<stdio.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to arrange processes by their arrival time
void arrangeArrival(int num, int mat[][6]) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (mat[j][1] > mat[j + 1][1]) {
                for (int k = 0; k < 6; k++) {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
}

void calculateTimes(int num, int mat[][6]) {
    int time = 0, min, index;

    for (int i = 0; i < num; i++) {
        min = 10000;
        index = -1;

        // Find the process with the smallest burst time that has arrived
        for (int j = i; j < num; j++) {
            if (mat[j][1] <= time && mat[j][2] < min) {
                min = mat[j][2];
                index = j;
            }
        }

        // If no process is ready, move time forward
        if (index == -1) {
            time = mat[i][1];
            i--;
            continue;
        }

        // Process the selected job
        time += mat[index][2];
        mat[index][3] = time; // Completion time
        mat[index][4] = mat[index][3] - mat[index][1]; // Turnaround time
        mat[index][5] = mat[index][4] - mat[index][2]; // Waiting time

        // Move the selected process to its sorted position
        for (int k = 0; k < 6; k++) {
            swap(&mat[i][k], &mat[index][k]);
        }
    }
}

int main() {
    int num;
    printf("Enter the number of processes: ");
    scanf("%d", &num);

    int mat[num][6]; 
    for (int i = 0; i < num; i++) {
        mat[i][0] = i + 1; 
        printf("\nEnter arrival time for process %d: ", i + 1);
        scanf("%d", &mat[i][1]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &mat[i][2]);
        mat[i][3] = mat[i][4] = mat[i][5] = 0; 
    }


    arrangeArrival(num, mat);
    calculateTimes(num, mat);


    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    printf("\n--------------------------------------------------------------------\n");

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < num; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                mat[i][0], mat[i][1], mat[i][2], mat[i][5], mat[i][4]);
        total_wt += mat[i][5];
        total_tat += mat[i][4];
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / num);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / num);

    return 0;
}