#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LENGTH 256

typedef struct {
    char character;
    int value;
} CharValue;

void encode();
void decode();
void toLowerCase(char* str);
void printCharValues(CharValue* charValues, int size);
char *read_string();
void write_string(char *encoded_string);

int main(){

    CharValue charValues[] = {
        {'A',10}, {'a',10}, {'B',11}, {'b',11}, {'C',12}, {'c',12}, {'D',13}, {'d',13}, {'E',14}, {'e',14},
        {'F',15}, {'f',15}, {'G',16}, {'g',16}, {'H',17}, {'h',17}, {'I',18}, {'i',18}, {'J',19}, {'j',19}, 
        {'K',20}, {'k',20}, {'L',21}, {'l',21}, {'M',22}, {'m',22}, {'N',23}, {'n',23}, {'O',24}, {'o',24},
        {'P',25}, {'p',25}, {'Q',26}, {'q',26}, {'R',27}, {'r',27}, {'S',28}, {'s',28}, {'T',29}, {'t',29}, 
        {'U',30}, {'u',30}, {'V',31}, {'v',31}, {'W',32}, {'w',32}, {'X',33}, {'x',33}, {'Y',34}, {'y',34}, 
        {'Z',35}, {'z',35}, {' ',36}, {'.',37}, {'?',38}, {'!',39}
    };

    // Calculate the size of the array
    int arraySize = sizeof(charValues) / sizeof(charValues[0]);
    //printCharValues(charValues, arraySize);

    char user_selection;
    char user_selection_lower;
    
    printf("Welcome to the Encoder / Decoder program! \n");
    printf(" Please select d for decode or e for encode: e \n");
    scanf(" %c", &user_selection);

    printf("User selection is: %c \n", user_selection); 

    user_selection_lower = tolower(user_selection);

    char selection_str[2];
    selection_str[0] = user_selection_lower;
    selection_str[1] = '\0';

    int choice_e = strcmp(selection_str, "e");
    int choice_d = strcmp(selection_str, "d");

    

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

void encode(CharValue* charValues, int size){

    char *file_string_buffer = read_string();
    
    //toLowerCase(buffer);
    //printf("test sent after lower: %s \n", buffer);
    //int str_length = buffer.Length;

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

void decode(CharValue* charValues, int size){

}

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void printCharValues(CharValue* charValues, int size) {
    for (int i = 0; i < size; i++) {
        printf("Character: %c, Value: %d\n", charValues[i].character, charValues[i].value);
    }
}

char *read_string(){
    FILE *file;
    static char file_string_buffer[MAX_LENGTH];

    file = fopen("unencoded.txt", "r");
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

    printf("text from file: %s \n", file_string_buffer);

    return file_string_buffer;
} 

void write_string(char *encoded_string){
    FILE *file_out = fopen("encoded_out.txt", "w");

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