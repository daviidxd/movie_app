#include <stdio.h>
#include <stdlib.h>
#include "movie.h"
#include "utils.h"

void printMenu() {
    printf("1. List Movies\n");
    printf("2. Search Movies\n");
    printf("3. Consult Movie Details\n");
    printf("4. Add Movie\n");
    printf("0. Exit\n");
}

void printListMenu() {
    printf("1. By Code (Ascending)\n");
    printf("2. By Rating (Descending)\n");
    printf("3. By Title (Alphabetical)\n");
    printf("0. Back\n");
}

void printSearchMenu() {
    printf("1. By Title\n");
    printf("2. By Genre\n");
    printf("3. By Director\n");
    printf("4. By Actor\n");
    printf("0. Back\n");
}

int main() {
    MovieArray movieData;
    initializeMovies(&movieData);

    int choice;
    do {
        printMenu();
        choice = readInteger("Select an option: ");

        switch (choice) {
            case 1: {
                int listChoice;
                do {
                    printListMenu();
                    listChoice = readInteger("Select list option: ");
                    switch (listChoice) {
                        case 1: listMoviesByCode(&movieData); break;
                        case 2: listMoviesByRating(&movieData); break;
                        case 3: listMoviesByTitle(&movieData); break;
                        case 0: break;
                        default: printf("Invalid option.\n");
                    }
                } while (listChoice != 0);
                break;
            }
            case 2: {
                int searchChoice;
                do {
                    printSearchMenu();
                    searchChoice = readInteger("Select search option: ");
                    switch (searchChoice) {
                        case 1: {
                            char search[MAX_STRING];
                            readString("Enter title to search: ", search, MAX_STRING);
                            searchMoviesByTitle(&movieData, search);
                            break;
                        }
                        case 2: {
                            Genre g = selectGenre();
                            searchMoviesByGenre(&movieData, g);
                            break;
                        }
                        case 3: {
                            char director[MAX_STRING];
                            readString("Enter director name: ", director, MAX_STRING);
                            searchMoviesByDirector(&movieData, director);
                            break;
                        }
                        case 4: {
                            char actor[MAX_STRING];
                            readString("Enter actor name: ", actor, MAX_STRING);
                            searchMoviesByActor(&movieData, actor);
                            break;
                        }
                        case 0: break;
                        default: printf("Invalid option.\n");
                    }
                } while (searchChoice != 0);
                break;
            }
            case 3: {
                int code = readInteger("Enter Movie Code: ");
                consultMovie(&movieData, code);
                break;
            }
            case 4:
                addMovie(&movieData);
                break;
            case 0: {
                printf("Are you sure you want to exit? (1: Yes, 0: No): ");
                int confirm = readInteger("");
                if (confirm == 1) {
                } else {
                    choice = -1;
                }
                break;
            }
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
