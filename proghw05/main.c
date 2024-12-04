/**
 * @file main.c
 * @brief Reads input parameters and runs the scheduler for this project
 *
 * @author Ryan McCormick
 * @email rlmccormi@coastal.edu
 * 
 * @date 12-04-2024
 * @version 1.0
 *
 */

#include <stdio.h>
#include <string.h>
#include "scheduler.h"

/**
* @brief main for the program - takes user input and starts scheduler
* @param argc - count for argv[]  
* @param argv[] - arguments array for program
* @return 0
*/
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
    char line[100];
    
    while (fgets(line, sizeof(line), stdin)) {
        // Try to read all 4 values
        int read_count = sscanf(line, "%d %d %d %d", &pid, &arrival_time, &cpu_time, &priority);
        
        if (read_count < 3) {  
            break;
        }
        
        if (pid == 0) break;
        
        // Validate input
        if (pid < 0 || arrival_time < 0 || cpu_time <= 0) {
            continue; 
        }
        
        if (scheduler.process_count >= MAX_PROCESSES) {
            printf("Too many processes\n");
            return 1;
        }
        
        Process *p = &scheduler.processes[scheduler.process_count];
        p->pid = pid;
        p->arrival_time = arrival_time;
        p->cpu_time = cpu_time;
        p->priority = (strcmp(argv[1], "PP") == 0) ? priority : 0;
        p->remaining_time = cpu_time;
        p->first_run = 0;
        p->age = 0;
        p->start_time = 0;         // Initialize start_time
        p->completion_time = 0;    // Initialize completion_time
        p->waiting_time = 0;       // Initialize waiting_time
        
        scheduler.process_count++;
    }
    
    if (scheduler.process_count == 0) {
        printf("No valid processes read\n");
        return 1;
    }
    
    run_scheduler(&scheduler);
    print_statistics(&scheduler);
    
    return 0;
}