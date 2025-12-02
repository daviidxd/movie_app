#include "movie.h"
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *GENRE_NAMES[] = {"ACTION",  "ADVENTURE", "ANIMATION", "BIOGRAPHY",
                             "COMEDY",  "CRIME",     "DRAMA",     "FAMILY",
                             "FANTASY", "HISTORY",   "HORROR",    "MUSIC",
                             "MUSICAL", "MYSTERY",   "ROMANCE",   "SCI-FI",
                             "SPORT",   "THRILLER",  "WAR",       "WESTERN"};

const char *getGenreName(Genre g) {
  if (g >= 0 && g < GENRE_COUNT) {
    return GENRE_NAMES[g];
  }
  return "UNKNOWN";
}

void initializeMovies(MovieArray *list) { list->count = 0; }

int addMovie(MovieArray *list) {
  if (list->count >= MAX_MOVIES) {
    printf("Error: Maximum movie capacity reached.\n");
    return 0;
  }

  Movie *m = &list->movies[list->count];

  m->code = (list->count == 0) ? 1 : list->movies[list->count - 1].code + 1;

  readString("Enter Title: ", m->title, MAX_STRING);

  for (int i = 0; i < GENRE_COUNT; i++)
    m->genres[i] = 0;
  printf("Add genres (enter 0 to stop):\n");
  while (1) {
    Genre g = selectGenre();
    m->genres[g] = 1;
    printf("Add another genre? (1: Yes, 0: No): ");
    int choice = readIntegerRange("", 0, 1);
    if (choice == 0)
      break;
  }

  readString("Enter Description: ", m->description, MAX_DESCRIPTION);
  readString("Enter Director: ", m->director, MAX_STRING);

  m->actorsCount = 0;
  printf("Add actors (enter empty name to stop):\n");
  while (m->actorsCount < MAX_ACTORS) {
    char actorName[MAX_STRING];
    printf("Actor %d: ", m->actorsCount + 1);
    readString("", actorName, MAX_STRING);
    if (strlen(actorName) == 0)
      break;
    strcpy(m->actors[m->actorsCount], actorName);
    m->actorsCount++;
  }

  m->year = readIntegerRange("Enter Year: ", 1888, 2100);
  m->duration = readIntegerRange("Enter Duration (minutes): ", 1, 1000);
  m->rating = readFloatRange("Enter Rating (0-10): ", 0.0, 10.0);
  m->favorite = readIntegerRange("Enter Favorites count: ", 0, 1000000000);
  m->revenue = readFloatRange("Enter Revenue (millions): ", 0.0, 10000.0);

  list->count++;
  printf("Movie added successfully with Code: %d\n", m->code);
  return 1;
}

void printTableHeader() {
  printf("%-5s %-30s %-20s %-10s %-10s\n", "Code", "Title", "Director", "Year",
         "Rating");
}

void printMovieRow(const Movie *m) {
  printf("%-5d %-30.30s %-20.20s %-10d %-10.1f\n", m->code, m->title,
         m->director, m->year, m->rating);
}

void listMoviesByCode(const MovieArray *list) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    printMovieRow(&list->movies[i]);
  }
}

int compareRatingDesc(const void *a, const void *b) {
  const Movie *mA = (const Movie *)a;
  const Movie *mB = (const Movie *)b;
  if (mB->rating > mA->rating)
    return 1;
  if (mB->rating < mA->rating)
    return -1;
  return 0;
}

void listMoviesByRating(const MovieArray *list) {
  MovieArray temp = *list;
  qsort(temp.movies, temp.count, sizeof(Movie), compareRatingDesc);
  printTableHeader();
  for (int i = 0; i < temp.count; i++) {
    printMovieRow(&temp.movies[i]);
  }
}

int compareTitleAsc(const void *a, const void *b) {
  const Movie *mA = (const Movie *)a;
  const Movie *mB = (const Movie *)b;
  return strcmp(mA->title, mB->title);
}

void listMoviesByTitle(const MovieArray *list) {
  MovieArray temp = *list;
  qsort(temp.movies, temp.count, sizeof(Movie), compareTitleAsc);
  printTableHeader();
  for (int i = 0; i < temp.count; i++) {
    printMovieRow(&temp.movies[i]);
  }
}

int strCaseStr(const char *haystack, const char *needle) {
  if (!*needle)
    return 1;
  for (const char *p = haystack; *p; p++) {
    if (tolower((unsigned char)*p) == tolower((unsigned char)*needle)) {
      const char *h, *n;
      for (h = p, n = needle; *h && *n; h++, n++) {
        if (tolower((unsigned char)*h) != tolower((unsigned char)*n))
          break;
      }
      if (!*n)
        return 1;
    }
  }
  return 0;
}

void searchMoviesByTitle(const MovieArray *list, const char *search) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    if (strCaseStr(list->movies[i].title, search)) {
      printMovieRow(&list->movies[i]);
    }
  }
}

void searchMoviesByGenre(const MovieArray *list, Genre genre) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
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

void searchMoviesByActor(const MovieArray *list, const char *actor) {
  printTableHeader();
  for (int i = 0; i < list->count; i++) {
    for (int j = 0; j < list->movies[i].actorsCount; j++) {
      if (strCaseStr(list->movies[i].actors[j], actor)) {
        printMovieRow(&list->movies[i]);
        break;
      }
    }
  }
}

void consultMovie(const MovieArray *list, int code) {
  for (int i = 0; i < list->count; i++) {
    if (list->movies[i].code == code) {
      Movie m = list->movies[i];
      printf("Code: %d\n", m.code);
      printf("Title: %s\n", m.title);
      printf("Director: %s\n", m.director);
      printf("Year: %d\n", m.year);
      printf("Duration: %d min\n", m.duration);
      printf("Rating: %.1f\n", m.rating);
      printf("Favorites: %d\n", m.favorite);
      printf("Revenue: %.2fM\n", m.revenue);
      printf("Description: %s\n", m.description);
      printf("Genres: ");
      for (int g = 0; g < GENRE_COUNT; g++) {
        if (m.genres[g])
          printf("%s ", getGenreName((Genre)g));
      }
      printf("\nActors: ");
      for (int a = 0; a < m.actorsCount; a++) {
        printf("%s", m.actors[a]);
        if (a < m.actorsCount - 1)
          printf(", ");
      }
      return;
    }
  }
  printf("Movie with code %d not found.\n", code);
}
