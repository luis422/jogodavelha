#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include "arvoreJogoDaVelha.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    //variáveis
    int vez = 2, op, contRand = 1;
    char tabuleiro[3][3],
         nome1[100],
         nome2[100] = {"IA"};


    //loop para jogar mais rodadas
    do{

        //resetando tabuleiro
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                tabuleiro[i][j] = ' ';
            }
        }
        //resetando variável vez para começar uma nova rodada
vez = 3/*2*/;
        contRand = 1;

        //limpa a tela a cada nova rodada
        system("cls || clear");

        //pedindo o nome dos jogadores
        printf("\n  #####################\n  ##  JOGO DA VELHA  ##\n  #####################\n\n");
        printf("Digite o nome do jogador 1(X): ");
        _flushall();
        fgets(nome1, 100, stdin);
        //printf("Digite o nome do jogador 2(O): ");
        //fgets(nome2, 100, stdin);
//tirar depois
char tab[3][3] = {'X','O',' ','X','X',' ','O',' ',' '};
for(int i=0; i<3; i++){
 for(int j=0; j<3; j++){
  tabuleiro[i][j] = tab[i][j];
 }
}
        mostrarJogo(tabuleiro);

        //loop para jogadas
        do{
//tirar depois
char tab[3][3] = {'X','O',' ','X','X',' ','O',' ',' '};
for(int i=0; i<3; i++){
 for(int j=0; j<3; j++){
  tabuleiro[i][j] = tab[i][j];
 }
}
            //se a vez for par, jogador 1
            if(vez%2==0){
                jogar('X', nome1, tabuleiro);

            //se a vez for ímpar, jogador 2
            }else{
                printf("Vez da IA...");

                //jogada aleatória
                if(contRand <= JOGADAS_ALEATORIAS)
                    jogadaRandom('O', tabuleiro);
                else
                    IA('O', 'X', tabuleiro);

                contRand++;

            }

            //atualiza a vez dos jogadores
            vez++;

            //verificação para saber se alguém ganhou
        }while(!finalDoJogo(tabuleiro, nome1, nome2));

        printf("\nDeseja jogar novamente?\n[1 - Sim]\n[2 - Não]\n");
        scanf("%d", &op);

    }while(op==1);

	return 0;
}
