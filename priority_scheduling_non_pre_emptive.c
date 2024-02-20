#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void calculate_waiting_time(struct Process *processes, int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].waiting_time = current_time;
        current_time += processes[i].burst_time;
    }
}

void calculate_turnaround_time(struct Process *processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void print_processes(struct Process *processes, int n)
{
    printf("PID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void sort_processes_by_priority(struct Process *processes, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process *processes = malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++)
    {
        printf("Enter information for process %d:\n", i + 1);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].pid = i + 1;
    }
    sort_processes_by_priority(processes, n);
    calculate_waiting_time(processes, n);
    calculate_turnaround_time(processes, n);
    print_processes(processes, n);

    free(processes);

    return 0;
}