#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "words.h"
#include "hangman-io.h"

// display_board(word, guessed) displays the current state of the word being guessed
//   with guessed letters revealed and others hidden with asterisks ('*').
// effects: produces output
// time: O(n), where n is the length of the string 'word'
void display_board(const char *word, const int *guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == ' ') {
            printf(" ");
        } else if (guessed[i]) {
            printf("%c", word[i]);
        } else {
            printf("*");
        }
    }
    printf("\n");
}

// all_guessed(word, guessed) checks if all letters (excluding spaces) in the word have been guessed
// time: O(n), where n is the length of the string 'word'
int all_guessed(const char *word, const int *guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] != ' ' && !guessed[i]) {
            return 0;
        }
    }
    return 1;
}

// is_letter(c) checks if a given character is a letter (uppercase or lowercase)
// time: O(1)
int is_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// to_upper(c) converts a lowercase letter to its corresponding uppercase letter; leaves other characters unchanged
// time: O(1)
char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

int main(void) {
    int game_number;
    char play_again_response = 'Y';
    
    while (play_again_response == 'Y') {
        // Prompt for and validate game number
        printf(enter_game_number, max_words);
        scanf("%d", &game_number);
        while (game_number < 1 || game_number > max_words) {
            printf(invalid_game_number);
            printf(enter_game_number, max_words);
            scanf("%d", &game_number);
        }
        
        // Get the word
        const char *word = get_word(game_number);
        int word_length = strlen(word);
        int guessed[word_length];
        for (int i = 0; i < word_length; i++) {
            guessed[i] = 0;
        }
        
        int strikes = 0;
        char guess;
        
        // Start the game
        while (strikes < max_strikes && !all_guessed(word, guessed)) {
            print_hangman(strikes);
            printf("%s", letter_prompt);
            display_board(word, guessed);
            scanf(" %c", &guess);
            guess = to_upper(guess);
            
            if (!is_letter(guess)) {
                printf(not_a_letter, guess);
                continue;
            }
            
            int already_guessed = 0;
            for (int i = 0; i < word_length; i++) {
                if (guess == guessed[i]) {
                    already_guessed = 1;
                }
            }
            
            if (already_guessed) {
                printf(already_guessed_letter, guess);
                continue;
            }
            
            int correct_guess = 0;
            for (int i = 0; i < word_length; i++) {
                if (to_upper(word[i]) == guess) {
                    guessed[i] = 1;
                    correct_guess = 1;
                }
            }
            
            if (!correct_guess) {
                printf(not_in_word, guess);
                strikes++;
                if (strikes < max_strikes) {
                    printf(not_last_guess, max_strikes - strikes);
                }
            }
        }
        
        // End of the game
        print_hangman(strikes);
        if (all_guessed(word, guessed)) {
            printf(congratulations, word);
        } else {
            printf(game_over, word);
        }
        
        // Play again prompt
        printf("%s", play_again);
        scanf(" %c", &play_again_response);
        while (play_again_response != 'Y' && play_again_response != 'N' && play_again_response != 'n' && play_again_response != 'y') {
            printf(invalid_play_again_response);
            printf("%s", play_again);
            scanf(" %c", &play_again_response);
        } if (play_again_response == 'n' || play_again_response == 'N') {
            break;
        }
    }
    return 0;
}