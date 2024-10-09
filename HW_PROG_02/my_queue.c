#include "my_queue.h"
#include <stdlib.h>

queue newqueue() {
    queue q = (queue)malloc(sizeof(struct queueS));
    q->front = NULL;
    return q;
}

int isempty(const queue q) {
    return q->front == NULL;
}

void enqueue(queue q, void* item) {
    q_element* newElement = (q_element*)malloc(sizeof(q_element));
    newElement->contents = item;
    newElement->next = NULL;

    if (isempty(q)) {
        q->front = newElement;
    } else {
        q_element* current = q->front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newElement;
    }
}

void* dequeue(queue q) {
    if (isempty(q)) {
        return NULL;
    }

    q_element* frontElement = q->front;
    void* item = frontElement->contents;
    q->front = frontElement->next;
    free(frontElement);
    return item;
}

void* peek(queue q) {
    if (isempty(q)) {
        return NULL;
    }
    return q->front->contents;
}