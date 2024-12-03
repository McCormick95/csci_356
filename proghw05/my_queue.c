#include <stdlib.h>
#include "my_queue.h"

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue *q, Process *p) {
    QueueNode *new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->process = p;
    new_node->next = NULL;
    
    if (is_empty(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

Process* dequeue(Queue *q) {
    if (is_empty(q)) return NULL;
    
    QueueNode *temp = q->front;
    Process *p = temp->process;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return p;
}

int is_empty(Queue *q) {
    return q->front == NULL;
}

void sort_by_priority(Queue *q) {
    if (is_empty(q) || q->size == 1) return;
    
    QueueNode *current = q->front;
    QueueNode *index = NULL;
    Process *temp;
    
    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->process->priority < index->process->priority) {
                temp = current->process;
                current->process = index->process;
                index->process = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

void age_processes(Queue *q) {
    QueueNode *current = q->front;
    while (current != NULL) {
        current->process->age++;
        if (current->process->age >= 8) {
            current->process->priority++;
            current->process->age = 0;
        }
        current = current->next;
    }
}