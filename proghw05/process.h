#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival_time;
    int cpu_time;
    int priority;
    int remaining_time;
    int start_time;     // For response time
    int completion_time;
    int waiting_time;
    int first_run;      // Flag for first execution
    int age;           // For priority aging
} Process;

#endif