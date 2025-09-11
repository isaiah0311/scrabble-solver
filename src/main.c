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
 * Entry point of the project.
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

    char word[MAX_CHAR_COUNT];
    while (fgets(word, MAX_CHAR_COUNT, dictionary)) {
        printf("%s", word);
    }

    fclose(dictionary);
    return EXIT_SUCCESS;
}
