/**
 * \file main.c
 * \author Isaiah Lateer
 *
 * Entry point for the project.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_COUNT 17 // 15 letters + \r + \n = 17

/**
 * Reads input and converts it into letter counts.
 *
 * \param[out] letters Amount of each letter
 * \return Whether input could be read
 */
bool get_letters(int letters[27]) {
    char input[MAX_CHAR_COUNT] = { 0 };
    printf("Enter your letters: ");
    char* raw_input = fgets(input, sizeof(input) - 1, stdin);
    if (!raw_input) {
        fprintf(stderr, "[ERROR] Failed to read input.\n");
        return false;
    }

    input[strcspn(input, "\r\n")] = 0;

    for (size_t i = 0; i < sizeof(input); ++i) {
        const char letter = input[i];

        if (letter >= 'A' && letter <= 'Z') {
            ++letters[letter - 'A'];
        } else if (letter >= 'a' && letter <= 'z') {
            ++letters[letter - 'a'];
        } else if (letter == '?') {
            ++letters[26];
        } else if (letter != '\0') {
            fprintf(stderr, "[WARN] Unrecognized character: %c\n", letter);
        }
    }

    return true;
}

/**
 * Checks if a word can be made with the given letters.
 *
 * \param[in] letters Amount of each letter
 * \param[in] word Word
 * \return Whether the word can be made
 */
bool can_make_word(int letters[27], const char* word) {
    bool result = true;
    int frequency[26] = { 0 };
    const size_t char_count = strlen(word);

    for (size_t i = 0; i < char_count; ++i) {
        char letter = word[i];
        if (letter >= 'A' && letter <= 'Z') {
            ++frequency[letter - 'A'];
        } else if (letter >= 'a' && letter <= 'z') {
            ++frequency[letter - 'a'];
        } else {
            fprintf(stderr, "[WARN] Unrecognized character: %c\n", letter);
        }
    }

    int blanks = letters[26];

    for (int j = 0; j < 26; ++j) {
        if (letters[j] < frequency[j]) {
            if (blanks >= frequency[j] - letters[j]) {
                blanks -= frequency[j] - letters[j];
            } else {
                result = false;
                break;
            }
        }
    }

    return result;
}

/**
 * Converts a letter to its point value.
 *
 * \param[in] letter Letter
 * \return Point value
 */
int letter_to_points(char letter) {
    static int points[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10,
        1, 1, 1, 1, 4, 4, 8, 4, 10 };

    int value = 0;
    if (letter >= 'A' && letter <= 'Z') {
        value = points[letter - 'A'];
    } else if (letter >= 'a' && letter <= 'z') {
        value = points[letter - 'a'];
    } else {
        fprintf(stderr, "[WARN] Unrecognized character: %c\n", letter);
    }

    return value;
}

/**
 * Converts a word to its point value.
 *
 * \param[in] word Word
 * \return Point value
 */
int word_to_points(const char* word) {
    int value = 0;
    const size_t char_count = strlen(word);

    for (size_t i = 0; i < char_count; ++i) {
        value += letter_to_points(word[i]);
    }

    return value;
}

/**
 * Gets input from the user, then checks it against each word in the dictionary
 * file to see if it can be made using the given letters. Prints every word that
 * can be made, along with the total point value of that word.
 *
 * \param[in] argc Number of arguments
 * \param[in] argv Array of arguments
 * \return Exit code
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "[ERROR] Did not specify a dictionary file.\n");
    } else if (argc > 2) {
        fprintf(stderr, "[ERROR] Too many arguments were found.\n");
    }

    int letters[27] = { 0 };
    bool result = get_letters(letters);
    if (!result) {
        return EXIT_FAILURE;
    }

    FILE* dictionary = fopen(argv[1], "r");
    if (!dictionary) {
        fprintf(stderr, "[ERROR] Failed to open dictionary file.\n");
        return EXIT_FAILURE;
    }

    int word_count = 0;
    char word[MAX_CHAR_COUNT];

    while (fgets(word, sizeof(word), dictionary)) {
        const size_t position = strcspn(word, "\r\n");
        if (position) {
            word[position] = '\0';
        } else {
            fprintf(
                stderr, "[WARN] Failed to read word on line %d.\n", word_count);
            continue;
        }

        result = can_make_word(letters, word);
        if (result) {
            printf("%s (%d)\n", word, word_to_points(word));
        }
    }

    fclose(dictionary);
    return EXIT_SUCCESS;
}
