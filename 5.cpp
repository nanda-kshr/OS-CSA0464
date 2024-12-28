#include <stdio.h>

// Define a structure to hold process details
struct priority_scheduling {
    char process_name;      // Process Name (A, B, C, ...)
    int burst_time;         // Burst Time
    int waiting_time;       // Waiting Time
    int turn_around_time;   // Turnaround Time
    int priority;           // Priority (Higher value = Higher priority)
};

int main() {
    int number_of_process; // Number of processes
    int total = 0;         // Total time accumulator
    struct priority_scheduling temp_process; // Temporary structure for swapping
    int ASCII_number = 65; // ASCII code for process names (A, B, C, ...)
    int position;          // Position for sorting
    float average_waiting_time;
    float average_turnaround_time;

    // Input: Number of processes
    printf("Enter the total number of Processes: ");
    scanf("%d", &number_of_process);

    // Array to store process details
    struct priority_scheduling process[number_of_process];

    // Input: Burst Time and Priority for each process
    printf("\nPlease Enter the Burst Time and Priority of each process:\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].process_name = (char) ASCII_number; // Assign process name (A, B, ...)
        printf("\nEnter the details of the process %c \n", process[i].process_name);
        printf("Enter the burst time: ");
        scanf("%d", &process[i].burst_time);
        printf("Enter the priority: ");
        scanf("%d", &process[i].priority);
        ASCII_number++; // Move to the next process name
    }

    // Sort processes by priority (Descending order)
    for (int i = 0; i < number_of_process; i++) {
        position = i;
        for (int j = i + 1; j < number_of_process; j++) {
            if (process[j].priority > process[position].priority) {
                position = j;
            }
        }
        // Swap the processes
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // Calculate Waiting Time (WT)
    process[0].waiting_time = 0; // Waiting time of the first process is 0
    for (int i = 1; i < number_of_process; i++) {
        process[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
            process[i].waiting_time += process[j].burst_time;
        }
        total += process[i].waiting_time; // Accumulate total waiting time
    }
    average_waiting_time = (float) total / (float) number_of_process; // Calculate average WT

    // Calculate Turnaround Time (TAT)
    total = 0; // Reset total for TAT
    printf("\n\nProcess_name \t Burst Time \t Waiting Time \t Turnaround Time\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time; 
        total += process[i].turn_around_time; 
        printf("\t %c \t\t %d \t\t %d \t\t %d\n",
               process[i].process_name,
               process[i].burst_time,
               process[i].waiting_time,
               process[i].turn_around_time);
        printf("------------------------------------------------------------\n");
    }
    average_turnaround_time = (float) total / (float) number_of_process;


    printf("\n\n Average Waiting Time : %.2f", average_waiting_time);
    printf("\n Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}