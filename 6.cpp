#include <stdio.h>

struct process {
    int id;             
    int arrival_time;   
    int burst_time;     
    int priority;       
    int remaining_time; 
    int waiting_time;   
    int turnaround_time;
    int completed;     
};

int main() {
    int n, time = 0, completed = 0, min_priority_index;
    float avg_waiting_time = 0, avg_turnaround_time = 0;


    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];


    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0; 
    }

    printf("\nGantt Chart:\n");


    while (completed != n) {
        min_priority_index = -1;


        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && !processes[i].completed) {
                if (min_priority_index == -1 || processes[i].priority > processes[min_priority_index].priority) {
                    min_priority_index = i;
                }
            }
        }

        if (min_priority_index != -1) {

            printf("| P%d ", processes[min_priority_index].id);
            processes[min_priority_index].remaining_time--;
            time++;


            if (processes[min_priority_index].remaining_time == 0) {
                processes[min_priority_index].completed = 1;
                completed++;


                processes[min_priority_index].turnaround_time = time - processes[min_priority_index].arrival_time;
                processes[min_priority_index].waiting_time = processes[min_priority_index].turnaround_time - processes[min_priority_index].burst_time;


                avg_waiting_time += processes[min_priority_index].waiting_time;
                avg_turnaround_time += processes[min_priority_index].turnaround_time;
            }
        } else {

            time++;
        }
    }
    printf("|\n");

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }


    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}