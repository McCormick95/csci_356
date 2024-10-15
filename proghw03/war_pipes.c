#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

void draw_card(int *card);

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

    // int cards_f[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
    // int cards_s[4] = {1,2,3,4};
    int card_1[2];
    int card_2[2];

    int pipe_1[2], pipe_2[2];
    pid_t pid;

    if (pipe(pipe_1) == -1 || pipe(pipe_2) == -1) {
        perror("pipe");
        exit(1);
    }
    
    // pipe_1[0] ----> WRITE
    // pipe_1[1] ----> READ

    // pipe_2[0] ----> WRITE
    // pipe_2[1] ----> READ
    for(int i=0; i < game_count; i++){
        int pipe1_v = 0;
        int pipe1_s = 0;
        int pipe2_v = 0;
        int pipe2_s = 0;

        // write data from pipe_1
        draw_card(card_1);
        write(pipe_1[1], card_1, sizeof(int) * 2);

        // write data from pipe_2
        draw_card(card_2);
        write(pipe_2[1], card_2, sizeof(int) * 2);

        // read data from pipe_1
        read(pipe_1[0], card_1, sizeof(int) * 2);
        pipe1_v = card_1[0];
        pipe1_s = card_1[1];
    
        // read data from pipe_2
        read(pipe_2[0], card_2, sizeof(int) * 2);
        pipe2_v = card_2[0];
        pipe2_s = card_2[1];
        
        // compare 
        printf("PIPE_1 - card:  %d, suite: %d \n", pipe1_v, pipe1_s);
        printf("PIPE_2 - card:  %d, suite: %d \n", pipe2_v, pipe2_s);
    }

    close(pipe_1[0]);
    close(pipe_1[1]);
    close(pipe_2[0]);
    close(pipe_2[1]);
    
    return 0;
}


void draw_card(int *card){
    int rand_v, rand_s;

    rand_v = rand() % (14 - 2 + 1) + 2;
    rand_s = rand() % (4 - 1 + 1) + 1;

    card[0] = rand_v;
    card[1] = rand_s;
}



