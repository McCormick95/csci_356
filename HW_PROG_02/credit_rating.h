#ifndef CREDIT_RATING_H
#define CREDIT_RATING_H

#include "my_queue.h"

typedef struct {
    char name[50];
    int creditRating;
} Person;

void processInput(queue q, int* maxRating);
void displayResults(queue q, int maxRating);

#endif // CREDIT_RATING_H