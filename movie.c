#include "movie.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Array constante com os nomes dos géneros para mostrar ao utilizador
const char *GENRE_NAMES[] = {"ACTION",  "ADVENTURE", "ANIMATION", "BIOGRAPHY",
                             "COMEDY",  "CRIME",     "DRAMA",     "FAMILY",
                             "FANTASY", "HISTORY",   "HORROR",    "MUSIC",
                             "MUSICAL", "MYSTERY",   "ROMANCE",   "SCI-FI",
                             "SPORT",   "THRILLER",  "WAR",       "WESTERN"};

// Converte o número do género (enum) para o texto correspondente
const char *getGenreName(Genre g) {
  // Verifica se o género é válido antes de aceder ao array
  if (g >= 0 && g < GENRE_COUNT) {
    return GENRE_NAMES[g];
  }
  return "UNKNOWN";
}

// Inicializa a lista de filmes definindo o contador como 0
void initializeMovies(MovieArray *list) { list->count = 0; }

// Adiciona um novo filme à lista. Pede todos os dados ao utilizador
int addMovie(MovieArray *list) {
  // Verifica se ainda há espaço na lista
  if (list->count >= MAX_MOVIES) {
    printf("Erro: Capacidade maxima de filmes atingida.\n");
    return 0;
  }

  // Aponta para a próxima posição livre no array
  Movie *m = &list->movies[list->count];

  // Gera o ID automaticamente: se for o primeiro é 1, senão pega no último e soma 1
  m->code = (list->count == 0) ? 1 : list->movies[list->count - 1].code + 1;

  readString("Introduza o Titulo: ", m->title, MAX_STRING);

  // Inicializa todos os géneros como 0 (não selecionado)
  for (int i = 0; i < GENRE_COUNT; i++)
    m->genres[i] = 0;
    
  printf("Adicionar generos (introduza 0 para parar):\n");
  // Loop para adicionar múltiplos géneros
  while (1) {
    Genre g = selectGenre();
    m->genres[g] = 1; // Marca o género escolhido como 1 (selecionado)
    printf("Adicionar outro genero? (1: Sim, 0: Nao): ");
    int choice = readIntegerRange("", 0, 1);
    if (choice == 0)
      break;
  }

  readString("Introduza a Descricao: ", m->description, MAX_DESCRIPTION);
  readString("Introduza o Realizador: ", m->director, MAX_STRING);

  m->actorsCount = 0;
  printf("Adicionar atores (introduza nome vazio para parar):\n");
  // Loop para adicionar atores até ao máximo permitido
  while (m->actorsCount < MAX_ACTORS) {
    char actorName[MAX_STRING];
    printf("Ator %d: ", m->actorsCount + 1);
    readString("", actorName, MAX_STRING);
    // Se o utilizador der enter sem escrever nada, para de pedir atores
    if (strlen(actorName) == 0)
      break;
    strcpy(m->actors[m->actorsCount], actorName);
    m->actorsCount++;
  }

  // Lê os dados numéricos com validação de intervalo
  m->year = readIntegerRange("Introduza o Ano: ", 1888, 2100);
  m->duration = readIntegerRange("Introduza a Duracao (minutos): ", 1, 1000);
  m->rating = readFloatRange("Introduza a Classificacao (0-10): ", 0.0, 10.0);
  m->favorite =
      readIntegerRange("Introduza o numero de Favoritos: ", 0, 1000000000);
  m->revenue = readFloatRange("Introduza a Receita (milhoes): ", 0.0, 10000.0);

  // Incrementa o contador de filmes na lista
  list->count++;
  printf("Filme adicionado com sucesso com o Codigo: %d\n", m->code);
  return 1;
}

// Imprime o cabeçalho da tabela de filmes
void printTableHeader() {
  printf("%-5s %-30s %-20s %-10s %-10s\n", "Code", "Title", "Director", "Year",
         "Rating");
}

// Imprime uma linha com os dados de um filme, formatada para ficar alinhada com
// o cabeçalho
void printMovieRow(const Movie *m) {
  printf("%-5d %-30.30s %-20.20s %-10d %-10.1f\n", m->code, m->title,
         m->director, m->year, m->rating);
}

// Lista todos os filmes por ordem de código (ordem de inserção)
void listMoviesByCode(const MovieArray *list) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    printMovieRow(&list->movies[i]);
  }
}

