#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>


void draw_card(int *card);
void play_war(int write_1p, int read_1c, int write_2p, int read_2c, int game_count);

int main(int argc, char *argv[]){
    srand(time(NULL));

    int game_count;
    
    if(argc != 1){
        game_count = atoi(argv[1]);
    }

    if(game_count <= 0){
        fprintf(stderr, "USAGE: ./war_pipes <int>\n");
        return 1;
    } 

    int card[2];
    int pipe_1p[2], pipe_1c[2], pipe_2p[2], pipe_2c[2];
    pid_t pid_1, pid_2;

    if (pipe(pipe_1p) == -1 || pipe(pipe_1c) == -1 || pipe(pipe_2p) == -1 || pipe(pipe_2c) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_1 = fork();
    if(pid_1 == 0){
        close(pipe_1p[1]); 
        close(pipe_1c[0]);
        exit(0);
    }

    pid_2 = fork();
    if(pid_2 == 0){
        close(pipe_2p[1]); 
        close(pipe_2c[0]);
        exit(0);
    }

    printf("Child 1 PID: %d\n", (int)pid_1);
    printf("Child 2 PID: %d\n", (int)pid_2);

    printf("Beginning %d Rounds!\n", game_count);
    printf("-----------------------\n");

    play_war(pipe_1p[0], pipe_1c[1], pipe_2p[0], pipe_2c[1], game_count);
    
    close(pipe_1p[0]); 
    close(pipe_1c[1]);
    close(pipe_2p[0]); 
    close(pipe_2c[1]);
    
    return 0;
}

void play_war(int write_1p, int read_1c, int write_2p, int read_2c, int game_count){
    int card_1[2];
    int card_2[2];
    int win_c1 = 0;
    int win_c2 = 0;
    int round_count = 1;

    char *face_cards[] = {"Jack", "Queen", "King", "Ace"};
    char *cards_suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    
    for(int i=0; i < game_count; i++){
        printf("Round %d:\n", round_count);
        draw_card(card_1);
        write(write_1p, card_1, sizeof(int) * 2);

        draw_card(card_2);
        write(write_2p, card_2, sizeof(int) * 2); 

        read(read_1c, card_1, sizeof(int) * 2);
        read(read_2c, card_2, sizeof(int) * 2);

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
            if(card_1[0]<=10){
                printf("Child 1 draws: %d %s \n", card_1[0], cards_suit[card_1[1]-1]);
                printf("TESTING: SUIT_NUM: %d \n", card_1[1]);
            }
            else if(card_1[0]>10){
                printf("Child 1 draws: %s %s \n", face_cards[card_1[0]-11], cards_suit[card_1[1]-1]);
                printf("TESTING: SUIT_NUM: %d \n", card_1[1]); 
            }

            if(card_2[0]<=10){
                printf("Child 2 draws: %d %s \n", card_2[0], cards_suit[card_2[1]-1]);
                printf("TESTING: SUIT_NUM: %d \n", card_1[1]);
            }
            else if(card_1[0]>10){
                printf("Child 2 draws: %s %s \n", face_cards[card_2[0]-11], cards_suit[card_2[1]-1]);
                printf("TESTING: SUIT_NUM: %d \n", card_2[1]);  
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

        printf("-----------------------\n");
    }

    printf("Child 1 won: %d rounds.\n", win_c1);
    printf("Child 2 won: %d rounds.\n", win_c2);

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

void draw_card(int *card){
    int rand_v, rand_s;

    rand_v = rand() % (14 - 2 + 1) + 2;
    rand_s = rand() % (4 - 1 + 1) + 1;

    card[0] = rand_v;
    card[1] = rand_s;
}