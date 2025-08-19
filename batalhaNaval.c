#include <stdio.h>
#include <stdlib.h>

#define TAM 10      // tamanho do tabuleiro 10x10
#define NAVIO 3     // tamanho fixo dos navios
#define HABIL 5     // tamanho das matrizes (5x5)

// Função para aplicar a habilidade no tabuleiro 
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HABIL][HABIL], int origemLinha, int origemColuna) {
    int meio = HABIL / 2; // Ponto central da matriz de habilidade
   
    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            int linhaTab = origemLinha - meio + i;
            int colTab   = origemColuna - meio + j;

            // Garantir que estamos dentro dos limites do tabuleiro 
            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (habilidade[i][j] == 1) {
                    if (tabuleiro[linhaTab][colTab] == 0) {
                        tabuleiro[linhaTab][colTab] = 5; // marca habilidade
                    }
                }
            }
        }
    }
}

// Função para exibir uma matriz de habilidade 
void exibirHabilidade(int habilidade[HABIL][HABIL], const char *nome) {
    printf("\n=== Habilidade: %s ===\n", nome);
    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            if (habilidade[i][j] == 1)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};
    
    // Posicionar navios
    int linhaVertical = 2, colunaVertical = 5; 
    for (int i = 0; i < NAVIO; i++) 
        tabuleiro[linhaVertical+i][colunaVertical] = 3;

    int linhaHorizontal = 7, colunaHorizontal = 5;
    for (int j = 0; j < NAVIO; j++) 
        tabuleiro[linhaHorizontal][colunaHorizontal+j] = 3;

    int linhaDiagonal1 = 0, colunaDiagonal1 = 0;
    for (int k = 0; k < NAVIO; k++) 
        tabuleiro[linhaDiagonal1+k][colunaDiagonal1+k] = 3;

    int linhaDiagonal2 = 0, colunaDiagonal2 = 9;
    for (int k = 0; k < NAVIO; k++) 
        tabuleiro[linhaDiagonal2+k][colunaDiagonal2-k] = 3;

    // Matrizes de habilidade
    int cone[HABIL][HABIL] = {0}, cruz[HABIL][HABIL] = {0}, octaedro[HABIL][HABIL] = {0};

    // Construir cone
    for (int i = 0; i < HABIL; i++) 
        for (int j = 0; j < HABIL; j++) 
            if (j >= 2-i && j <= 2+i) cone[i][j] = 1;

    // Construir cruz
    for (int i = 0; i < HABIL; i++) 
        for (int j = 0; j < HABIL; j++) 
            if (i == 2 || j == 2) cruz[i][j] = 1;

    // Construir octaedro
    for (int i = 0; i < HABIL; i++) 
        for (int j = 0; j < HABIL; j++) 
            if (j >= 2-abs(2-i) && j <= 2+abs(2-i)) octaedro[i][j] = 1;

    // Exibir habilidades
    exibirHabilidade(cone, "Cone");
    exibirHabilidade(cruz, "Cruz");
    exibirHabilidade(octaedro, "Octaedro");

    // Aplicar habilidades
    aplicarHabilidade(tabuleiro, cone, 1, 1);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);
             
    // Exibir o tabuleiro  
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");

    // Cabeçalho com letras (colunas)
    printf("    ");
    for (int j = 0; j < TAM; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    // Linhas com números (1-10)
    for (int i = 0; i < TAM; i++) {
        printf("%2d  ", i + 1);
        for (int j = 0; j < TAM; j++) {
            char simbolo;
            if (tabuleiro[i][j] == 0) simbolo = '~';  // água 
            else if (tabuleiro[i][j] == 3) simbolo = 'N'; // navio
            else simbolo = '*'; // área de habilidade 
            printf("%c ", simbolo);
        }
        printf("\n");
    }

    return 0;
}
