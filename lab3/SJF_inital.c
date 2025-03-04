#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
    int completion_time;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].remaining_time < min_time && !proc[i].is_completed && proc[i].arrival_time <= current_time) {
            index = i;
            min_time = proc[i].remaining_time;
        }
        
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = INT_MAX;
    int completed = 0;
    
    int prev = -1;
    
    int execution_order[1000] = {};
    int execution_order_idx = 0;

    // Initialize waiting and turnaround times
    // and other things
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].is_completed = 0;
        
        if (current_time > proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
    }
    
    printf("first process arrives at time %d.\n\n", current_time);
    
    // Build the loop to execute processes in the queue list
    while (completed != n) {
        int index = findNextProcess(proc, current_time);
        
        // all processes currently complete, so find the next arrival time
        if (index == -1) {
            current_time = INT_MAX;
            
            for (int i = 0; i < n; i++) {
                if (current_time > proc[i].arrival_time && !proc[i].is_completed) {
                    index = i;
                    current_time = proc[i].arrival_time;
                }
            }
        }
        
        // execution_order OOB is checked in case of programmer error
        if (
            prev != index
            && execution_order_idx < (sizeof(execution_order) / sizeof(execution_order[0]))) {
            execution_order[execution_order_idx] = proc[index].process_id;
            execution_order_idx += 1;
            prev = index;
        }
        
        // Process found to execute
        
        // finding when either a new process arrives or the current process finishes
        int next_check_time = proc[index].remaining_time;
        
        for (int i = 0; i < n; i++) {
            int time_before_arrival = proc[i].arrival_time - current_time;
            
            if (
                time_before_arrival > 0
                && next_check_time > time_before_arrival
                && (proc[index].remaining_time - time_before_arrival) > proc[i].burst_time) {
                next_check_time = time_before_arrival;
            }
        }
        
        // updating stats
        current_time += next_check_time;
        proc[index].remaining_time -= next_check_time;
        if (proc[index].remaining_time <= 0) {
            completed += 1;
            proc[index].is_completed = 1;
            proc[index].completion_time = current_time;
        }
    }
    
    // printing some stats
    double combined_turnaround_time = 0.0;
    double combined_waiting_time = 0.0;
    
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        combined_turnaround_time += proc[i].turnaround_time;
        combined_waiting_time += proc[i].waiting_time;
    }
    
    printf("Execution Order: ");
    printf("%d", execution_order[0]);
    for (int i = 1; i < execution_order_idx; i++) {
        printf(" -> %d", execution_order[i]);
    }
    
    printf(
        "\n\nall processes finished at time %d.\naverage turnaround time: %f.\naverage waiting time: %f.\n\n",
        current_time,
        combined_turnaround_time / n,
        combined_waiting_time / n
    );
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\t  Completion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d\n",
            proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
            proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time
        );
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
