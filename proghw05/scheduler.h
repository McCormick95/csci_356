#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "my_queue.h"

#define MAX_PROCESSES 25

typedef struct {
    Process processes[MAX_PROCESSES];
    int process_count;
    Queue *ready_queue;
    Process *current_process;
    int current_time;
    char algorithm[5];
} Scheduler;

void init_scheduler(Scheduler *s, char *algorithm);
void run_scheduler(Scheduler *s);
void handle_process_arrival(Scheduler *s, int time);
void handle_process_completion(Scheduler *s);
void print_statistics(Scheduler *s);

#endif