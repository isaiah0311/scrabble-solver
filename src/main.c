/**
 * \file main.c
 * \author Isaiah Lateer
 * 
 * Scrabble word finder.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: Used for testing only.
const char* dictionary[16] = {
    "ONE",
    "TWO",
    "THREE",
    "FOUR",
    "FIVE",
    "SIX",
    "SEVEN",
    "EIGHT",
    "NINE",
    "TEN"
};

/**
 * Entry point for the program. Takes in letters as input and checks against
 * words in the dictionary to determine which words can be made using the given
 * letters.
 * 
 * \return Exit code.
 */
int main() {
    printf("Enter your letters: ");

    char input[16] = { 0 };

    int result = scanf("%15s", input);
    if (result < 1) {
        fprintf(stderr, "[ERROR] Unable to read letters.\n");
        return EXIT_FAILURE;
    }

    char letters[26] = { 0 };

    for (int i = 0; i < 15; ++i) {
        const char letter = input[i];

        if (letter == 0) {
            continue;
        } else if (letter >= 'A' && letter <= 'Z') {
            ++letters[letter - 'A'];
        } else if (letter >= 'a' && letter <= 'z') {
            ++letters[letter - 'a'];
        } else {
            fprintf(stderr, "[ERROR] \'%c\' is not a valid letter.\n", letter);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < 10; ++i) {
        const char* word = dictionary[i];
        const size_t char_count = strlen(word);

        char frequency[26] = { 0 };
        bool invalid_word = false;

        for (size_t j = 0; j < char_count; ++j) {
            if (word[j] >= 'A' && word[j] <= 'Z') {
                ++frequency[word[j] - 'A'];
            } else if (word[j] >= 'a' && word[j] <= 'z') {
                ++frequency[word[j] - 'a'];
            } else {
                fprintf(stderr, "[ERROR] Skipping invalid word: %s.\n", word);
                invalid_word = true;
                break;
            }
        }

        if (invalid_word) {
            continue;
        }

        bool can_make_word = true;

        for (int j = 0; j < 26; ++j) {
            if (letters[j] < frequency[j]) {
                can_make_word = false;
                break;
            }
        }

        if (can_make_word) {
            printf("%s\n", word);
        }
    }

    return EXIT_SUCCESS;
}
