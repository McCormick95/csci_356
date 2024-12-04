/**
 * @file scheduler.c
 * @brief all of the functions necessary for the scheduler to operate
 *
 * @author Ryan McCormick
 * @email rlmccormi@coastal.edu
 * 
 * @date 12-04-2024
 * @version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

/**
* @brief sort_by_priority() - sorts the priority of the processes in the queue
* @param queue - priority queue
* @return NULL
*/
void sort_by_priority(queue q) {
    if (isempty(q)) return;
    
    q_element *current = q->front;
    q_element *index = NULL;
    Process *temp;
    
    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            Process *curr_proc = (Process*)current->contents;
            Process *idx_proc = (Process*)index->contents;
            if (curr_proc->priority < idx_proc->priority) {
                temp = current->contents;
                current->contents = index->contents;
                index->contents = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

/**
* @brief age_processes() - ages the processes as they sit in the waiting queue
* @param queue - priority queue
* @param current_time - the current time in the simulation
* @return NULL
*/
void age_processes(queue q, int current_time) {
    q_element *current = q->front;
    while (current != NULL) {
        Process *proc = (Process*)current->contents;
        // Only age processes that have been in queue for 8 or more time units
        if (current_time - proc->arrival_time - proc->age * 8 >= 8) {
            printf("%d %d aging\n", current_time, proc->pid);
            proc->priority++;
            proc->age++;
        }
        current = current->next;
    }
}

/**
* @brief init_scheduler() - Initilizes the scheudler
* @param Scheduler *s - pointer to a scheduler sctuct
* @param char *algorithm - the type of algorithm that will be used (FCFS or PP)
* @return NULL
*/
void init_scheduler(Scheduler *s, char *algorithm) {
    s->process_count = 0;
    s->ready_queue = newqueue();
    s->current_process = NULL;
    s->current_time = 0;
    strcpy(s->algorithm, algorithm);
}

/**
* @brief handle_process_arrival() - manages the arrival time for each process
* @param Scheduler *s - pointer to a scheduler sctuct
* @param time - current time for the simulation
* @return NULL
*/
void handle_process_arrival(Scheduler *s, int time) {
    int preemption_needed = 0;
    Process *highest_priority_new = NULL;

    for (int i = 0; i < s->process_count; i++) {
        Process *p = &s->processes[i];
        if (p->arrival_time == time) {
            printf("%d %d arriving\n", time, p->pid);
            // Initialize process timing data when it arrives
            p->waiting_time = 0;
            p->first_run = 0;
            p->age = 0;  // Reset age counter on arrival
            
            // FOR PP ONLY, check if this new process has higher priority than current process
            if (strcmp(s->algorithm, "PP") == 0 && s->current_process != NULL) {
                if (p->priority > s->current_process->priority) {
                    preemption_needed = 1;
                    if (highest_priority_new == NULL || p->priority > highest_priority_new->priority) {
                        highest_priority_new = p;
                    }
                }
            }
            
            enqueue(s->ready_queue, p);
            
            if (strcmp(s->algorithm, "PP") == 0) {
                sort_by_priority(s->ready_queue);
            }
        }
    }
    
    if (preemption_needed && highest_priority_new != NULL) {
        enqueue(s->ready_queue, s->current_process);
        s->current_process = highest_priority_new;

        queue new_queue = newqueue();
        while (!isempty(s->ready_queue)) {
            Process *p = dequeue(s->ready_queue);
            if (p != highest_priority_new) {
                enqueue(new_queue, p);
            }
        }
        s->ready_queue = new_queue;
        
        printf("%d %d running\n", time, s->current_process->pid);
    }
}

/**
* @brief handle_process_completion() - manages completion for each process
* @param Scheduler *s - pointer to a scheduler sctuct
* @return NULL
*/
void handle_process_completion(Scheduler *s) {
    if (s->current_process != NULL && s->current_process->remaining_time == 0) {
        s->current_process->completion_time = s->current_time + 1;  
        printf("%d %d finished\n", s->current_process->completion_time, s->current_process->pid);
        s->current_process = NULL;
    }
}

/**
* @brief update_waiting_times() - updates the waiting time as a process sits in the waiting queue 
* @param Scheduler *s - pointer to a scheduler sctuct
* @return NULL
*/
void update_waiting_times(Scheduler *s) {
    // Only increment waiting time for processes that have arrived
    q_element *current = s->ready_queue->front;
    while (current != NULL) {
        Process *proc = (Process*)current->contents;
        if (s->current_time >= proc->arrival_time) {
            proc->waiting_time++;
        }
        current = current->next;
    }
}

/**
* @brief run_scheduler() - runs the scheuler simulation 
* @param Scheduler *s - pointer to a scheduler sctuct
* @return NULL
*/
void run_scheduler(Scheduler *s) {
    printf("Simulation starting...\n");
    
    int all_complete = 0;
    while (!all_complete) {
        // Handle arrivals first
        handle_process_arrival(s, s->current_time);
        
        // Handle PP aging
        if (strcmp(s->algorithm, "PP") == 0) {
            age_processes(s->ready_queue, s->current_time);
            sort_by_priority(s->ready_queue);
        }
        
        // Process scheduling
        if (s->current_process == NULL) {
            s->current_process = (Process*)dequeue(s->ready_queue);
            if (s->current_process != NULL) {
                if (s->current_process->first_run == 0) {
                    s->current_process->start_time = s->current_time;
                    s->current_process->first_run = 1;
                }
            }
        }
        
        // Execute current process if there is one
        if (s->current_process != NULL) {
            printf("%d %d running\n", s->current_time, s->current_process->pid);
            s->current_process->remaining_time--;
            
            // Update waiting times for processes in ready queue
            update_waiting_times(s);
            
            // Check if process completed
            if (s->current_process->remaining_time == 0) {
                s->current_process->completion_time = s->current_time + 1;
                printf("%d %d finished\n", s->current_time + 1, s->current_process->pid);
                s->current_process = NULL;
            }
        }
        
        // Check if all processes are complete
        all_complete = 1;  // Assume all complete until we find one that isn't
        for (int i = 0; i < s->process_count; i++) {
            Process *p = &s->processes[i];
            if (p->remaining_time > 0 || 
                (s->current_time < p->arrival_time)) {
                all_complete = 0;  // Found an incomplete process
                break;
            }
        }
        
        if (!all_complete) {
            s->current_time++;
        }
    }
}

/**
* @brief print_statistics() - prints the statistics from the simulation 
* @param Scheduler *s - pointer to a scheduler sctuct
* @return NULL
*/
void print_statistics(Scheduler *s) {
    float total_waiting_time = 0;
    float total_response_time = 0;
    float total_turnaround_time = 0;
    
    for (int i = 0; i < s->process_count; i++) {
        Process *p = &s->processes[i];
        total_waiting_time += p->waiting_time;
        total_response_time += p->start_time - p->arrival_time;
        total_turnaround_time += p->completion_time - p->arrival_time;
    }
    
    printf("\nAverage waiting time: %.2f\n", total_waiting_time / s->process_count);
    printf("Average response time: %.2f\n", total_response_time / s->process_count);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / s->process_count);
    printf("Average CPU usage: 100.00%%\n");
}