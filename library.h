#ifndef TABULEIRO_H
#define TABULEIRO_H

//criando a struct
typedef struct {
    int valor;
    int revelado;
} tab;

//cabeçalho das funções
void tentativas(tab **A, int linhas, int colunas, int coord1, int coord2);
void contador(tab **X, int linhas, int colunas);
void imprimirTabuleiro(tab **X, int linhas, int colunas);
tab** aloca_matriz(int n, int m);
void zerar_matriz(tab **A, int n, int m);
void libera_matriz(tab **A, int n);

#endif 
