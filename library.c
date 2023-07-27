#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabuleiro.h"
 

// recursive function that executes the moves
void tentativas(tab **A, int linhas, int colunas, int coord1, int coord2) {
    if (coord1 < 0 || coord1 >= linhas || coord2 < 0 || coord2 >= colunas)
        return;

    if (A[coord1][coord2].revelado == 1)
        return;

    A[coord1][coord2].revelado = 1;

    if (A[coord1][coord2].valor == -1) {
        A[coord1][coord2].revelado = -1; // bomb founded, reveal -1
        return;
    }
    else if (A[coord1][coord2].valor == 0) {
        // reveal 0 and keep going revealing the empty adjacent cells
        tentativas(A, linhas, colunas, coord1 - 1, coord2);
        tentativas(A, linhas, colunas, coord1 + 1, coord2);
        tentativas(A, linhas, colunas, coord1, coord2 - 1);
        tentativas(A, linhas, colunas, coord1, coord2 + 1);
    }
}

// function that records the number of adjacent bombs on the cells
void contador(tab **X, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (X[i][j].valor != -1) {
                int bombas_ao_redor = 0;
                if (j > 0 && X[i][j - 1].valor == -1)
                    bombas_ao_redor++;
                if (j < colunas - 1 && X[i][j + 1].valor == -1)
                    bombas_ao_redor++;
                if (i > 0 && X[i - 1][j].valor == -1)
                    bombas_ao_redor++;
                if (i < linhas - 1 && X[i + 1][j].valor == -1)
                    bombas_ao_redor++;
                if (i > 0 && j < colunas - 1 && X[i - 1][j + 1].valor == -1)
                    bombas_ao_redor++;
                if (i > 0 && j > 0 && X[i - 1][j - 1].valor == -1)
                    bombas_ao_redor++;
                if (i < linhas - 1 && j > 0 && X[i + 1][j - 1].valor == -1)
                    bombas_ao_redor++;
                if (i < linhas - 1 && j < colunas - 1 && X[i + 1][j + 1].valor == -1)
                    bombas_ao_redor++;

                X[i][j].valor = bombas_ao_redor;
            }
        }
    }
}

// function that prints the board
void imprimirTabuleiro(tab **X, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (X[i][j].revelado == 0)
                printf("-\t"); // non-revealed cells
            else if (X[i][j].revelado == -1)
                printf("-1\t"); // revealed bomb
            else
                printf("%d\t", X[i][j].valor); // number on the revealed cells
        }
        printf("\n");
    }
}

// function that dynamically allocates and creates an array
tab** aloca_matriz(int n, int m) {
    tab** x = malloc(n * sizeof(tab*));
    for (int i = 0; i < n; i++) {
        x[i] = malloc(m * sizeof(tab));
    }
    return x;
}

//function that records 0 to all of the cells on the array
void zerar_matriz(tab **A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j].valor = 0;
            A[i][j].revelado = 0;
        }
    }
    
}

// function to free the dynamically allocated array 
void libera_matriz(tab **A, int n) {
for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
}
