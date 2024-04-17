#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern char words[][6];     // 2D array from wordlist.c to get the string
extern int length;          // Extern keyword is used to access data type from wordlist.c

// implementation of tolower function
char tolower_custom(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

// implementation of toupper function
char toupper_custom(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

// Function to print output in yellow color
void check_yel()
{
    printf("\033[1;33m");
}

// Function to print output in green color
void check_grn()
{
    printf("\033[1;32m");
}

// Function to reset output color
void reset()
{
    printf("\033[0m");
}

// Function to check correctness and position of letters
int c_and_pos(char word[], char user_word[])
{
    char temp[10];
    int correct[5] = {-1, -1, -1, -1, -1};  // Array to store indices of correctly guessed letters
    int posnot[5] = {-1, -1, -1, -1, -1};   // Array to store indices of letters present but not in the correct position
    int t1 = 0;  // Counter for correct array
    int t2 = 0;  // Counter for posnot array

    // Loop to check for correct letters and their positions
    for (int i = 0; i < 5; i++)
    {
        if (word[i] == user_word[i])
        {
            correct[t1] = i;  // Store index of correctly guessed letter
            t1++;
        }
    }

    // Loop to check for letters that are present but not in the correct position
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int isCorrect = 0;

            // Check if the letter is already identified as correct
            for (int k = 0; k < 5; k++)
            {
                if (j == correct[k])
                {
                    isCorrect = 1;
                    break;
                }
            }

            // If the letter is not already identified as correct and matches with a letter in the word
            if (!isCorrect)
            {
                if (word[j] == user_word[i])
                {
                    posnot[t2] = i;  // Store index of letter present but not in the correct position
                    t2++;
                }
            }
        }
    }

    strcpy(temp, user_word);  // Copy user_word to temp for comparison

    // Loop to print the letters with correct, incorrect, or positionally incorrect colors
    for (int i = 0; i < 5; i++)
    {
        int isCorrect = 0;

        // Check if the letter is correctly guessed
        for (int j = 0; j < 5; j++)
        {
            if (i == correct[j])
            {
                isCorrect = 1;
                break;
            }
        }

        int isPosNot = 0;

        // Check if the letter is present but not in the correct position
        for (int j = 0; j < 5; j++)
        {
            if (i == posnot[j])
            {
                isPosNot = 1;
                break;
            }
        }

        if (isCorrect)
        {
            reset();
            check_grn();
            printf("%c", toupper_custom(user_word[i]));  // Print correctly guessed letter in green color
            reset();
        }
        else if (isPosNot)
        {
            reset();
            check_yel();
            printf("%c", toupper_custom(user_word[i]));  // Print letter present but not in the correct position in yellow color
            reset();
        }
        else
            printf("%c", toupper_custom(user_word[i]));  // Print other letters in default color
    }

    // Check if the word is correctly guessed
    if (strcmp(word, temp) == 0)
        return 1;  // Return 1 if word is correctly guessed
    else
        return 0;  // Return 0 if word is not correctly guessed
}

int main()
{
    srand(time(0));  // Seed the random number generator with current time
    int found = 0;
    int tries = 6;
    char word[6];
    char user_word[10];
    strcpy(word, words[rand() % length]);  // Select a random word from the wordlist

    // Print game instructions
    printf("\n\t\tVOCABULIZE!\n");
    printf("\n\t\tInstructions\n");
    printf("\t\t_____________________\n");
    printf("\t\tLetters will be GREEN in color if you guessed the letter in the correct position.\n");
    printf("\t\tLetters will be YELLOW in color if the letter is present in the word but not in the correct position.\n");
    printf("\t\tYou have 6 tries to guess the word!\n");

    printf("\n");

    // Loop to allow the user to make guesses
    for (int a = 6; a > 0; a--)
    {
        reset();
        printf("\n\t\tYou have %d tries left!\n", a);
        printf("\t\tEnter a word to guess (5 letters): ");
        scanf("%s", user_word);

        if (strlen(user_word) != 5)
        {
            printf("\n\t\tWord entered is not a 5-letter word.\n");
            a++;
            continue;  // Skip the rest of the loop and start the next iteration
        }

        // Convert user_word to lowercase
        for (int b = 0; b < 6; b++)
            user_word[b] = tolower_custom(user_word[b]);

        found = c_and_pos(word, user_word);  // Check correctness and position of letters
        if (found == 1)
        {
            printf("\n\t\tYou found the word!\n");
            return 0;  // End the program
        }
    }

    // Convert word to uppercase
    for (int b = 0; b < 6; b++)
        word[b] = toupper_custom(word[b]);

    printf("\n\t\tYou didn't guess the word! The word was - %s", word);
    return 0;
}
