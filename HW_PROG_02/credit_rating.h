#ifndef CREDIT_RATING_H
#define CREDIT_RATING_H

#include "my_queue.h"

typedef struct {
    char name[50];
    int creditRating;
} Person;

/**
 * @brief Processes user input and enqueues Person objects into the queue
 * @param q Pointer to the queue to store Person objects
 * @param maxRating Pointer to store the maximum credit rating encountered
 */
void processInput(queue q, int* maxRating);

/**
 * @brief Displays the results of the credit rating analysis
 * @param q Pointer to the queue containing Person objects
 * @param maxRating The maximum credit rating encountered
 */
void displayResults(queue q, int maxRating);

#endif // CREDIT_RATING_H