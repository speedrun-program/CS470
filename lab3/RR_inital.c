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



// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Array to store remaining burst times
    // Assuming a maximum of 1000 executions for simplicity
    int execution_order[1000] = {};
    int execution_order_idx = 0;
    
    // Current time
    // initialize things and find the first arrival time
    int current_time = INT_MAX;
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].is_completed = 0;
        proc[i].completion_time = 0;
        
        if (current_time > proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }
    }
    
    printf("first process arrives at time %d.\n\n", current_time);

    // Keep traversing processes in round-robin manner until all of them are not done
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0 then only need to process further
            
            if (proc[i].arrival_time > current_time || proc[i].is_completed) {
                continue;
            }
            
            done = 0;
            
            // this is in the if block to avoid accessing OOB by programmer error
            if (execution_order_idx < (sizeof(execution_order) / sizeof(execution_order[0]))) {
                execution_order[execution_order_idx] = proc[i].process_id;
                execution_order_idx += 1;
            }
            
            int added_time = (quantum <= proc[i].remaining_time) ? quantum : proc[i].remaining_time;
            
            current_time += added_time;
            proc[i].remaining_time -= added_time;
            if (proc[i].remaining_time <= 0) {
                proc[i].is_completed = 1;
                proc[i].completion_time = current_time;
            }
        }
        
        // all processes currently complete, so find the soonest arrival time of remaining processes
        if (done == 1) {
            int tmp_current_time = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (current_time > proc[i].arrival_time && !proc[i].is_completed) {
                    current_time = proc[i].arrival_time;
                    done = 0;
                }
            }
            
            if (tmp_current_time != INT_MAX) {
                current_time = tmp_current_time;
            }
        }

        // If all processes are done
        if (done == 1) break;
    }

    // Print the execution order
    printf("Execution Order: ");
    printf("%d", execution_order[0]);
    for (int i = 1; i < execution_order_idx; i++) {
        printf(" -> %d", execution_order[i]);
    }
    printf("\n\nall processes finished at time %d.\n", current_time);
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    
    double combined_turnaround_time = 0.0;
    double combined_waiting_time = 0.0;
    
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        combined_turnaround_time += proc[i].turnaround_time;
        combined_waiting_time += proc[i].waiting_time;
    }
    
    printf(
        "average turnaround time: %f.\naverage waiting time: %f.\n\n",
        combined_turnaround_time / n,
        combined_waiting_time / n
    );
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\t  Completion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t  %d\n",
            proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
            proc[i].waiting_time, proc[i].turnaround_time, proc[i].completion_time
        );
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
