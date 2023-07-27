#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabuleiro.h"
 

int main() {
    // Definindo variáveis e a matriz
    char nomeArquivo[20];
    int linha = 0, coluna = 0, bombas = 0, b1 = 0, b2 = 0, jogadas = 0, j1 = 0, j2 = 0;
    tab ** x;
    
    // Abrindo o arquivo
    FILE *f;
    scanf("%s", nomeArquivo);
    f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Coletando o número de linhas e colunas
    fscanf(f, "%d %d", &linha, &coluna);

    // Montando o tabuleiro 1) criando matriz de tamanho linha x coluna
    x = aloca_matriz(linha, coluna);

    // Montando o tabuleiro 2) atribuindo 0 a todos os structs
    zerar_matriz(x, linha, coluna);
    
    // Montando o tabuleiro 3) colocando bombas
    fscanf(f, "%d", &bombas);
    for (int i = 0; i < bombas; i++) {
        fscanf(f, "%d %d", &b1, &b2);
        x[b1][b2].valor = -1;
    }
    
    // Montando o tabuleiro 4) colocando nas casas livres o número de bombas ao redor
    contador(x, linha, coluna);

    // Recolhendo jogadas e aplicando elas através da função recursiva
    fscanf(f, "%d", &jogadas);
    for (int i = 0; i < jogadas; i++) {
        fscanf(f, "%d %d", &j1, &j2);
        tentativas(x, linha, coluna, j1, j2);
        if (x[j1][j2].revelado == -1) {
            printf("Uma mina foi encontrada na jogada %d!\n", i + 1);
            break;
        }
    }

    // Imprimir o tabuleiro
    imprimirTabuleiro(x, linha, coluna);

    // Liberando a memória alocada dinamicamente
    libera_matriz(x, linha);

    // Fechar arquivo
    fclose(f);
    return 0;
}
