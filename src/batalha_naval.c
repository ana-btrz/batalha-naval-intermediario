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

    // Percorrer cada linha do tabuleiro para imprimir.
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i); // Imprime o número da linha.
        // Dentro de cada linha, percorremos cada coluna.
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o valor da célula (0 ou 3).
        }
        printf("\n"); // Depois de imprimir toda a linha, vamos para a próxima linha.
    }
    printf("\n"); // Linha extra no final para melhor visualização.
}

int main() {
    // Declara o nosso tabuleiro 10x10.
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro com água (todas as células com valor 0).
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicializado:\n");
    exibirTabuleiro(tabuleiro);

    printf("Posicionando os navios...\n");

    // Posicionar quatro navios, como pedido: dois horizontais/verticais e dois diagonais.
    // A direção 0 é horizontal, 1 é vertical, 2 é diagonal crescente, 3 é diagonal decrescente.
    int tamanhoNavio = 3; // O tamanho de todos os navios é 3.

    // Posicionando o primeiro navio horizontalmente. Escolhemos a linha 2 e a coluna 1.
    posicionarNavio(tabuleiro, 2, 1, tamanhoNavio, 0);
    printf("Navio horizontal posicionado.\n");

    // Posicionando o segundo navio verticalmente. Escolhemos a linha 5 e a coluna 3.
    posicionarNavio(tabuleiro, 5, 3, tamanhoNavio, 1);
    printf("Navio vertical posicionado.\n");

    // Posicionando o terceiro navio diagonalmente (linha e coluna aumentando). Começamos na linha 0 e coluna 0.
    posicionarNavio(tabuleiro, 0, 0, tamanhoNavio, 2);
    printf("Navio diagonal crescente posicionado.\n");

    // Posicionando o quarto navio diagonalmente (linha aumentando e coluna diminuindo). Começamos na linha 0 e coluna 9.
    posicionarNavio(tabuleiro, 0, 9, tamanhoNavio, 3);
    printf("Navio diagonal decrescente posicionado.\n");

    printf("\nTabuleiro com os navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    return 0; // Programa terminou corretamente.
}

    
