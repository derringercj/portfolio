#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//Function signautres
void encode(char code[], FILE *input);
void decode(char code[], FILE *input);
char *shiftLeft(int iterations, char word[]);
char *shiftRight(int iterations, char word[]);
char *ASCIIUp(int iterations, char word[]);
char *ASCIIDown(int iterations, char word[]);
char *binaryNormal(int iterations, char word[]);
char *binaryReverse(int iterations, char word[]);

int main(int argc, char *argv[]){
    //Arrays that command line arguments will be stored in
    char ed[10];
    char code[100];
    //Error mitigation
    if(argc != 4){
        printf("Invalid number of arguments, must be exactly 4\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if(input == 0){
        printf("Could not open file '%s'\n", argv[1]);
        return 1;
    }
    
    //pointers to the first value of the command line arguments
    char *action = *(argv + 2);
    char *tasks = *(argv + 3);
    
    //Assigning the command line arguments to their respective arrays, making them easier to manipulate
    for(int i = 0; i < 10; i++){
        ed[i] = *(action + i);
    }
    for(int i = 0; i < 100; i++){
        code[i] = *(tasks + i);
    }
    //Calling encode or decode based on the command line argument in the array
    if(strcmp(ed, "encode") == 0){
        encode(code, input);
    }
    else if(strcmp(ed, "decode") == 0){
        decode(code, input);
    }
    else{
        printf("Invalid option, must be 'encode' or 'decode'!\n");
    }
    return 0;
}

void encode(char code[], FILE *input){
    int length = strlen(code);
    int iterations = 0;
    char word[100];

    //While you have not reached the end of file, read in a word
    while(fscanf(input, "%s", word) == 1){
        //For the length of that word, check the task to be performed and call the corresponding function
        for(int i = 0; i < length; i++){
            if(code[i] == 'L' && isdigit(code[i + 1])){
                //Converting the number character next to the character to an integer
                iterations = code[i + 1] - '0';
                shiftRight(iterations, word);
                i++;
            }
            else if(code[i] == 'R' && isdigit(code[i + 1])){
                iterations = code[i + 1] - '0';
                shiftLeft(iterations, word);
                i++;
            }
            else if(code[i] == 'C' && isdigit(code[i + 1])){
                iterations = code[i + 1] - '0';    
                ASCIIDown(iterations, word);
                i++;
            }
            else if(code[i] == 'B' && isdigit(code[i + 1])){
                iterations = code[i + 1] -'0';
                binaryNormal(iterations, word);
                i++;
            }
            //If one of the four tasks is not represented in the code, error
            else if(code[i] != 'B' && code[i] != 'C' && code[i] != 'R' && code[i] != 'L'){
                printf("I cannot encrypt the message with task '%c'!\n", code[i]);
                exit(0);
            }
            //If a two digit integer is entered in the code, error
            else if(isdigit(code[i + 2]) && isdigit(code[i + 1])){
                printf("Please enter a valid number for the encryption task '%c'!\n", code[i]);
                exit(0);
            }
            //If a character is present where an integer should be, error
            else if(isalpha(code[i + 1])){
                printf("Please enter a valid number for the encryption task '%c'!\n", code[i]);
                exit(0);
            }
        }
        printf("%s\n", word);
    }
}

void decode(char code[], FILE *input){
    int length = strlen(code);
    int iterations = 0;
    char word[100];
    
    //While you have not reached end of file, read word
    while(fscanf(input, "%s", word) == 1){
        //For the length of the word, check what task to be performed and how many times, then call function
        for(int i = 0; i < length; i++){   
            if(code[i] == 'L' && isdigit(code[i + 1])){
                //Convert char number from code into integer to pass to function
                iterations = code[i + 1] - '0';
                shiftLeft(iterations, word);
                i++;
            }
            else if(code[i] == 'R' && isdigit(code[i + 1])){
                iterations = code[i + 1] - '0';
                shiftRight(iterations, word);
                i++;
            }
            else if(code[i] == 'C' && isdigit(code[i + 1])){
                iterations = code[i + 1] - '0';    
                ASCIIUp(iterations, word);
                i++;
            }
            else if(code[i] == 'B' && isdigit(code[i + 1])){
                iterations = code[i + 1] - '0';
                binaryReverse(iterations, word);
                i++;
            }
            //If the code presents a non-valid task, error
            else if(code[i] != 'B' && code[i] != 'C' && code[i] != 'R' && code[i] != 'L'){
                printf("I cannot encrypt the message with task '%c'!\n", code[i]);
                exit(0);
            }
            //If the code presents a non valid integer to go with a task, error
            else if(isdigit(code[i + 1]) && isdigit(code[i + 2])){
                printf("Please enter a valid number for the encryption task '%c'!\n", code[i]);
                exit(0);
            }
            //If the code presents a char instead of a number to go with a task, error
            else if(isalpha(code[i + 1])){
                printf("Please enter a valid number for the encryption task '%c'!\n", code[i]);
                exit(0);
            }
        }
        //Print word after all changes have been made to it
        printf("%s\n", word);
    }
}
/*Assign first part of array to tempVal, each character now becomes the one to its right, the last
character becomes the first character saved to tempval, repeat as many times as dictated by function call and 
return word*/
char *shiftLeft(int iterations, char word[]){
    char tempVal;
    
    while(iterations){
        int length = strlen(word);

        tempVal = word[0];

        for(int i = 0; i < length; i++){
            word[i] = word[i + 1];
        }
        word[length - 1] = tempVal;
        iterations--;
    }
    return word;
}
/*Assign last character of array to tempVal, each character in array becomes one to its left and first character of array
is assigned the original last character. Repeat for as many times as dictated by function call*/
char *shiftRight(int iterations, char word[]){
    char tempVal;

    int length = strlen(word);

    tempVal = word[length - 1];

    while(iterations){
       
        int length = strlen(word);

        tempVal = word[length - 1];

        for(int i = length - 1; i > 0; i--){
            word[i] = word[i - 1];
        }
        word[0] = tempVal;

        iterations--;
    }
    return word;
}
/*For as many times as function call dictates, for each character of the array, increase its value by 1 and 
if the character goes beyond valid values, it wraps down and goes back to the first valid character*/
char *ASCIIUp(int iterations, char word[]){
    while(iterations){
        int length = strlen(word);
        for(int i = 0; i < length; i++){
            word[i] = word[i] + 1;
            if(word[i] > 126){
                word[i] = 33;
            }
        }
        iterations--;
    }
    return word;
}
/*For as many times as function call dictates, for each character of the arrya, decrease its value by 1 and if the
character goes below valid values, it wraps down and goes back to the last valid character*/
char *ASCIIDown(int iterations, char word[]){
    while(iterations){
        int length = strlen(word);
        for(int i = 0; i < length; i++){
            word[i] = word[i] - 1;
            if(word[i] < 33){
                word[i] = 126;
            }
            
        }
        iterations--;
    }
    return word;
}
char *binaryNormal(int iterations, char word[]){
    //Declare Array
    int binary[4];
    int length = strlen(word);
    //Binary counter used to track where in the binary array we are with each loop iterations
    int binaryCounter = 0;
    int binaryLength = 0;
    /*Based on number given by function call, assign the binary equivalent of that number to a binary array
    and establish binaryLength as the length of that binary value*/
    switch(iterations){
        case 0:
            binary[0] = 0;
            binaryLength = 1;
            break;
        case 1:
            binary[0] = 1;
            binaryLength = 1;
            break;
        case 2:
            binary[0] = 1;
            binary[1] = 0;
            binaryLength = 2;
            break;
        case 3:
            binary[0] = 1;
            binary[1] = 1;
            binaryLength = 2;
            break;
        case 4:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binaryLength = 3;
            break;
        case 5:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 1;
            binaryLength = 3;
            break;
        case 6:
            binary[0] = 1;
            binary[1] = 1;
            binary[2] = 0;
            binaryLength = 3;
            break;
        case 7:
            binary[0] = 1;
            binary[1] = 1;
            binary[2] = 1;
            binaryLength = 3;
            break;
        case 8:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binary[3] = 0;
            binaryLength = 4;
            break;
        case 9:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binary[3] = 1;
            binaryLength = 4;
            break;
    }
/*For length of word, if binary value at given index is 1 and the array character is alpha numeric,
increase ascii value by 1*/
    for(int i = 0; i < length; i++){
        if(binary[binaryCounter] == 1 && isalnum(word[i]) != 0){
            word[i] = word[i] + 1;
            //If value goes beyond lowercase Z, wrap to lowercase A
            if(word[i] > 122){
                word[i] = 97;
            }
            //If value goes beyond uppercase Z, wrap to uppercase A
            else if(word[i] > 90 && word[i] < 97){
                word[i] = 65;
            }
            //If value goes beyond 9, wrap to 0
            else if(word[i] > 57 && word[i] < 65){
                word[i] = 48;
            }
            //Increase binary counter and if binary counter is as long as the length of the binary value, reset binary counter
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
        /*If binary value is 0 and array character is alphanumeric, decrease ascii value by 1, wrapping values
        as done above*/
        else if(binary[binaryCounter] == 0  && isalnum(word[i]) != 0){
            word[i] = word[i] - 1;
            if(word[i] < 65 && word[i] > 58){
                word[i] = 90;
            }
            else if(word[i] < 97 && word[i] > 90){
                word[i] = 122;
            }
            else if(word[i] < 48){
                word[i] = 57;
            }
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
        /*If binary value is 1 or 0, but character is not alphanumeric, do nothing except increase binary counter to keep 
        track of place in array*/
        else{
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
    }
    return word;
}
/*Does the same as function above, but binary value of one corresponds with decrease of ascii value
and binary value of zero corresponds with increase of ascii value, with same wrapping as previous*/
char *binaryReverse(int iterations, char word[]){
    int binary[4];
    int length = strlen(word);
    int binaryCounter = 0;
    int binaryLength = 0;

    switch(iterations){
        case 0:
            binary[0] = 0;
            binaryLength = 1;
            break;
        case 1:
            binary[0] = 1;
            binaryLength = 1;
            break;
        case 2:
            binary[0] = 1;
            binary[1] = 0;
            binaryLength = 2;
            break;
        case 3:
            binary[0] = 1;
            binary[1] = 1;
            binaryLength = 2;
            break;
        case 4:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binaryLength = 3;
            break;
        case 5:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 1;
            binaryLength = 3;
            break;
        case 6:
            binary[0] = 1;
            binary[1] = 1;
            binary[2] = 0;
            binaryLength = 3;
            break;
        case 7:
            binary[0] = 1;
            binary[1] = 1;
            binary[2] = 1;
            binaryLength = 3;
            break;
        case 8:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binary[3] = 0;
            binaryLength = 4;
            break;
        case 9:
            binary[0] = 1;
            binary[1] = 0;
            binary[2] = 0;
            binary[3] = 1;
            binaryLength = 4;
            break;
    }

    for(int i = 0; i < length; i++){
        if(binary[binaryCounter] == 1 && isalnum(word[i]) != 0){
            word[i] = word[i] - 1;
            if(word[i] < 65 && word[i] > 58){
                word[i] = 90;
            }
            else if(word[i] < 97 && word[i] > 90){
                word[i] = 122;
            }
            else if(word[i] < 48){
                word[i] = 57;
            }
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
        else if(binary[binaryCounter] == 0  && isalnum(word[i]) != 0){
            word[i] = word[i] + 1;
            if(word[i] > 122){
                word[i] = 97;
            }
            else if(word[i] > 90 && word[i] < 97){
                word[i] = 65;
            }
            else if(word[i] > 57 && word[i] < 65){
                word[i] = 48;
            }
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
        else{
            binaryCounter++;
            if(binaryCounter == binaryLength){
                binaryCounter = 0;
            }
        }
    }
    return word;
}
