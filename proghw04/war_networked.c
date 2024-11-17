/**
 * @file war_networked.c
 * @brief Creates two processes that can play the card 
 * game of war against each other for a given number of rounds
 *  
 *
 * @author Ryan McCormick
 * @email rlmccormi@coastal.edu
 * 
 * @date 11-17-2024
 * @version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/un.h>
#include <sys/socket.h>

/**
* @brief Struct for card with value and suit
*/
typedef struct {
    int value;  
    int suit;  
} Card;

/**
* @brief Struct for players
*/
typedef struct {
    int player_id;
    int socket_pair[2];  
    int wins;
} ThreadData;

void* player_thread(void* arg);
Card draw_card();
const char* get_card_name(int value);
const char* get_suit_name(int suit);

/**
* @brief main for the program - takes user input and starts game
* @param argc - count for argv[]  
* @param argv[] - arguments array for program
* @return 0
*/
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_rounds>\n", argv[0]);
        return 1;
    }

    int rounds = atoi(argv[1]);
    if (rounds < 1) {
        printf("Number of rounds must be positive\n");
        return 1;
    }

    srand(time(NULL));

    // initilizes threads 
    pthread_t threads[2];
    ThreadData thread_data[2];

    for (int i = 0; i < 2; i++) {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, thread_data[i].socket_pair) == -1) {
            perror("socketpair");
            exit(1);
        }
        thread_data[i].player_id = i + 1;
        thread_data[i].wins = 0;
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, player_thread, &thread_data[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
        printf("Child %d TID: %lu\n", i + 1, threads[i]);
    }

    // starts game
    printf("Beginning %d Rounds...\n", rounds);
    printf("Fight!\n");
    printf("---------------------------\n");

    int current_rounds = rounds;
    int sudden_death = 0;

    do {
        for (int round = 1; round <= current_rounds; round++) {
            if (sudden_death) {
                printf("Sudden Death Round:\n");
            } else {
                printf("Round %d:\n", round);
            }

            Card cards[2];
            char signal = 1;

            for (int i = 0; i < 2; i++) {
                write(thread_data[i].socket_pair[0], &signal, 1);
                read(thread_data[i].socket_pair[0], &cards[i], sizeof(Card));
                printf("Child %d draws %s\n", i + 1, get_card_name(cards[i].value));
            }

            int winner;
            if (cards[0].value != cards[1].value) {
                winner = (cards[0].value > cards[1].value) ? 0 : 1;
            } else {
                printf("Checking suit...\n");
                printf("Child 1 draws %s %s\n", get_card_name(cards[0].value), 
                       get_suit_name(cards[0].suit));
                printf("Child 2 draws %s %s\n", get_card_name(cards[1].value), 
                       get_suit_name(cards[1].suit));
                winner = (cards[0].suit > cards[1].suit) ? 0 : 1;
            }

            thread_data[winner].wins++;
            printf("Child %d Wins!\n", winner + 1);
            printf("---------------------------\n");
        }

        if (!sudden_death && thread_data[0].wins == thread_data[1].wins) {
            printf("Tie! Going to sudden death!\n");
            printf("---------------------------\n");
            sudden_death = 1;
            current_rounds = 1;
            continue;
        }
        break;

    } while (1);
    // ends game
    char quit_signal = 0;
    for (int i = 0; i < 2; i++) {
        write(thread_data[i].socket_pair[0], &quit_signal, 1);
        close(thread_data[i].socket_pair[0]);
        close(thread_data[i].socket_pair[1]);
        pthread_join(threads[i], NULL);
    }

    // returns results
    printf("Results:\n");
    printf("Child 1: %d\n", thread_data[0].wins);
    printf("Child 2: %d\n", thread_data[1].wins);
    printf("Child %d Wins!\n", (thread_data[0].wins > thread_data[1].wins) ? 1 : 2);

    return 0;
}

/**
* @brief player_thread()  
* @param argv[] - arguments array passed fom main
* @return NULL
*/
void* player_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    char signal;

    while (1) {
        read(data->socket_pair[1], &signal, 1);
        
        if (signal == 0) { 
            break;
        }

        Card card = draw_card();
        write(data->socket_pair[1], &card, sizeof(Card));
    }

    return NULL;
}

/**
* @brief draws a card when called using a random number
* @return card
*/
Card draw_card() {
    Card card;
    card.value = (rand() % 13) + 2;  
    card.suit = rand() % 4;          
    return card;
}

/**
* @brief get_card_name() - returns the value of a card as a string when given a value
* @param value - integer value for a card from a random number generator
* @return names - string for the card value
*/
const char* get_card_name(int value) {
    static const char *names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                                "Jack", "Queen", "King", "Ace"};
    return names[value - 2];
}

/**
* @brief get_suit_name() - returns the suit of a card as a string when given a value
* @param suit - integer value for a card from a random number generator
* @return suit - string for the card suite
*/
const char* get_suit_name(int suit) {
    static const char *suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    return suits[suit];
}