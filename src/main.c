/**
 * \file main.c
 * \author Isaiah Lateer
 * 
 * Scrabble word finder.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char* dictionary[178691];
extern size_t word_count;

/**
 * Gets the number of points a letter is worth.
 * 
 * \param[in] letter Letter to convert.
 * \return Point value.
 */
unsigned letter_to_points(char letter) {
    static unsigned points[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1,
        3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
    
    if (letter >= 'A' && letter <= 'Z') {
        return points[letter - 'A'];
    } else if (letter >= 'a' && letter <= 'z') {
        return points[letter - 'a'];
    } else if (letter < 26) {
        return points[(int) letter];
    }

    return 0;
}

/**
 * Entry point for the program. Takes in letters as input and checks against
 * words in the dictionary to determine which words can be made using the given
 * letters.
 * 
 * \return Exit code.
 */
int main() {
    // Get letters. ////////////////////////////////////////////////////////////

    printf("Enter your letters (? for blanks): ");

    char input[16] = { 0 };

    char* result = fgets(input, sizeof(input) - 1, stdin);
    if (!result) {
        fprintf(stderr, "[ERROR] Failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = 0;

    unsigned letters[27] = { 0 };

    for (size_t i = 0; i < sizeof(input); ++i) {
        const char letter = input[i];

        if (letter == 0) {
            continue;
        } else if (letter >= 'A' && letter <= 'Z') {
            ++letters[letter - 'A'];
        } else if (letter >= 'a' && letter <= 'z') {
            ++letters[letter - 'a'];
        } else if (letter == '?') {
            ++letters[26];
        } else {
            fprintf(stderr, "[WARN] Skipping invalid letter: \'%c\'.\n",
                letter);
            continue;
        }
    }

    // Get what the word must start with. //////////////////////////////////////

    printf("Needs to start with (Optional): ");

    char starts_with[16] = { 0 };

    result = fgets(starts_with, sizeof(starts_with), stdin);
    if (!result) {
        fprintf(stderr, "[ERROR] Failed to read input.\n");
        return EXIT_FAILURE;
    }

    starts_with[strcspn(starts_with, "\r\n")] = 0;

    for (size_t i = 0; i < sizeof(starts_with); ++i) {
        if (starts_with[i] >= 'a' && starts_with[i] <= 'z') {
            starts_with[i] = toupper(starts_with[i]);
        }
    }

    // Get what the word must end with. ////////////////////////////////////////

    printf("Needs to end with (Optional): ");

    char ends_with[16] = { 0 };

    result = fgets(ends_with, sizeof(ends_with), stdin);
    if (!result) {
        fprintf(stderr, "[ERROR] Failed to read input.\n");
        return EXIT_FAILURE;
    }

    ends_with[strcspn(ends_with, "\r\n")] = 0;

    for (size_t i = 0; i < sizeof(ends_with); ++i) {
        if (ends_with[i] >= 'a' && ends_with[i] <= 'z') {
            ends_with[i] = toupper(ends_with[i]);
        }
    }

    // Get substring the word must contain. ////////////////////////////////////

    printf("Needs to contain substring (Optional): ");

    char contains[16] = { 0 };

    result = fgets(contains, sizeof(contains), stdin);
    if (!result) {
        fprintf(stderr, "[ERROR] Failed to read input.\n");
        return EXIT_FAILURE;
    }

    contains[strcspn(contains, "\r\n")] = 0;

    for (size_t i = 0; i < sizeof(contains); ++i) {
        if (contains[i] >= 'a' && contains[i] <= 'z') {
            contains[i] = toupper(contains[i]);
        }
    }

    // Search dictionary. //////////////////////////////////////////////////////

    for (size_t i = 0; i < word_count; ++i) {
        const char* word = dictionary[i];
        const size_t char_count = strlen(word);

        if (strncmp(word, starts_with, strlen(starts_with))) {
            continue;
        }

        if (char_count > strlen(ends_with) &&
            strcmp(word + char_count - strlen(ends_with), ends_with)) {
            continue;
        }

        if (!strstr(word, contains)) {
            continue;
        }

        unsigned points = 0;
        unsigned frequency[26] = { 0 };
        bool invalid_word = false;

        for (size_t j = 0; j < char_count; ++j) {
            const char letter = word[j];

            points += letter_to_points(letter);

            if (letter >= 'A' && letter <= 'Z') {
                ++frequency[letter - 'A'];
            } else if (letter >= 'a' && letter <= 'z') {
                ++frequency[letter - 'a'];
            } else {
                fprintf(stderr, "[WARN] Skipping invalid word: %s.\n", word);
                invalid_word = true;
                break;
            }
        }

        if (invalid_word) {
            continue;
        }

        bool can_make_word = true;
        unsigned blanks = letters[26];

        for (int j = 0; j < 26; ++j) {
            if (letters[j] < frequency[j]) {
                if (blanks >= frequency[j] - letters[j]) {
                    points -= letter_to_points(j);
                    blanks -= frequency[j] - letters[j];
                } else {
                    can_make_word = false;
                    break;
                }
            }
        }

        if (can_make_word) {
            printf("%s (%d)\n", word, points);
        }
    }

    return EXIT_SUCCESS;
}
