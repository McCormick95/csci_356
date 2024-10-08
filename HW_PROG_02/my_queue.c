#include "my_queue.h"
#include <stdlib.h>

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

void* dequeue(Queue* q) {
    if (isEmpty(q)) return NULL;

    Node* temp = q->front;
    void* data = temp->data;

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
    q->size--;
    return data;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void destroyQueue(Queue* q) {
    while (!isEmpty(q)) {
        void* data = dequeue(q);
        free(data);
    }
    free(q);
}