// Função auxiliar para o qsort. Compara dois filmes pela classificação para ordenar do maior para o menor
int compareRatingDesc(const void *a, const void *b) {
  // Faz cast dos ponteiros genéricos (void*) para ponteiros de Movie
  const Movie *mA = (const Movie *)a;
  const Movie *mB = (const Movie *)b;
  
  // Retorna positivo se B for maior que A (para ordem decrescente)
  if (mB->rating > mA->rating)
    return 1;
  if (mB->rating < mA->rating)
    return -1;
  return 0;
}

// Cria uma cópia da lista para não estragar a original e ordena por classificação
void listMoviesByRating(const MovieArray *list) {
  // Aloca memória temporária para a cópia da lista
  MovieArray *temp = malloc(sizeof(MovieArray));
  if (temp == NULL) {
    printf("Erro ao alocar memoria.\n");
    return;
  }
  // Copia o conteúdo da lista original para a temporária
  *temp = *list;
  
  // Usa o qsort (Quick Sort) da biblioteca padrão para ordenar
  qsort(temp->movies, temp->count, sizeof(Movie), compareRatingDesc);
  
  printTableHeader();
  for (int i = 0; i < temp->count; i++) {
    printMovieRow(&temp->movies[i]);
  }
  
  // Liberta a memória alocada
  free(temp);
}

// Função auxiliar para o qsort. Compara os títulos para ordenar alfabeticamente
int compareTitleAsc(const void *a, const void *b) {
  const Movie *mA = (const Movie *)a;
  const Movie *mB = (const Movie *)b;
  // strcmp compara duas strings e retorna <0, 0 ou >0
  return strcmp(mA->title, mB->title);
}

// Cria uma cópia da lista e ordena por título
void listMoviesByTitle(const MovieArray *list) {
  MovieArray *temp = malloc(sizeof(MovieArray));
  if (temp == NULL) {
    printf("Erro ao alocar memoria.\n");
    return;
  }
  *temp = *list;
  qsort(temp->movies, temp->count, sizeof(Movie), compareTitleAsc);
  printTableHeader();
  for (int i = 0; i < temp->count; i++) {
    printMovieRow(&temp->movies[i]);
  }
  free(temp);
}

// Procura texto ignorando maiúsculas/minúsculas. É preciso fazer isto à mão porque o C padrão não tem esta função
int strCaseStr(const char *haystack, const char *needle) {
  if (!*needle)
    return 1; // Se a string de busca for vazia, encontra sempre
    
  // Percorre a string principal (haystack)
  for (const char *p = haystack; *p; p++) {
    // Se encontrar o primeiro caracter igual (ignorando case)
    if (tolower((unsigned char)*p) == tolower((unsigned char)*needle)) {
      const char *h, *n;
      // Verifica se o resto da palavra também bate certo
      for (h = p, n = needle; *h && *n; h++, n++) {
        if (tolower((unsigned char)*h) != tolower((unsigned char)*n))
          break;
      }
      // Se chegámos ao fim da string de busca (*n == 0), encontrámos!
      if (!*n)
        return 1;
    }
  }
  return 0; // Não encontrou
}

// Pesquisa filmes que tenham o texto no título (parcial)
void searchMoviesByTitle(const MovieArray *list, const char *search) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    if (strCaseStr(list->movies[i].title, search)) {
      printMovieRow(&list->movies[i]);
    }
  }
}

// Pesquisa filmes que tenham um determinado género
void searchMoviesByGenre(const MovieArray *list, Genre genre) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    // Verifica se o género está marcado como 1 (verdadeiro) neste filme
    if (list->movies[i].genres[genre]) {
      printMovieRow(&list->movies[i]);
    }
  }
}

void searchMoviesByDirector(const MovieArray *list, const char *director) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    if (strCaseStr(list->movies[i].director, director)) {
      printMovieRow(&list->movies[i]);
    }
  }
}

// Pesquisa filmes por ator
void searchMoviesByActor(const MovieArray *list, const char *actor) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    // Percorre todos os atores do filme
    for (int j = 0; j < list->movies[i].actorsCount; j++) {
      // Se encontrar o ator, mostra o filme e passa para o próximo filme (break)
      if (strCaseStr(list->movies[i].actors[j], actor)) {
        printMovieRow(&list->movies[i]);
        break;
      }
    }
  }
}

