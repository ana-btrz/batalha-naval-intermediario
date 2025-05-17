#include <stdio.h>
#include <stdlib.h>

// Definição do nosso tabuleiro como 10x10
#define TAMANHO 10

//Representa os valores que tem em cada célula do tabuleiro
#define AGUA 0
#define NAVIO 3

// Função coloca o tabuleiro todo como água no início.
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Vamos percorrer cada linha do tabuleiro.
    for (int i = 0; i < TAMANHO; i++) {
        // Dentro de cada linha, vamos percorrer cada coluna.
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA; // Colocando '0' (água) em cada posição.
        }
    }
}

// Função para verificar se uma linha e coluna estão dentro do tabuleiro.
int dentroDoTabuleiro(int linha, int coluna) {
    // Se a linha for maior ou igual a 0 e menor que o tamanho, E a coluna for maior ou igual a 0 e menor que o tamanho,
    // então a posição está dentro do tabuleiro. Retornamos 1 (verdadeiro).
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

   
// Função para verificar as posições onde queremos o novio estar livre 
int posicoesLivres(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int direcao) {
    // Verifica cada parte do navio 
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna; // Começamos na posição inicial.
        // Ajustamos a linha e a coluna dependendo da direção:
        if (direcao == 0) c += i; // Horizontal: só a coluna muda.
        else if (direcao == 1) l += i; // Vertical: só a linha muda.
        else if (direcao == 2) { l += i; c += i; } // Diagonal Crescente: linha e coluna aumentam.
        else if (direcao == 3) { l += i; c -= i; } // Diagonal Decrescente: linha aumenta, coluna diminui.
   

        // Posicionamento estiver fora do tabuleiro ou já tiver um navio as posições estão ocupadas 
        if (!dentroDoTabuleiro(l, c) || tabuleiro[l][c] == NAVIO) {
            return 0; // Retornamos 0 (falso).
        }
    }
    return 1; // Se passamos por todas as partes do navio sem problemas, as posições estão livres. Retornamos 1 (verdadeiro).
}

    // Função que colocar os navios no tabuleiro.
    void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho, int direcao) {
    // Primeiro, verificamos se as posições estão livres.
    if (posicoesLivres(tabuleiro, linha, coluna, tamanho, direcao)) {
        // Se estiverem livres, vamos colocar o navio parte por parte.
        for (int i = 0; i < tamanho; i++) {
            int l = linha, c = coluna;
            if (direcao == 0) c += i;
            else if (direcao == 1) l += i;
            else if (direcao == 2) { l += i; c += i; }
            else if (direcao == 3) { l += i; c -= i; }
            tabuleiro[l][c] = NAVIO; // Colocamos '3' (navio) na posição.
        }
    } else {
        // Se as posições não estiverem livres, mostramos uma mensagem de erro.
        printf("Erro ao posicionar navio na linha %d, coluna %d, direcao %d.\n", linha, coluna, direcao);
    }
}

 // Função para mostrar o tabuleiro no console.
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("  "); // Espaços para alinhar com os números das colunas.
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", j); // Imprime os números das colunas (0 a 9).
    }
    printf("\n");
    return 0;
