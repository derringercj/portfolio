#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

//Function signatures
void jerseyPrompt(int i);
void printRoster(int jerseyNums[], int ratingNums[]);
char menu();
void updateRating(int jerseyNums[], int ratingNums[]);
void updatePlayer(int jerseyNums[], int ratingNums[]);

const int NUM_PLAYERS = 5;

int main() {
   
   //Variable declarations
    int playerNums[NUM_PLAYERS];
    int playerRatings[NUM_PLAYERS];
    char menuChoice;

    //For loop to get players numbers and ratings
    for(int i = 0; i < NUM_PLAYERS; i++){
        jerseyPrompt(i);
        scanf("%d", &playerNums[i]);
        while(1){
            for(int j = 0; j < NUM_PLAYERS; j++){
                if(i == j){
                    continue;
                }
                if(playerNums[i] == playerNums[j]){
                    printf("Invalid jersey number. Enter player %d's jersey number:\n", i + 1);
                    scanf("%d", &playerNums[i]);
                }
            }
            if(playerNums[i] < 0 || playerNums[i] > 99){
                printf("Invalid jersey number. Enter player %d's jersey number:\n", i + 1);
                scanf("%d", &playerNums[i]);
            }
            else{
                printf("Enter player %d's rating:\n", i + 1);
                scanf("%d", &playerRatings[i]);
                while(1){
                    if(playerRatings[i] < 1 || playerRatings[i] > 10){
                        printf("Invalid player rating. Enter player %d's rating:\n", i + 1);
                        scanf("%d", &playerRatings[i]);
                    }
                    else{
                        break;
                    }
                }
                break;
            }
        }
    }
    //Function to print roster
    printRoster(playerNums, playerRatings);

    //Initialization of menu with switch statement
    while(1){
        menuChoice = menu();
        //Switch statement that controls menu
        switch(menuChoice){
            case 'u':
                updateRating(playerNums, playerRatings);
                break;
            case 'r':
                updatePlayer(playerNums, playerRatings);
                break;
            case 'o':
                printRoster(playerNums, playerRatings);
                break;
            case 'q':
                return 0;
            default:
                printf("\nInvalid option\n");
        }
    }

    return 0;
}
//Function to print roster
void printRoster(int jerseyNums[], int ratingNums[]){
    printf("\n");
    printf("ROSTER\n");
    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("Player %d -- Jersey Number: %d, Rating: %d\n", i + 1, jerseyNums[i], ratingNums[i]);
    }
    //printf("\n");

}
//Function to ask user for jersey number
void jerseyPrompt(int i){
    printf("Enter player %d's jersey number:\n", i + 1);
}
//Function to print menu
char menu(){
    char choice;
    printf("\nMENU\nu - Update player rating\n");
    printf("r - Replace player\no - Output roster\n");
    printf("q - quit\n\nChoose an option:\n");
    scanf(" %c", &choice);
    return choice;
}
void updateRating(int jerseyNums[], int ratingNums[]){
    int tempJerseyNumber = 0;
    bool jerseyFound = false;
    int playerNumber = 0;

    printf("\nEnter jersey number for rating update:\n");
    scanf("%d", &tempJerseyNumber);

    while(1){
        for(int i = 0; i < NUM_PLAYERS; i++){
            if(tempJerseyNumber == jerseyNums[i]){
                jerseyFound = true;
                playerNumber = i;
            }
        }
        if(jerseyFound == true){
            printf("Found jersey number. Enter new rating for player:\n");
            scanf("%d", &ratingNums[playerNumber]);
            while(1){
                if(ratingNums[playerNumber] < 1 || ratingNums[playerNumber] > 10){
                    printf("Invalid player rating. Enter valid rating:\n");
                    scanf("%d", &ratingNums[playerNumber]);
                }
                else{
                    break;
                }
                }
            break;
        }
        else{
            printf("Invalid jersey number. Enter valid jersey number:\n");
            scanf("%d", &tempJerseyNumber);
        }
    }
}
void updatePlayer(int jerseyNums[], int ratingNums[]){
    int tempJerseyNumber = 0;
    bool jerseyFound = false;
    int playerNumber = 0;
    
    printf("\nEnter jersey number to replace:\n");
    scanf("%d", &tempJerseyNumber);

    while(1){
        for(int i = 0; i < NUM_PLAYERS; i++){
            if(tempJerseyNumber == jerseyNums[i]){
                jerseyFound = true;
                playerNumber = i;
            }
        }
        if(jerseyFound == true){
            printf("Found player. Enter new jersey number:\n");
            scanf("%d", &jerseyNums[playerNumber]);
            while(1){
                if(jerseyNums[playerNumber] < 0 || jerseyNums[playerNumber] > 99){
                    printf("Invalid jersey number. Enter valid jersey number:\n");
                    scanf("%d", &jerseyNums[playerNumber]);
                }
                else{
                    printf("Enter player rating:\n");
                    scanf("%d", &ratingNums[playerNumber]);
                    while(1){
                        if(ratingNums[playerNumber] > 10 || ratingNums[playerNumber] < 1){
                            printf("Invalid player rating. Enter valid rating:\n");
                            scanf("%d", &ratingNums[playerNumber]);
                        }
                        else{
                            break;
                        }
                    }
                    break;
                }
            }
        break;
        }
        else{
            printf("Invalid jersey number. Enter valid jersey number:\n");
            scanf("%d", &tempJerseyNumber);
        }
    }
}