// Mostra todos os detalhes de um filme específico pelo código
void consultMovie(const MovieArray *list, int code) {
  for (int i = 0; i < list->count; i++) {
    if (list->movies[i].code == code) {
      Movie m = list->movies[i];
      printf("Codigo: %d\n", m.code);
      printf("Titulo: %s\n", m.title);
      printf("Realizador: %s\n", m.director);
      printf("Ano: %d\n", m.year);
      printf("Duracao: %d min\n", m.duration);
      printf("Classificacao: %.1f\n", m.rating);
      printf("Favoritos: %d\n", m.favorite);
      printf("Receita: %.2fM\n", m.revenue);
      printf("Descricao: %s\n", m.description);
      printf("Generos: ");
      for (int g = 0; g < GENRE_COUNT; g++) {
        if (m.genres[g])
          printf("%s ", getGenreName((Genre)g));
      }
      printf("\nAtores: ");
      for (int a = 0; a < m.actorsCount; a++) {
        printf("%s", m.actors[a]);
        if (a < m.actorsCount - 1)
          printf(", ");
      }
      printf("\n");
      return;
    }
  }
  printf("Filme com o codigo %d nao encontrado.\n", code);
}

#include <strings.h>

// Atualiza os dados de um filme existente
int updateMovie(MovieArray *list, int code) {
  int index = -1;
  for (int i = 0; i < list->count; i++) {
    if (list->movies[i].code == code) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Filme com o codigo %d nao encontrado.\n", code);
    return 0;
  }

  Movie *m = &list->movies[index];
  printf("A editar filme: %s\n", m->title);

  readString("Novo Titulo: ", m->title, MAX_STRING);

  for (int i = 0; i < GENRE_COUNT; i++) m->genres[i] = 0;
  printf("Novos generos (0 para parar):\n");
  while (1) {
    Genre g = selectGenre();
    m->genres[g] = 1;
    printf("Adicionar outro? (1: Sim, 0: Nao): ");
    if (readIntegerRange("", 0, 1) == 0) break;
  }

  m->year = readIntegerRange("Novo Ano: ", 1888, 2100);
  m->duration = readIntegerRange("Nova Duracao (min): ", 1, 1000);
  m->rating = readFloatRange("Nova Classificacao (0-10): ", 0.0, 10.0);
  m->favorite = readIntegerRange("Novos Favoritos: ", 0, 1000000000);
  m->revenue = readFloatRange("Nova Receita (milhoes): ", 0.0, 10000.0);

  printf("Filme atualizado com sucesso.\n");
  return 1;
}

// Remove um filme da lista
int deleteMovie(MovieArray *list, int code) {
  int index = -1;
  for (int i = 0; i < list->count; i++) {
    if (list->movies[i].code == code) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    printf("Filme com o codigo %d nao encontrado.\n", code);
    return 0;
  }

  for (int i = index; i < list->count - 1; i++) {
    list->movies[i] = list->movies[i + 1];
  }
  
  list->count--;
  printf("Filme removido com sucesso.\n");
  return 1;
}

// Apaga todos os filmes da memória
void clearMovies(MovieArray *list) {
  list->count = 0;
}

// Helper para ler campo CSV
char *getCSVField(char **linePtr) {
    char *start = *linePtr;
    if (*start == '\0' || *start == '\n' || *start == '\r') return NULL;

    char *end;
    if (*start == '"') {
        start++; 
        end = start;
        while (*end) {
            if (*end == '"') {
                if (*(end + 1) == '"') {
                    end++; 
                } else {
                    break; 
                }
            }
            end++;
        }
        *end = '\0'; 
        *linePtr = end + 1;
        if (**linePtr == ';') (*linePtr)++; 
    } else {
        end = strchr(start, ';');
        if (end) {
            *end = '\0';
            *linePtr = end + 1;
        } else {
            *linePtr = start + strlen(start);
            // Remove newline if present at the very end of the line
            char *nl = strchr(start, '\n');
            if(nl) *nl = '\0';
            nl = strchr(start, '\r');
            if(nl) *nl = '\0';
        }
    }
    return start;
}

// Helper para converter float com virgula
float parseFloatFromCSV(char *str) {
    if(!str) return 0.0;
    char temp[50];
    strncpy(temp, str, 49);
    for(int i=0; temp[i]; i++) {
        if(temp[i] == ',') temp[i] = '.';
    }
    return atof(temp);
}

