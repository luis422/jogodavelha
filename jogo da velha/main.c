#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "arvoreJogoDaVelha.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    //vari�veis
    int vez = 2, op;
    char tabuleiro[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '},
         nome1[100],
         nome2[100];


    //loop para jogar mais rodadas
    do{

        //pedindo o nome dos jogadores
        printf("\n  #####################\n  ##  JOGO DA VELHA  ##\n  #####################\n\n");
        printf("Digite o nome do jogador 1(X): ");
        fgets(nome1,100,stdin);
        printf("Digite o nome do jogador 2(O): ");
        fgets(nome2,100,stdin);

        //loop para escolher
        do{
            mostrarJogo(tabuleiro);

            //se a vez for par, jogador 1
            if(vez%2==0){

                jogar('X', nome1, tabuleiro);

            //se a vez for �mpar, jogador 2
            }else{

                jogar('O', nome2, tabuleiro);

            }

            //atualiza a vez dos jogadores
            vez++;

            //verifica��o para saber se algu�m ganhou
        }while(!alguemGanhou(tabuleiro, nome1, nome2));

        printf("\nDeseja jogar novamente?\n[1 - Sim]\n[2 - N�o]");
        scanf("%d", &op);

    }while(op==1);

	return 0;
}