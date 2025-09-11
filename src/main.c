/**
 * \file main.c
 * \author Isaiah Lateer
 *
 * Entry point for the project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 15 (letters) + 1 (\r) + 1 (\n) = 17
#define MAX_CHAR_COUNT 17

/**
 * Converts a letter to its point value.
 *
 * \param[in] letter Letter.
 * \return Point value.
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
 * Reads in a dictionary file and coverts each word into its point value.
 *
 * \return Exit code
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "[ERROR] Did not specify a dictionary file.\n");
    } else if (argc > 2) {
        fprintf(stderr, "[ERROR] Too many arguments were found.\n");
    }

    FILE* dictionary = fopen(argv[1], "r");
    if (!dictionary) {
        fprintf(stderr, "[ERROR] Failed to open dictionary file.\n");
        return EXIT_FAILURE;
    }

    int word_count = 0;
    char word[MAX_CHAR_COUNT];

    while (fgets(word, MAX_CHAR_COUNT, dictionary)) {
        ++word_count;

        const size_t position = strcspn(word, "\r\n");
        if (position) {
            word[position] = '\0';
        } else {
            fprintf(
                stderr, "[WARN] Failed to read word on line %d.\n", word_count);
            continue;
        }

        const size_t length = strlen(word);

        int points = 0;
        for (size_t i = 0; i < length; ++i) {
            points += letter_to_points(word[i]);
        }

        printf("%s (%d)\n", word, points);
    }

    fclose(dictionary);
    return EXIT_SUCCESS;
}
