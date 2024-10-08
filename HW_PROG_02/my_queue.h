#ifndef MY_QUEUE_H
#define MY_QUEUE_H

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);
int isEmpty(Queue* q);
void destroyQueue(Queue* q);

#endif // MY_QUEUE_H