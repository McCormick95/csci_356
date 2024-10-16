/**
 * @file war_pipes.c
 * @brief Creates two processes that can play the card 
 * game of war against each other for a given number of rounds
 *  
 * @note timing data was to test effeciency vs James Burke, 
 * mine was 3x faster
 *
 * @author Ryan McCormick
 * @email rlmccormi@coastal.edu
 * 
 * @date 10-16-2024
 * @version 2.0
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

/**
 * @brief Main function to create pipes and call play_war()
 * @param argc number of elements in argv[]
 * @param argv array of command line arguments  
 * @return 0 on successful execution
 */
void draw_card(int *card);
void play_war(int write_1p, int read_1c, int write_2p, int read_2c, int game_count);

int main(int argc, char *argv[]){
    srand(time(NULL));
    int game_count;
    // validates that argument is passed to program
    if(argc != 1){
        game_count = atoi(argv[1]);
    }
    // validates that game_count is more than 0, prints USAGE statement if not
    if(game_count <= 0){
        fprintf(stderr, "USAGE: ./war_pipes <int>\n");
        return 1;
    } 

    // struct timespec start, end;
    // double elapsed_time = 0.0;
    // // Start the timer
    // clock_gettime(CLOCK_MONOTONIC, &start);

    // initilize pipes and pids 
    int pipe_1p[2], pipe_1c[2], pipe_2p[2], pipe_2c[2];
    pid_t pid_1, pid_2;

    if (pipe(pipe_1p) == -1 || pipe(pipe_1c) == -1 || pipe(pipe_2p) == -1 || pipe(pipe_2c) == -1) {
        perror("pipe");
        exit(1);
    }
    // fork pid_1 and close unused pipes
    pid_1 = fork();
    if(pid_1 == 0){
        close(pipe_1p[1]); 
        close(pipe_1c[0]);
        exit(0);
    }
    // fork pid_2 and close unused pipes
    pid_2 = fork();
    if(pid_2 == 0){
        close(pipe_2p[1]); 
        close(pipe_2c[0]);
        exit(0);
    }

    printf("Child 1 PID: %d\n", (int)pid_1);
    printf("Child 2 PID: %d\n", (int)pid_2);

    printf("Beginning %d Rounds!\n", game_count);
    printf("-------------------------------------\n");

    // calls play_war and gives it the processes that will play
    play_war(pipe_1p[0], pipe_1c[1], pipe_2p[0], pipe_2c[1], game_count);
    
    // closes pipes that have been used
    close(pipe_1p[0]); 
    close(pipe_1c[1]);
    close(pipe_2p[0]); 
    close(pipe_2c[1]);

    // End the timer
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    // printf("time: %f \n", elapsed_time);

    return 0;
}

/**
 * @brief play_war() to allow two processes to play a game of war 
 * agianst one another for a given number of rounds
 * @param write_1p write end of pipe 1
 * @param read_1c read end of pipe 1
 * @param write_2p write end of pipe 2
 * @param read_2c read end of pipe 2
 * @param game_count number of rounds to play
 * @return void
 */
void play_war(int write_1p, int read_1c, int write_2p, int read_2c, int game_count){
    int card_1[2];
    int card_2[2];
    int win_c1 = 0;
    int win_c2 = 0;
    int round_count = 1;

    // arrays for face cards and suits
    char *face_cards[] = {"Jack", "Queen", "King", "Ace"};
    char *cards_suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    
    // loops for game_count
    for(int i=0; i < game_count; i++){
        printf("Round %d:\n", round_count);
        // process 1 plays the game
        draw_card(card_1);
        write(write_1p, card_1, sizeof(int) * 2);
        //process 2 plays the game
        draw_card(card_2);
        write(write_2p, card_2, sizeof(int) * 2); 

        read(read_1c, card_1, sizeof(int) * 2);
        read(read_2c, card_2, sizeof(int) * 2);
        // print card values
        if(card_1[0]<=10){
            printf("Child 1 draws: %d \n", card_1[0]);
        }
        else if(card_1[0]>10){
            printf("Child 1 draws: %s \n", face_cards[card_1[0]-11]); 
        }

        if(card_2[0]<=10){
            printf("Child 2 draws: %d \n", card_2[0]);
        }
        else if(card_2[0]>10){
            printf("Child 2 draws: %s \n", face_cards[card_2[0]-11]); 
        }
        // determine winner
        if(card_1[0] < card_2[0]){
            printf("Child 2 Wins!\n");
            win_c2++;
        }
        else if(card_1[0] > card_2[0]){
            printf("Child 1 Wins!\n");
            win_c1++;
        }
        else{
            printf("Checking suit…\n");
            // resolves ties based on suit
            if(card_1[0]<=10){
                printf("Child 1 draws: %d of %s \n", card_1[0], cards_suit[card_1[1]-1]);
            }
            else if(card_1[0]>10){
                printf("Child 1 draws: %s of %s \n", face_cards[card_1[0]-11], cards_suit[card_1[1]-1]);
            }

            if(card_2[0]<=10){
                printf("Child 2 draws: %d of %s \n", card_2[0], cards_suit[card_2[1]-1]);
            }
            else if(card_1[0]>10){
                printf("Child 2 draws: %s of %s \n", face_cards[card_2[0]-11], cards_suit[card_2[1]-1]); 
            }
            
            if(card_1[1] < card_2[1]){
                printf("Child 2 Wins!\n");
                win_c2++; 
            }
            else if(card_1[1] > card_2[1]){
                printf("Child 1 Wins!\n");
                win_c1++;
            }
            else if(card_1[1] == card_2[1]){
                printf("BOTH CARDS & SUITS MATCH, IT'S A TIE!\n");
            }
        }
        round_count++;

        printf("-------------------------------------\n");
    }

    printf("Child 1 won: %d rounds.\n", win_c1);
    printf("Child 2 won: %d rounds.\n", win_c2);
    // determines winner after all rounds are played
    if(win_c1 < win_c2){
        printf("Child 2 Wins!\n");
    }
    else if((win_c1 > win_c2)){
        printf("Child 1 Wins!\n");
    }
    else{
        printf("IT'S A TIE!\n");
    }
}

/**
 * @brief draw_card() provides a random card and suit when called
 * @param card pointer to a 2-dimentional array that holds two ints
 * one for card value and one for suit
 * @return void
 */
void draw_card(int *card){
    int rand_v, rand_s;

    rand_v = rand() % (14 - 2 + 1) + 2;
    rand_s = rand() % (4 - 1 + 1) + 1;

    card[0] = rand_v;
    card[1] = rand_s;
}