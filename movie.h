#ifndef MOVIE_H
#define MOVIE_H

#define MAX_MOVIES 2000
#define MAX_STRING 100
#define MAX_DESCRIPTION 500
#define MAX_ACTORS 10
#define GENRE_COUNT 20

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

typedef struct {
  int code;
  char title[MAX_STRING];
  int genres[GENRE_COUNT];
  char description[MAX_DESCRIPTION];
  char director[MAX_STRING];
  char actors[MAX_ACTORS][MAX_STRING];
  int actorsCount;
  int year;
  int duration;
  float rating;
  int favorite;
  float revenue;
} Movie;

typedef struct {
  Movie movies[MAX_MOVIES];
  int count;
} MovieArray;

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
const char *getGenreName(Genre g);

#endif
