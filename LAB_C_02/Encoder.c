// ################################## //
// ASSIGNMENT: LAB_C_02               //
// AUTHOR:     Ryan McCormick         //
// USERNAME:   rlmccormi              //
// EMAIL:      rlmccormi@coastal.edu  //
// VERSION:    1.0                    //
// DATE:       09/23/2024             //
// ################################## //

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LENGTH 256
#define OUTPUT_FILE "encoded_out.txt"
#define INPUT_FILE "unencoded.txt"

// define struc for character-value relationship 
typedef struct {
    char character;
    int value;
} CharValue;

void encode();
void decode();
void toLowerCase(char* str);
//void printCharValues(CharValue* charValues, int size);
char *read_string();
void write_string(char *encoded_string);

int main(){
    char user_selection;
    char user_selection_lower;

    //struct for characters-values
    CharValue charValues[] = {
        {'a',10}, {'b',11}, {'c',12}, {'d',13}, {'e',14},
        {'f',15}, {'g',16}, {'h',17}, {'i',18}, {'j',19}, 
        {'k',20}, {'l',21}, {'m',22}, {'n',23}, {'o',24},
        {'p',25}, {'q',26}, {'r',27}, {'s',28}, {'t',29}, 
        {'u',30}, {'v',31}, {'w',32}, {'x',33}, {'y',34}, 
        {'z',35}, {' ',36}, {'.',37}, {'?',38}, {'!',39}
    };

    int arraySize = sizeof(charValues) / sizeof(charValues[0]);

    //print statments to command line for user
    printf("Welcome to the Encoder / Decoder program! \n");
    printf(" Please select d for decode or e for encode: e \n");
    scanf(" %c", &user_selection);

    //printf("User selection is: %c \n", user_selection); 

    user_selection_lower = tolower(user_selection);

    char selection_str[2];
    selection_str[0] = user_selection_lower;
    selection_str[1] = '\0';

    int choice_e = strcmp(selection_str, "e");
    int choice_d = strcmp(selection_str, "d");

    // process user input and throw error if necessary
    if(choice_e == 0){
        encode(charValues, arraySize);
    }
    else if(choice_d == 0){
        decode(charValues, arraySize);
    }else{
        printf("ERROR: %s IS NOT ACCEPTED, PLEASE ENTER 'e' FOR ENCODE AND 'd' FOR DECODE \n", selection_str);
        exit(0);
    }

    return 0;
}

// function to encode string
void encode(CharValue* charValues, int size){
    char *file_string_buffer = read_string(INPUT_FILE);
    toLowerCase(file_string_buffer);

    char encoded_string[MAX_LENGTH];
    char encode_temp[10];
    int encode_value;
    encoded_string[0] = '\0';

    for(int i = 0; file_string_buffer[i] != '\0'; i++){
        for (int j=0; j < size; j++){
            if(charValues[j].character == file_string_buffer[i]){
                encode_value = charValues[j].value;
                sprintf(encode_temp, "%d", encode_value);
                strcat(encoded_string, encode_temp);
            }
        }
    }
    write_string(encoded_string);    
}

// function to decode string
void decode(CharValue* charValues, int size){
    char decoded_string[MAX_LENGTH];
    decoded_string[0] = '\0';
    int decoded_temp;

    char* encoded_string = read_string(OUTPUT_FILE);
    int string_length = strlen(encoded_string);
    printf("STRING READ IN: %s\n", encoded_string);

    if(string_length % 2 != 0){
        printf("ERROR: THE ENCODED STRING IS NOT EVEN");
        exit(0);
    }

    for(int i = 0; encoded_string[i] != '\0'; i += 2){
        char encode_pair[3];
        encode_pair[0] = encoded_string[i];
        encode_pair[1] = encoded_string[i + 1];
        encode_pair[2] = '\0';
        decoded_temp = atoi(encode_pair);

        for (int j=0; j < size; j++){
            if(charValues[j].value == decoded_temp){
                char temp_char[2];
                temp_char[0] = charValues[j].character;
                temp_char[1] = '\0';
                strcat(decoded_string, temp_char);
            }
        }
    }
    printf("DECODED STRING: %s \n", decoded_string);
}

// function to convert string to lower case
void toLowerCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// function sto read string from file
char *read_string(char *file_name){
    FILE *file;
    static char file_string_buffer[MAX_LENGTH];

    file = fopen(file_name, "r");
    if(file == NULL){
        perror("ERROR WHILE OPENING FILE");
        exit(0);
    }
    
    if(fgets(file_string_buffer, MAX_LENGTH, file) == NULL) {
        perror("ERROR WHILE READING FILE");
        fclose(file);
        exit(0);
    }

    fclose(file);

    printf("STRING FROM FILE: %s \n", file_string_buffer);

    return file_string_buffer;
} 

// function to print string to file
void write_string(char *encoded_string){
    FILE *file_out = fopen(OUTPUT_FILE, "w");

    if(file_out == NULL){
        perror("ERROR: WHILE OPENING FILE");
        exit(0);
    }

    if(fputs(encoded_string, file_out) == EOF){
        perror("ERROR: WHILE OPENING FILE");
        fclose(file_out);
        exit(0);
    }

    printf("STRING WRITTEN TO FILE: %s\n", encoded_string);

    fclose(file_out);
}