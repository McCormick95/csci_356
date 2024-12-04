/**
 * @file my_queue.c
 * @brief manages the queue of information 
 * from credit_rating.c
 *
 * @author Ryan McCormick
 * @email rlmccormi@coastal.edu
 * @date 10-09-2024
 * @version 1.0
 *
 */

#include "my_queue.h"
#include <stdlib.h>

/**
 * @brief Creates a new empty queue
 * @return A pointer to the newly created queue
 */
queue newqueue() {
    queue q = (queue)malloc(sizeof(struct queueS));
    q->front = NULL;
    return q;
}


/**
 * @brief Checks if the queue is empty
 * @param q Pointer to the queue to check
 * @return 1 if the queue is empty, 0 otherwise
 */
int isempty(const queue q) {
    return q->front == NULL;
}


/**
 * @brief Adds an item to the end of the queue
 * @param q Pointer to the queue
 * @param item Pointer to the item to be added
 */
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


/**
 * @brief Removes and returns the first item from the queue
 * @param q Pointer to the queue
 * @return Pointer to the dequeued item, or NULL if the queue is empty
 */
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


/**
 * @brief Returns the first item from the queue without removing it
 * @param q Pointer to the queue
 * @return Pointer to the first item, or NULL if the queue is empty
 */
void* peek(queue q) {
    if (isempty(q)) {
        return NULL;
    }
    return q->front->contents;
}