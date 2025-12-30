#ifndef MOVIE_H
#define MOVIE_H

// Definições de constantes para tamanhos máximos
#define MAX_MOVIES 2000      // Máximo de filmes que o programa aguenta
#define MAX_STRING 100       // Tamanho máximo para strings curtas (títulos, nomes)
#define MAX_DESCRIPTION 500  // Tamanho máximo para descrições
#define MAX_ACTORS 10        // Máximo de atores por filme
#define GENRE_COUNT 20       // Número total de géneros disponíveis

// Enumeração para os géneros de filmes. Facilita o uso de nomes em vez de números.
typedef enum {
  ACTION,
  ADVENTURE,
  ANIMATION,
  BIOGRAPHY,
  COMEDY,
  CRIME,
  DRAMA,
  FAMILY,
  FANTASY,
  HISTORY,
  HORROR,
  MUSIC,
  MUSICAL,
  MYSTERY,
  ROMANCE,
  SCI_FI,
  SPORT,
  THRILLER,
  WAR,
  WESTERN
} Genre;

// Estrutura que representa um filme com todos os seus dados
typedef struct {
  int code;                          // Código único do filme
  char title[MAX_STRING];            // Título do filme
  int genres[GENRE_COUNT];           // Array de 0s e 1s para indicar os géneros (1 = tem o género)
  char description[MAX_DESCRIPTION]; // Sinopse do filme
  char director[MAX_STRING];         // Nome do realizador
  char actors[MAX_ACTORS][MAX_STRING]; // Lista de nomes dos atores
  int actorsCount;                   // Quantos atores foram inseridos
  int year;                          // Ano de lançamento
  int duration;                      // Duração em minutos
  float rating;                      // Classificação (0.0 a 10.0)
  int favorite;                      // Número de vezes que foi marcado como favorito (ou likes)
  float revenue;                     // Receita em milhões
} Movie;

// Estrutura para guardar a lista de filmes e quantos filmes existem atualmente
typedef struct {
  Movie movies[MAX_MOVIES]; // Array estático com todos os filmes
  int count;                // Número atual de filmes na lista
} MovieArray;

// Declarações das funções que podem ser usadas noutros ficheiros
void initializeMovies(MovieArray *list);
int addMovie(MovieArray *list);
void listMoviesByCode(const MovieArray *list);
void listMoviesByRating(const MovieArray *list);
void listMoviesByTitle(const MovieArray *list);
void searchMoviesByTitle(const MovieArray *list, const char *search);
void searchMoviesByGenre(const MovieArray *list, Genre genre);
void searchMoviesByDirector(const MovieArray *list, const char *director);
void searchMoviesByActor(const MovieArray *list, const char *actor);
void consultMovie(const MovieArray *list, int code);
int updateMovie(MovieArray *list, int code);
int deleteMovie(MovieArray *list, int code);
void clearMovies(MovieArray *list);
int importMovies(MovieArray *list, const char *filename);
int exportMovies(const MovieArray *list, const char *filename);
const char *getGenreName(Genre g);

#endif
