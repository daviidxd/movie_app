#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

// Limpa o lixo que fica no buffer (tipo o 'enter') depois de ler números com o scanf
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lê um número inteiro do utilizador, garantindo que é válido
int readInteger(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Entrada invalida. Por favor introduza um inteiro: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Lê um número decimal (float) do utilizador
float readFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        printf("Entrada invalida. Por favor introduza um numero: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Lê um inteiro dentro de um intervalo específico (min e max)
int readIntegerRange(const char *prompt, int min, int max) {
    int value;
    do {
        value = readInteger(prompt);
        if (value < min || value > max) {
            printf("O valor deve estar entre %d e %d.\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

float readFloatRange(const char *prompt, float min, float max) {
    float value;
    do {
        value = readFloat(prompt);
        if (value < min || value > max) {
            printf("O valor deve estar entre %.1f e %.1f.\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

// Lê uma string (texto) do utilizador de forma segura
void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        // Remove o 'enter' que o fgets apanha no fim da frase, senão a string fica com uma linha nova
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Mostra a lista de géneros e pede ao utilizador para escolher um
Genre selectGenre() {
    for (int i = 0; i < GENRE_COUNT; i++) {
        printf("%d. %s\n", i + 1, getGenreName((Genre)i));
    }
    int choice = readIntegerRange("Introduza o numero do genero: ", 1, GENRE_COUNT);
    return (Genre)(choice - 1);
}
