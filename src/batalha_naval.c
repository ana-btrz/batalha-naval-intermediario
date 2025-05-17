#include <stdio.h>

// Definições de constantes para o tabuleiro e navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // Representação do tabuleiro (matriz 10x10)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int navio_horizontal_linha = 2;
    int navio_horizontal_coluna = 3;
    int navio_vertical_linha = 6;
    int navio_vertical_coluna = 1;

    // Posicionamento do navio horizontal
    if (navio_horizontal_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica se não há sobreposição com outros navios (neste caso, apenas com a água inicial)
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_horizontal_linha][navio_horizontal_coluna + i] = NAVIO;
            }
        } else {
            printf("Erro: Navio horizontal sobrepõe outra embarcação.\n");
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro.\n");
    }

    // Posicionamento do navio vertical
    if (navio_vertical_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica se não há sobreposição
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] == NAVIO) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_vertical_linha + i][navio_vertical_coluna] = NAVIO;
            }
        } else {
            printf("Erro: Navio vertical sobrepõe outra embarcação.\n");
        }
    } else {
        printf("Erro: Navio vertical fora dos limites do tabuleiro.\n");
    }

    // Exibe o tabuleiro
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}