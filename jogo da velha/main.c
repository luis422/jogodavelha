#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "arvoreJogoDaVelha.h"

int main() {
    setlocale(LC_ALL, "Portuguese");

    //variaveis
    int vez = 2, op, contRand = 1;
    char tabuleiro[3][3],
         nome1[100],
         nome2[100] = {"IA"};


    //loop para jogar mais rodadas
    do{

        //reset do tabuleiro
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                tabuleiro[i][j] = ' ';
            }
        }
        //reset da variavel vez para comecar uma nova rodada
        vez = 2;
        contRand = 1;

        //limpa a tela a cada nova rodada
        system("cls || clear");

        printf("\n  #####################\n  ##  JOGO DA VELHA  ##\n  #####################\n\n");
        printf("Digite o nome do jogador 1(X): ");
        _flushall();
        fgets(nome1, 100, stdin);
        //printf("Digite o nome do jogador 2(O): ");
        //fgets(nome2, 100, stdin);

        mostrarJogo(tabuleiro);


        //loop para jogadas
        do{
            //se a vez for par, jogador 1
            if(vez%2==0){
                vezDoPlayer('X', nome1, tabuleiro);

            //se a vez for Ã­mpar, jogador 2
            }else{
                printf("\nVez da IA...");

                //jogada aleatoria
                if(contRand <= JOGADAS_ALEATORIAS)
                    jogadaRandom('O', tabuleiro);
                else
                    IA('O', 'X', tabuleiro);

                contRand++;

            }

            //atualiza a vez dos jogadores
            vez++;

        //teste para saber se o jogo acabou
        }while(!finalDoJogo(tabuleiro, nome1, nome2));

        //exclui a árvore a cada novo jogo
        excluirArvore(&raizIA);
        raizIA = NULL;

        printf("\nDeseja jogar novamente?\n[1 - Sim]\n[2 - Nï¿½o]\n");
        scanf("%d", &op);

    }while(op==1);

	return 0;
}
