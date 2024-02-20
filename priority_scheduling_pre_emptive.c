#include <stdio.h>

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    int i, j, time = 0, remaining = n;

    for (i = 0; i < n; i++)
    {
        printf("\nEnter the details of process %d\n", i + 1);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &p[i].burst_time);
        printf("Enter priority: ");
        scanf("%d", &p[i].priority);
        p[i].process_id = i + 1;
        p[i].remaining_time = p[i].burst_time;
    }

    struct process temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int min_priority, min_index;
    i = 0;

    printf("\nGantt Chart:\n");

    printf("0");

    while (remaining > 0)
    {
        min_priority = 9999;
        for (j = 0; j < n; j++)
        {
            if (p[j].arrival_time <= time && p[j].remaining_time > 0)
            {
                if (p[j].priority < min_priority)
                {
                    min_priority = p[j].priority;
                    min_index = j;
                }
            }
        }

        printf("--P%d--%d", p[min_index].process_id, time + p[min_index].remaining_time);

        time += p[min_index].remaining_time;
        p[min_index].remaining_time = 0;
        p[min_index].completion_time = time;
        p[min_index].turnaround_time = p[min_index].completion_time - p[min_index].arrival_time;
        p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;
        remaining--;

        i++;
    }

    float avg_turnaround_time = 0, avg_waiting_time = 0;

    printf("\n\nProcess Details:\n");

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

        avg_turnaround_time += p[i].turnaround_time;
        avg_waiting_time += p[i].waiting_time;
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turnaround Time: %f\n", avg_turnaround_time);
    printf("Average Waiting Time: %f\n", avg_waiting_time);
}