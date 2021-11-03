#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct no{
	char tab[3][3];
	struct no* filhos[9];//númerto máximo de filhos
};

struct no* raiz = NULL;

void jogadaRandom(char caractere, char tabuleiro[3][3]){

    int linha, coluna;
    do{

        linha = rand() % 3;
        coluna = rand() % 3;

    }while(tabuleiro[linha][coluna] != ' ');

    //faz a jogada aleatória
    tabuleiro[linha][coluna] = caractere;


};

void IA(char caractere, char tabuleiro[3][3]){


}

//pede para o jogador digitar
void jogar(char caractere, char nome[100], char tabuleiro[3][3]){
    int  linha, coluna;
    printf("Digite a posição da jogada(ex: 1 1). Vez de: %s", nome);
    scanf("%d %d", &linha, &coluna);

    if(tabuleiro[linha][coluna] == ' '){
        tabuleiro[linha][coluna] = caractere;
    }else{
        printf("Essa posição já está ocupada!\n");
        jogar(caractere, nome, tabuleiro);
    }

}

/*
 * Executa uma verificação para saber se o jogo acabou e se há um vencedor
 */
bool alguemGanhou(char tabuleiro[3][3], char nome1[100], char nome2[100]){

    if( (tabuleiro[0][0] == tabuleiro[0][1] && tabuleiro[0][0] == tabuleiro[0][2] && tabuleiro[0][0] == 'X')||
        (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[0][0] == 'X')||
        (tabuleiro[0][0] == tabuleiro[1][0] && tabuleiro[0][0] == tabuleiro[2][0] && tabuleiro[0][0] == 'X')||
        (tabuleiro[0][1] == tabuleiro[1][1] && tabuleiro[0][1] == tabuleiro[2][1] && tabuleiro[0][1] == 'X')||
        (tabuleiro[0][2] == tabuleiro[1][2] && tabuleiro[0][2] == tabuleiro[2][2] && tabuleiro[0][2] == 'X')||
        (tabuleiro[1][0] == tabuleiro[1][1] && tabuleiro[1][0] == tabuleiro[1][2] && tabuleiro[1][0] == 'X')||
        (tabuleiro[2][0] == tabuleiro[2][1] && tabuleiro[2][0] == tabuleiro[2][2] && tabuleiro[2][0] == 'X')||
        (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[2][0] == tabuleiro[0][2] && tabuleiro[2][0] == 'X')){
        //o jogador 1(X) ganhou

        for(int i=0; i<15; i++){
            printf("\n");
        }

        mostrarJogo(tabuleiro);
        printf("Ganhador: %s", nome1);
        return true;

    }else
    if( (tabuleiro[0][0] == tabuleiro[0][1] && tabuleiro[0][0] == tabuleiro[0][2] && tabuleiro[0][0] == 'O')||
        (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[0][0] == 'O')||
        (tabuleiro[0][0] == tabuleiro[1][0] && tabuleiro[0][0] == tabuleiro[2][0] && tabuleiro[0][0] == 'O')||
        (tabuleiro[0][1] == tabuleiro[1][1] && tabuleiro[0][1] == tabuleiro[2][1] && tabuleiro[0][1] == 'O')||
        (tabuleiro[0][2] == tabuleiro[1][2] && tabuleiro[0][2] == tabuleiro[2][2] && tabuleiro[0][2] == 'O')||
        (tabuleiro[1][0] == tabuleiro[1][1] && tabuleiro[1][0] == tabuleiro[1][2] && tabuleiro[1][0] == 'O')||
        (tabuleiro[2][0] == tabuleiro[2][1] && tabuleiro[2][0] == tabuleiro[2][2] && tabuleiro[2][0] == 'O')||
        (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[2][0] == tabuleiro[0][2] && tabuleiro[2][0] == 'O')){
        //o jogador 2(O) ganhou

        for(int i=0; i<15; i++){
            printf("\n");
        }

        mostrarJogo(tabuleiro);
        printf("Ganhador: %s", nome2);
        return true;

    }else
    if( tabuleiro[0][0] != ' ' && tabuleiro[0][1] != ' ' && tabuleiro[0][2] != ' ' &&
        tabuleiro[1][0] != ' ' && tabuleiro[1][1] != ' ' && tabuleiro[1][2] != ' ' &&
        tabuleiro[2][0] != ' ' && tabuleiro[2][1] != ' ' && tabuleiro[2][2] != ' ' ){
        //deu velha

        for(int i=0; i<15; i++){
            printf("\n");
        }

        mostrarJogo(tabuleiro);
        printf("Deu velha\n");
        return true;

    }

    //o jogo ainda não acabou
    return false;
}


//mostra o tabuleiro do jogo
void mostrarJogo(char tabuleiro[3][3]){

	printf("\n\n      0   1   2\n\n");

	for(int i=0; i<3; i++){
		printf("  %d   %c | %c | %c\n", i, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);

		//formatação do texto na tela
		if(i!=2){
            printf("     ---|---|---\n");
        }
	}
    printf("\n");
}