int importMovies(MovieArray *list, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Erro ao abrir o ficheiro %s\n", filename);
        return -1;
    }

    char line[4096]; 
    int imported = 0;

    // Ignora o cabeçalho
    fgets(line, sizeof(line), f);

    while (fgets(line, sizeof(line), f) && list->count < MAX_MOVIES) {
        char *ptr = line;
        
        // Code
        char *token = getCSVField(&ptr);
        if(!token) continue;
        int code = atoi(token);
        
        // Verifica se o código já existe para não duplicar
        int exists = 0;
        for(int i=0; i<list->count; i++) {
            if(list->movies[i].code == code) {
                exists = 1;
                break;
            }
        }
        if(exists) continue;

        Movie *m = &list->movies[list->count];
        m->code = code;

        // Title
        token = getCSVField(&ptr);
        if(token) strncpy(m->title, token, MAX_STRING);

        // Genres
        token = getCSVField(&ptr);
        for(int i=0; i<GENRE_COUNT; i++) m->genres[i] = 0;
        if(token) {
            char *gPtr = token;
            char *gToken;
            while((gToken = strsep(&gPtr, ",")) != NULL) {
                while(*gToken == ' ') gToken++;
                for(int i=0; i<GENRE_COUNT; i++) {
                    if(strcasecmp(GENRE_NAMES[i], gToken) == 0) {
                        m->genres[i] = 1;
                    }
                }
            }
        }

        // Description
        token = getCSVField(&ptr);
        if(token) strncpy(m->description, token, MAX_DESCRIPTION);

        // Director
        token = getCSVField(&ptr);
        if(token) strncpy(m->director, token, MAX_STRING);

        // Actors
        token = getCSVField(&ptr);
        m->actorsCount = 0;
        if(token) {
            char *aPtr = token;
            char *aToken;
            while((aToken = strsep(&aPtr, ",")) != NULL && m->actorsCount < MAX_ACTORS) {
                while(*aToken == ' ') aToken++;
                strncpy(m->actors[m->actorsCount], aToken, MAX_STRING);
                m->actorsCount++;
            }
        }

        // Year
        token = getCSVField(&ptr);
        if(token) m->year = atoi(token);

        // Duration
        token = getCSVField(&ptr);
        if(token) m->duration = atoi(token);

        // Rating
        token = getCSVField(&ptr);
        if(token) m->rating = parseFloatFromCSV(token);

        // Favorite
        token = getCSVField(&ptr);
        if(token) m->favorite = atoi(token);

        // Revenue
        token = getCSVField(&ptr);
        if(token) m->revenue = parseFloatFromCSV(token);

        list->count++;
        imported++;
    }
    fclose(f);
    return imported;
}

int exportMovies(const MovieArray *list, const char *filename) {
    // Verifica se o ficheiro já existe
    FILE *fCheck = fopen(filename, "r");
    if (fCheck) {
        fclose(fCheck);
        printf("Erro: O ficheiro %s ja existe.\n", filename);
        return 0;
    }

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Erro ao criar o ficheiro %s\n", filename);
        return 0;
    }

    // Escreve o cabeçalho
    fprintf(f, "code;title;genres;description;director;actors;year;duration;rating;favorite ;revenue\n");

    for (int i = 0; i < list->count; i++) {
        Movie m = list->movies[i];
        fprintf(f, "%d;%s;", m.code, m.title);

        // Genres
        int first = 1;
        for(int g=0; g<GENRE_COUNT; g++) {
            if(m.genres[g]) {
                if(!first) fprintf(f, ", ");
                fprintf(f, "%s", getGenreName((Genre)g));
                first = 0;
            }
        }
        fprintf(f, ";");

        // Description (com aspas)
        fprintf(f, "\"%s\";", m.description);

        // Director
        fprintf(f, "%s;", m.director);

        // Actors
        first = 1;
        for(int a=0; a<m.actorsCount; a++) {
            if(!first) fprintf(f, ", ");
            fprintf(f, "%s", m.actors[a]);
            first = 0;
        }
        fprintf(f, ";");

        // Year, Duration
        fprintf(f, "%d;%d;", m.year, m.duration);

        // Rating (com virgula)
        char buffer[50];
        sprintf(buffer, "%.1f", m.rating);
        for(int k=0; buffer[k]; k++) if(buffer[k] == '.') buffer[k] = ',';
        fprintf(f, "%s;", buffer);

        // Favorite
        fprintf(f, "%d;", m.favorite);

        // Revenue (com virgula)
        sprintf(buffer, "%.2f", m.revenue);
        for(int k=0; buffer[k]; k++) if(buffer[k] == '.') buffer[k] = ',';
        fprintf(f, "%s\n", buffer);
    }

    fclose(f);
    return 1;
}
