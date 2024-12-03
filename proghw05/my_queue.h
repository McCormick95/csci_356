#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "process.h"

typedef struct QueueNode {
    Process *process;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

Queue* create_queue();
void enqueue(Queue *q, Process *p);
Process* dequeue(Queue *q);
int is_empty(Queue *q);
void sort_by_priority(Queue *q);
void age_processes(Queue *q);

#endif