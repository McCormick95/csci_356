#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "my_queue.h"
#include "process.h"

#define MAX_PROCESSES 25

typedef struct {
    Process processes[MAX_PROCESSES];
    int process_count;
    queue ready_queue;
    Process *current_process;
    int current_time;
    char algorithm[5];
} Scheduler;

void init_scheduler(Scheduler *s, char *algorithm);
void run_scheduler(Scheduler *s);
void handle_process_arrival(Scheduler *s, int time);
void handle_process_completion(Scheduler *s);
void print_statistics(Scheduler *s);
void sort_by_priority(queue q);
void age_processes(queue q);

#endif