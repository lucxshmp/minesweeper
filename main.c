#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabuleiro.h"
 

int main() {
    // Defining variables and the array
    char nomeArquivo[20];
    int linha = 0, coluna = 0, bombas = 0, b1 = 0, b2 = 0, jogadas = 0, j1 = 0, j2 = 0;
    tab ** x;
    
    // opening the file
    FILE *f;
    scanf("%s", nomeArquivo);
    f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // collecting the number of rows and columns
    fscanf(f, "%d %d", &linha, &coluna);

    // arranging the board: 1) creating an array of size rowsXcolumns 
    x = aloca_matriz(linha, coluna);

    // arranging the board: 2) assigning 0 to all of the structs
    zerar_matriz(x, linha, coluna);
    
    // arranging the board: 3) inserting the bombs
    fscanf(f, "%d", &bombas);
    for (int i = 0; i < bombas; i++) {
        fscanf(f, "%d %d", &b1, &b2);
        x[b1][b2].valor = -1;
    }
    
    // arranging the board: 4) Inserting the number of bombs in the surroundings into the places without bombs
    contador(x, linha, coluna);

    // collecting moves and applying them through the recursive function.
    fscanf(f, "%d", &jogadas);
    for (int i = 0; i < jogadas; i++) {
        fscanf(f, "%d %d", &j1, &j2);
        tentativas(x, linha, coluna, j1, j2);
        if (x[j1][j2].revelado == -1) {
            printf("Uma mina foi encontrada na jogada %d!\n", i + 1);
            break;
        }
    }

    // print the board
    imprimirTabuleiro(x, linha, coluna);

    // freeing dynamically allocated memory
    libera_matriz(x, linha);

    // closing the file
    fclose(f);
    return 0;
}
