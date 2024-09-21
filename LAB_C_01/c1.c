#include <stdio.h>
#include <stdlib.h>

//function declaration
void combine(int digit1, int digit2, int digit3, int *num, int *reversed_num);

//main
int main(){
    //declare variables
    int digit1, digit2, digit3, num, reversed_num;

    //print to ask for user input
    printf("Enter 3 digits separated by spaces: \n");
    //read uesr input
    scanf("%d %d %d", &digit1, &digit2, &digit3);

    //check that input is valid, throw error if not valid
    if(digit1 >= 10 || digit2 >= 10 || digit3 >= 10 || digit1 < 0 || digit2 < 0 || digit2 < 0 ){
        printf("ERROR: ONE OF THE NUMBERS WAS NOT A SINGLE DIGIT");
        exit(0);
    }else{
        //call combine
        combine(digit1, digit2, digit3, &num, &reversed_num);
    }
    //print results to user
    printf("After calling combine: \n");
    printf("number= %d \n", num);
    printf("resersed number= %d \n", reversed_num);
}

//combine
void combine(int digit1, int digit2, int digit3, int *num, int *reversed_num){
    //put numbers in std order
    *num = (digit1 * 100 + digit2 * 10 + digit3 * 1);
    //put numbers in reverse order
    *reversed_num = (digit3 * 100 + digit2 * 10 + digit1 * 1);
}