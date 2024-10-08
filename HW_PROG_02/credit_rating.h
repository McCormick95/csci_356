#ifndef CREDIT_RATING_H
#define CREDIT_RATING_H

typedef struct {
    char name[50];
    int creditRating;
} Person;

void processInput(Queue* q, int* maxRating);
void displayResults(Queue* q, int maxRating);

#endif // CREDIT_RATING_H