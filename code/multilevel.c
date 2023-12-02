
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <../graphique/ProcessesInterface.h>
#define MAXx 100
#define MAX_QUEUE 3

typedef struct {
    char id[MAXx];
    int arrive_time;
    int burst;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int executed;
} Process;

int process_count = 0; // Declare process_count globally

void process_init(Process p[], int len) {
    for (int i = 0; i < len; i++) {
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].remaining_time = p[i].burst;
        p[i].executed = 0;
    }
}

void print_table(Process process[], int n1) {
    puts("+-----+-------------+------------+--------------+-----------------+---------+");
    puts("| PID | Arrive time | Burst Time | Waiting Time | Turnaround Time | Priority|");
    puts("+-----+-------------+------------+--------------+-----------------+---------+");

    for (int i = 0; i < n1; i++) {
        printf("| %2s  |     %2d      |     %2d     |      %2d      |        %2d       |    %2d   |\n",
               process[i].id, process[i].arrive_time, process[i].burst, process[i].waiting_time,
               process[i].turnaround_time, process[i].priority);
        puts("+-----+-------------+------------+--------------+-----------------+---------+");
    }
}

void MLFQ(Process processes[], int n, int quantum) {
    int time = 0;
    int quantum_values[MAX_QUEUE] = {2, 4, 8}; // Quantum values for each queue

    printf("\nGantt Chart:\n");
    printf("-----------\n");

    int done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].executed == 0) {
                done = 0;
                int priority = processes[i].priority;

                printf("| %s ", processes[i].id);
                processes[i].remaining_time -= 1;
                time++;

                if (time % 10 == 0 && priority > 0) {
                    processes[i].priority--; // Simulated promotion
                }

                if (processes[i].remaining_time == 0) {
                    processes[i].executed = 1;
                    processes[i].turnaround_time = time - processes[i].arrive_time;
                    printf("|");
                }
            }
        }
    }
    printf("\n\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int process_count = 0;
    Process *process;

    FILE *fp = fopen("inputs/inputs.txt", "r");
    if (fp == NULL) {
        printf("FILE OPEN ERROR!\n");
        return 1;
    }

    fscanf(fp, " %d", &process_count);
    process = (Process *)malloc(sizeof(Process) * process_count);

    for (int i = 0; i < process_count; i++) {
        fscanf(fp, "%s %d %d %d", process[i].id, &process[i].arrive_time, &process[i].burst, &process[i].priority);
    }

    fclose(fp);

    int quantum = 0;
    printf("Enter quantum value for all priority queues: ");
    scanf("%d", &quantum);

    process_init(process, process_count);
    MLFQ(process, process_count, quantum);

    printf("\nProcess Table with Priority:\n");
    print_table(process, process_count);
    
  
    // GTK+ main loop
    gtk_main();

    // Free allocated memory
    free(process);

    return 0;
}

    
