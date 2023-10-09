#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Define your functions here. */

void PrintMenu () {
   printf("MENU\n");
   printf("c - Number of non-whitespace characters\n");
   printf("w - Number of words\n");
   printf("f - Fix capitalization\n");
   printf("r - Replace all !'s\n");
   printf("s - Shorten spaces\n");
   printf("q - Quit\n\n");
   }

// updates the string by replacing all sequences of 2 or more spaces with a single space
void ShortenSpace(char* userText) {
    int i, j;
    int length = strlen(userText);

    for (i = 0, j = 0; i < length; ++i) {
        // If the current character is a space and the next character is also a space,
        // skip the extra spaces by not copying them.
        if (userText[i] == ' ' && userText[i + 1] == ' ') {
            continue;
        }

        // Otherwise, copy the character to the updated string.
        userText[j++] = userText[i];
    }

    // Null-terminate the updated string.
    userText[j] = '\0';
}


// updates the string by replacing each '!' character in the string with a '.' character.
void ReplaceExclamation(char* userText) {
    int i;

    for (i = 0; i <strlen(userText); ++i) {
        if (userText[i] == '!') {
            userText[i] = '.';
        }
    }

}


// updates the string by replacing lowercase letters at the beginning of sentences with uppercase letters.
void FixCapitalization(char* userText) {
    int length = strlen(userText);
    bool capitalizeNext = true;

    for (int i = 0; i < length; ++i) {
        if (userText[i] == '.' && (userText[i + 1] == ' ' || userText[i + 1] == '\n')) {
            // Skip consecutive spaces after a period
            while (userText[i + 1] == ' ') {
                i++;
            }
            capitalizeNext = true;
        } else if (capitalizeNext && islower(userText[i])) {
            userText[i] = toupper(userText[i]);
            capitalizeNext = false;
        } else {
            capitalizeNext = false;
        }
    }
}


// returns the number of words in the string
int GetNumOfWords(const char* userText) {
    int i;
    int numWords = 0;

    for (i = 0; i < strlen(userText); ++i) {
        if (userText[i] == '\n' || userText[i] == ' ') {
            if (userText[i+1] == ' ') {
                numWords = numWords;
            }
            else {
                numWords = numWords + 1;
            }
            
        }
    }
    
    return numWords;
}

//returns the number of characters in the string, excluding all whitespace
int GetNumOfNonWSCharacters(const char* userText) {
    int nonWhiteChars = 0;
    int i;
    for (i = 0; i < strlen(userText); ++i) {
        if (userText[i] != '\n') {
            if (userText[i] != ' ') {
                nonWhiteChars = nonWhiteChars + 1;
            }
        }
    }
    return nonWhiteChars;
}


void ExecuteMenu(char userChoice, char* userText) {
//calling the appropriate functions
if (userChoice == 'c') {
    int nonWhiteChars = GetNumOfNonWSCharacters(userText);
    printf("Number of non-whitespace characters: %d\n\n" ,nonWhiteChars);
}

if (userChoice == 'w') {
    int numWords = GetNumOfWords(userText);
    printf("Number of words: %d\n\n", numWords);
}
if (userChoice == 'f') {
    FixCapitalization(userText);
    printf("Edited text: %s\n", userText);
}
if (userChoice == 'r') {
    ReplaceExclamation(userText);
    printf("Edited text: %s\n", userText);

}
if (userChoice == 's') {
    ShortenSpace(userText);
    printf("Edited text: %s\n", userText);
}

}




int main(void) {

   /* Type your code here. */
   char userChoice = 'z'; // z is a placeholder so while loop runs correctly
   char userInput[999];
   bool isQuit = false;
   printf("Enter a sample text:\n\n");
   fgets(userInput, 999, stdin);
   
   printf("You entered: %s\n", userInput);
   
//loop until user wants to quit
while (isQuit == false) {
   PrintMenu();

    // If an invalid character is entered, continue to prompt for a valid choice
    while (userChoice != 'c' && userChoice != 'w' && userChoice != 'f' && userChoice != 'r' && userChoice != 's' && userChoice != 'q') {
    // promt user for menu choice
        printf("Choose an option:");
    scanf(" %c", &userChoice);
    printf("\n"); // newline after user enters choice
    }
    //check if user wants to quit
    if (userChoice == 'q') {
    isQuit = true;
    break;
    }
    // When a valid option is entered, execute the option by calling ExecuteMenu().
    ExecuteMenu(userChoice, userInput);

    //reset userChoice back to 'z' to ensure that the menu is printed again, and the user is prompted for a new choice in the next iteration of the loop.
    userChoice = 'z';
}


   return 0;
}