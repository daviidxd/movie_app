#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInteger(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter an integer: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

float readFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        printf("Invalid input. Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

int readIntegerRange(const char *prompt, int min, int max) {
    int value;
    do {
        value = readInteger(prompt);
        if (value < min || value > max) {
            printf("Value must be between %d and %d.\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

float readFloatRange(const char *prompt, float min, float max) {
    float value;
    do {
        value = readFloat(prompt);
        if (value < min || value > max) {
            printf("Value must be between %.1f and %.1f.\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

Genre selectGenre() {
    for (int i = 0; i < GENRE_COUNT; i++) {
        printf("%d. %s\n", i + 1, getGenreName((Genre)i));
    }
    int choice = readIntegerRange("Enter genre number: ", 1, GENRE_COUNT);
    return (Genre)(choice - 1);
}
