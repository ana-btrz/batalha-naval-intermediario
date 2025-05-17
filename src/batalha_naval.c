#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Para a função abs()

// Definição do nosso tabuleiro como 10x10
#define TAMANHO_TABULEIRO 10

//Representa os valores que tem em cada célula do tabuleiro
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

// Definição do tamanho das matrizes de habilidade
#define TAMANHO_HABILIDADE 7 // Tamanho ímpar para ter um centro bem definido

// Função para verificar se uma linha e coluna estão dentro do tabuleiro
int dentroDoTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se as posições para o navio estão livres
int posicoesLivres(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, int direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (direcao == 0) c += i;
        else if (direcao == 1) l += i;
        else if (direcao == 2) { l += i; c += i; }
        else if (direcao == 3) { l += i; c -= i; }

        if (!dentroDoTabuleiro(l, c) || tabuleiro[l][c] == NAVIO) {
            return 0;
        }
    }
    return 1;
}

// Função para posicionar os navios no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, int direcao) {
    if (posicoesLivres(tabuleiro, linha, coluna, tamanho, direcao)) {
        for (int i = 0; i < tamanho; i++) {
            int l = linha, c = coluna;
            if (direcao == 0) c += i;
            else if (direcao == 1) l += i;
            else if (direcao == 2) { l += i; c += i; }
            else if (direcao == 3) { l += i; c -= i; }
            tabuleiro[l][c] = NAVIO;
        }
    } else {
        printf("Erro ao posicionar navio na linha %d, coluna %d, direcao %d.\n", linha, coluna, direcao);
    }
}

// Funções para criar as matrizes de habilidade
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = (i >= 0 && j >= centro - i && j <= centro + i) ? 1 : 0;
        }
    }
}

void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Função para inicializar o tabuleiro com água e alguns navios
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    // Posicionamento de alguns navios para teste
    posicionarNavio(tabuleiro, 2, 1, 3, 0);
    posicionarNavio(tabuleiro, 5, 3, 3, 1);
    posicionarNavio(tabuleiro, 0, 0, 3, 2);
    posicionarNavio(tabuleiro, 0, 9, 3, 3);
}

// Função para sobrepor a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int centroHabilidade = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTabuleiro = linhaOrigem - centroHabilidade + i;
                int colunaTabuleiro = colunaOrigem - centroHabilidade + j;
                if (dentroDoTabuleiro(linhaTabuleiro, colunaTabuleiro) && tabuleiro[linhaTabuleiro][colunaTabuleiro] != NAVIO) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = AREA_AFETADA;
                }
            }
        }
    }
}

// Função para mostrar o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("0 ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("3 ");
            } else if (tabuleiro[i][j] == AREA_AFETADA) {
                printf("5 ");
            } else {
                printf(". "); // Para debugging
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Declara o nosso tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água e posiciona alguns navios
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro Inicial:\n");
    exibirTabuleiro(tabuleiro);

    // Matrizes de habilidade
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE] = {0};

    // Criar as formas das habilidades
    criarCone(habilidadeCone);
    printf("Forma da Habilidade Cone:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidadeCone[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    criarCruz(habilidadeCruz);
    printf("Forma da Habilidade Cruz:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidadeCruz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    criarOctaedro(habilidadeOctaedro);
    printf("Forma da Habilidade Octaedro:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidadeOctaedro[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Ponto de origem das habilidades no tabuleiro (definido diretamente no código)
    int origemConeLin = 2;
    int origemConeCol = 7;
    int origemCruzLin = 5;
    int origemCruzCol = 5;
    int origemOctaedroLin = 7;
    int origemOctaedroCol = 2;

    // Aplicar as habilidades ao tabuleiro
    printf("Tabuleiro com Habilidade Cone aplicada em (%d, %d):\n", origemConeLin, origemConeCol);
    aplicarHabilidade(tabuleiro, habilidadeCone, origemConeLin, origemConeCol);
    exibirTabuleiro(tabuleiro);

    // Reinicializar o tabuleiro para aplicar a próxima habilidade
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro com Habilidade Cruz aplicada em (%d, %d):\n", origemCruzLin, origemCruzCol);
    aplicarHabilidade(tabuleiro, habilidadeCruz, origemCruzLin, origemCruzCol);
    exibirTabuleiro(tabuleiro);

    // Reinicializar o tabuleiro para aplicar a próxima habilidade
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro com Habilidade Octaedro aplicada em (%d, %d):\n", origemOctaedroLin, origemOctaedroCol);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, origemOctaedroLin, origemOctaedroCol);
    exibirTabuleiro(tabuleiro);

    return 0;
}