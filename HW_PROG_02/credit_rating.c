#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_queue.h"
#include "credit_rating.h"


/**
 * @brief Processes user input and enqueues Person objects into the queue
 * @param q Pointer to the queue to store Person objects
 * @param maxRating Pointer to store the maximum credit rating encountered
 */
void processInput(queue q, int* maxRating) {
    char input[100];
    *maxRating = 0;

    printf("Enter credit rating data (name rating), or press Enter to finish:\n");

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '\n') {
            break;
        }

        Person* person = (Person*)malloc(sizeof(Person));
        if (sscanf(input, "%s %d", person->name, &person->creditRating) == 2) {
            enqueue(q, person);
            if (person->creditRating > *maxRating) {
                *maxRating = person->creditRating;
            }
        } else {
            printf("Invalid input. Please enter name and rating.\n");
            free(person);
        }
    }
}


/**
 * @brief Displays the results of the credit rating analysis
 * @param q Pointer to the queue containing Person objects
 * @param maxRating The maximum credit rating encountered
 */
void displayResults(queue q, int maxRating) {
    int totalRating = 0;
    int count = 0;

    printf("\nName\tRating\tDistance\n");

    while (!isempty(q)) {
        Person* person = (Person*)dequeue(q);
        int distance = maxRating - person->creditRating;
        printf("%s\t%d\t%d\n", person->name, person->creditRating, distance);
        
        totalRating += person->creditRating;
        count++;
        free(person);
    }

    if (count > 0) {
        float average = (float)totalRating / count;
        printf("\nAverage: %.2f\n", average);
    } else {
        printf("\nNo data entered.\n");
    }
}


/**
 * @brief Main function to run the credit rating program
 * @return 0 on successful execution
 */
int main() {
    queue q = newqueue();
    int maxRating = 0;

    processInput(q, &maxRating);
    displayResults(q, maxRating);

    free(q);
    return 0;
}