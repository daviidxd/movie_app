#include <stdio.h>
#include <stdlib.h>
#include "movie.h"
#include "utils.h"

// Menu principal que aparece quando o programa inicia
void printMenu() {
    printf("1. Listar Filmes\n");
    printf("2. Pesquisar Filmes\n");
    printf("3. Consultar Detalhes do Filme\n");
    printf("4. Adicionar Filme\n");
    printf("0. Sair\n");
}

// Menu para escolher como queremos ver a lista de filmes
void printListMenu() {
    printf("1. Por Código (Crescente)\n");
    printf("2. Por Classificação (Decrescente)\n");
    printf("3. Por Título (Alfabético)\n");
    printf("0. Voltar\n");
}

// Menu para escolher o tipo de pesquisa
void printSearchMenu() {
    printf("1. Por Título\n");
    printf("2. Por Género\n");
    printf("3. Por Realizador\n");
    printf("4. Por Ator\n");
    printf("0. Voltar\n");
}

int main() {
    MovieArray movieData;
    initializeMovies(&movieData);

    int choice;
    // Loop principal do programa. Só sai quando o utilizador escolhe 0
    do {
        printMenu();
        choice = readInteger("Selecione uma opção: ");

        switch (choice) {
            case 1: {
                // Sub-menu de listagem
                int listChoice;
                do {
                    printListMenu();
                    listChoice = readInteger("Selecione uma opção de listagem: ");
                    switch (listChoice) {
                        case 1: listMoviesByCode(&movieData); break;
                        case 2: listMoviesByRating(&movieData); break;
                        case 3: listMoviesByTitle(&movieData); break;
                        case 0: break;
                        default: printf("Opção inválida.\n");
                    }
                } while (listChoice != 0);
                break;
            }
            case 2: {
                // Sub-menu de pesquisa
                int searchChoice;
                do {
                    printSearchMenu();
                    searchChoice = readInteger("Selecione uma opção de pesquisa: ");
                    switch (searchChoice) {
                        case 1: {
                            char search[MAX_STRING];
                            readString("Introduza o título para pesquisar: ", search, MAX_STRING);
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
                            readString("Introduza o nome do realizador: ", director, MAX_STRING);
                            searchMoviesByDirector(&movieData, director);
                            break;
                        }
                        case 4: {
                            char actor[MAX_STRING];
                            readString("Introduza o nome do ator: ", actor, MAX_STRING);
                            searchMoviesByActor(&movieData, actor);
                            break;
                        }
                        case 0: break;
                        default: printf("Opção inválida.\n");
                    }
                } while (searchChoice != 0);
                break;
            }
            case 3: {
                int code = readInteger("Introduza o Código do Filme: ");
                consultMovie(&movieData, code);
                break;
            }
            case 4:
                addMovie(&movieData);
                break;
            case 0: {
                printf("Tem a certeza que quer sair? (1: Sim, 0: Não): ");
                int confirm = readInteger("");
                if (confirm == 1) {
                } else {
                    choice = -1;
                }
                break;
            }
            default:
                printf("Opção inválida.\n");
        }
    } while (choice != 0);

    return 0;
}
