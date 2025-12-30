#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "movie.h"
#include "utils.h"

// Menu principal que aparece quando o programa inicia
void printMenu() {
    printf("1. Listar Filmes\n");
    printf("2. Pesquisar Filmes\n");
    printf("3. Consultar Detalhes do Filme\n");
    printf("4. Adicionar Filme\n");
    printf("5. Alterar Filme\n");
    printf("6. Eliminar Filme\n");
    printf("7. Limpar Filmes\n");
    printf("8. Importar Filmes (CSV)\n");
    printf("9. Exportar Filmes (CSV)\n");
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
    // Define a localização para Português de Portugal para aceitar acentos e caracteres especiais
    setlocale(LC_ALL, "pt_PT.UTF-8");
    
    // Cria a estrutura que vai guardar todos os filmes. 'static' faz com que a variável dure o programa todo.
    static MovieArray movieData;
    
    // Prepara a lista de filmes (coloca o contador a zero)
    initializeMovies(&movieData);

    int choice;
    // Loop principal do programa. Só sai quando o utilizador escolhe 0
    do {
        printMenu();
        // Lê a escolha do utilizador
        choice = readInteger("Selecione uma opção: ");

        // Verifica qual foi a opção escolhida e executa o código correspondente
        switch (choice) {
            case 1: {
                // Sub-menu de listagem: permite escolher a ordem dos filmes
                int listChoice;
                    // Loop do sub-menu de listagem
                    do {
                        printListMenu();
                        listChoice = readInteger("Selecione uma opção de listagem: ");
                        switch (listChoice) {
                            case 1: listMoviesByCode(&movieData); break; // Lista por ordem de criação
                            case 2: listMoviesByRating(&movieData); break; // Lista por melhor classificação
                            case 3: listMoviesByTitle(&movieData); break; // Lista por ordem alfabética
                            case 0: break; // Sai do sub-menu
                            default: printf("Opção inválida.\n");
                        }
                    } while (listChoice != 0);
                break;
            }
            case 2: {
                // Sub-menu de pesquisa: permite procurar filmes por vários critérios
                int searchChoice;
                do {
                    printSearchMenu();
                    searchChoice = readInteger("Selecione uma opção de pesquisa: ");
                    switch (searchChoice) {
                        case 1: {
                            // Pesquisa por título
                            char search[MAX_STRING];
                            readString("Introduza o título para pesquisar: ", search, MAX_STRING);
                            searchMoviesByTitle(&movieData, search);
                            break;
                        }
                        case 2: {
                            // Pesquisa por género (mostra lista de géneros para escolher)
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
                // Pede o código do filme e mostra todos os detalhes
                int code = readInteger("Introduza o Código do Filme: ");
                consultMovie(&movieData, code);
                break;
            }
            case 4:
                // Chama a função para adicionar um novo filme
                addMovie(&movieData);
                break;
            case 5: {
                int code = readInteger("Introduza o Código do Filme a alterar: ");
                updateMovie(&movieData, code);
                break;
            }
            case 6: {
                int code = readInteger("Introduza o Código do Filme a eliminar: ");
                deleteMovie(&movieData, code);
                break;
            }
            case 7: {
                printf("Tem a certeza que quer apagar TODOS os filmes? (1: Sim, 0: Não): ");
                int confirm = readInteger("");
                if (confirm == 1) {
                    clearMovies(&movieData);
                    printf("Todos os filmes foram apagados.\n");
                }
                break;
            }
            case 8: {
                char filename[MAX_STRING];
                readString("Introduza o nome do ficheiro CSV para importar: ", filename, MAX_STRING);
                int count = importMovies(&movieData, filename);
                if (count >= 0) {
                    printf("%d filmes importados com sucesso.\n", count);
                }
                break;
            }
            case 9: {
                char filename[MAX_STRING];
                readString("Introduza o nome do ficheiro CSV para exportar: ", filename, MAX_STRING);
                if (exportMovies(&movieData, filename)) {
                    printf("Filmes exportados com sucesso.\n");
                }
                break;
            }
            case 0: {
                // Confirmação antes de sair do programa
                printf("Tem a certeza que quer sair? (1: Sim, 0: Não): ");
                int confirm = readInteger("");
                if (confirm == 1) {
                    // Se confirmar, o loop vai terminar porque choice continua a ser 0
                } else {
                    // Se não confirmar, muda choice para -1 para o loop continuar
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
