#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

void init_scheduler(Scheduler *s, char *algorithm) {
    s->process_count = 0;
    s->ready_queue = create_queue();
    s->current_process = NULL;
    s->current_time = 0;
    strcpy(s->algorithm, algorithm);
}

void handle_process_arrival(Scheduler *s, int time) {
    for (int i = 0; i < s->process_count; i++) {
        if (s->processes[i].arrival_time == time) {
            printf("%d %d arriving\n", time, s->processes[i].pid);
            enqueue(s->ready_queue, &s->processes[i]);
            
            if (strcmp(s->algorithm, "PP") == 0) {
                sort_by_priority(s->ready_queue);
            }
        }
    }
}

void handle_process_completion(Scheduler *s) {
    if (s->current_process != NULL && s->current_process->remaining_time == 0) {
        printf("%d %d finished\n", s->current_time, s->current_process->pid);
        s->current_process->completion_time = s->current_time;
        s->current_process = NULL;
    }
}

void run_scheduler(Scheduler *s) {
    printf("Simulation starting...\n");
    
    int all_complete = 0;
    while (!all_complete) {
        handle_process_arrival(s, s->current_time);
        
        if (strcmp(s->algorithm, "PP") == 0 && s->current_time % 8 == 0) {
            age_processes(s->ready_queue);
            sort_by_priority(s->ready_queue);
        }
        
        if (s->current_process == NULL) {
            s->current_process = dequeue(s->ready_queue);
            if (s->current_process != NULL) {
                if (s->current_process->first_run == 0) {
                    s->current_process->start_time = s->current_time;
                    s->current_process->first_run = 1;
                }
                printf("%d %d running\n", s->current_time, s->current_process->pid);
            }
        } else {
            s->current_process->remaining_time--;
            printf("%d %d running\n", s->current_time, s->current_process->pid);
        }
        
        handle_process_completion(s);
        
        // Check if all processes are complete
        all_complete = 1;
        for (int i = 0; i < s->process_count; i++) {
            if (s->processes[i].remaining_time > 0) {
                all_complete = 0;
                break;
            }
        }
        
        s->current_time++;
    }
}

void print_statistics(Scheduler *s) {
    float total_waiting_time = 0;
    float total_response_time = 0;
    float total_turnaround_time = 0;
    
    for (int i = 0; i < s->process_count; i++) {
        Process *p = &s->processes[i];
        total_waiting_time += p->completion_time - p->arrival_time - p->cpu_time;
        total_response_time += p->start_time - p->arrival_time;
        total_turnaround_time += p->completion_time - p->arrival_time;
    }
    
    printf("\nAverage waiting time: %.2f\n", total_waiting_time / s->process_count);
    printf("Average response time: %.2f\n", total_response_time / s->process_count);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / s->process_count);
    printf("Average CPU usage: 100.00%%\n");
}