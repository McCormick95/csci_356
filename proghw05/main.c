#include <stdio.h>
#include <string.h>
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: scheduler [FCFS | PP]\n");
        return 1;
    }
    
    if (strcmp(argv[1], "FCFS") != 0 && strcmp(argv[1], "PP") != 0) {
        printf("Invalid scheduling algorithm\n");
        return 1;
    }
    
    Scheduler scheduler;
    init_scheduler(&scheduler, argv[1]);
    
    // Read input
    int pid, arrival_time, cpu_time, priority;
    while (1) {
        if (strcmp(argv[1], "PP") == 0) {
            scanf("%d %d %d %d", &pid, &arrival_time, &cpu_time, &priority);
        } else {
            scanf("%d %d %d", &pid, &arrival_time, &cpu_time);
            priority = 0;
        }
        
        if (pid == 0) break;
        
        Process *p = &scheduler.processes[scheduler.process_count];
        p->pid = pid;
        p->arrival_time = arrival_time;
        p->cpu_time = cpu_time;
        p->priority = priority;
        p->remaining_time = cpu_time;
        p->first_run = 0;
        p->age = 0;
        
        scheduler.process_count++;
    }
    
    run_scheduler(&scheduler);
    print_statistics(&scheduler);
    
    return 0;
}