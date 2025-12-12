#ifndef UTILS_H
#define UTILS_H

#include "movie.h"

// Funções utilitárias para leitura de dados e validação
void clearInputBuffer();
int readInteger(const char *prompt);
float readFloat(const char *prompt);
void readString(const char *prompt, char *buffer, int size);
Genre selectGenre();
int readIntegerRange(const char *prompt, int min, int max);
float readFloatRange(const char *prompt, float min, float max);

#endif
