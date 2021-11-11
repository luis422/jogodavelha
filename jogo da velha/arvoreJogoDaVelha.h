#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//configs
#define JOGADAS_ALEATORIAS      1
#define logIA                   true

struct noIA{
	char tab[3][3];
	struct noIA* filhos[9];//número máximo de filhos
	int valor;
};

struct noIA* raizIA = NULL;

//mostra o tabuleiro do jogo
void mostrarJogo(char t[3][3]){

	printf("\n\n      0   1   2\n\n");

	for(int i=0; i<3; i++){
		printf("  %d   %c | %c | %c\n", i, t[i][0], t[i][1], t[i][2]);

		//formatação do texto na tela
		if(i!=2){
            printf("     ---|---|---\n");
        }
	}
    printf("\n");
}

//faz uma jogada aleatória
void jogadaRandom(char caractere, char t[3][3]){

if(logIA){
printf("Jogada aleatória\n");}

    int linha, coluna;
    do{
        srand(time(NULL));
        linha = rand() % 3;
        coluna = rand() % 3;

    }while(t[linha][coluna] != ' ');

    //faz a jogada aleatória
    t[linha][coluna] = caractere;


}

bool deuVelha(char t[3][3]){

    if( t[0][0] != ' ' && t[0][1] != ' ' && t[0][2] != ' ' &&
        t[1][0] != ' ' && t[1][1] != ' ' && t[1][2] != ' ' &&
        t[2][0] != ' ' && t[2][1] != ' ' && t[2][2] != ' ' ){
        return true;
    }else{
        return false;
    }

}

bool marcouPonto(char c, char t[3][3]){
    if( (t[0][0] == t[0][1] && t[0][0] == t[0][2] && t[0][0] == c)||
        (t[0][0] == t[1][1] && t[0][0] == t[2][2] && t[0][0] == c)||
        (t[0][0] == t[1][0] && t[0][0] == t[2][0] && t[0][0] == c)||
        (t[0][1] == t[1][1] && t[0][1] == t[2][1] && t[0][1] == c)||
        (t[0][2] == t[1][2] && t[0][2] == t[2][2] && t[0][2] == c)||
        (t[1][0] == t[1][1] && t[1][0] == t[1][2] && t[1][0] == c)||
        (t[2][0] == t[2][1] && t[2][0] == t[2][2] && t[2][0] == c)||
        (t[2][0] == t[1][1] && t[2][0] == t[0][2] && t[2][0] == c)){
        return true;
    }else{
        return false;
    }
}

void jogar(char caractere, char nome[100], char t[3][3]){
    int  linha, coluna;
    printf("Digite a posição da jogada(ex: 1 1). Vez de: %s", nome);
    scanf("%d %d", &linha, &coluna);

    if(t[linha][coluna] == ' '){
        t[linha][coluna] = caractere;
    }else{
        printf("Essa posição já está ocupada!\n");
        jogar(caractere, nome, t);
    }

}

//Executa uma verificação para saber se o jogo acabou e se há um vencedor
bool finalDoJogo(char t[3][3], char nome1[100], char nome2[100]){

    printf("\n");
    mostrarJogo(t);

    if(marcouPonto('X', t)){
        //o jogador 1(X)
        printf("Ganhador: %s", nome1);
        return true;

    }else if(marcouPonto('O', t)){
        //o jogador 2(O)
        printf("Ganhador: %s", nome2);
        return true;

    }else if(deuVelha(t)){
        //deu velha
        printf("Deu velha\n");
        return true;
    }

    //o jogo ainda não acabou
    return false;
}

void minimax(char meuCaracter, char oponenteCaracter, struct noIA** raizIA){

    bool folha = true;

    //1 - avaliar se é folha
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if((*raizIA)->tab[i][j] == ' '){
                folha = false;
                i=j=3;
            }
        }
        if(folha){
            //calcular a heuristica

            //avaliar se a IA ganhou, perdeu ou deu velha
            if(marcouPonto(meuCaracter,(*raizIA)->tab)){
                //se eu ganhei
                (*raizIA)->valor = 1;
                return;

            }else if(marcouPonto(oponenteCaracter,(*raizIA)->tab)){
                //se o oponente ganhou
                (*raizIA)->valor = -1;
                return;

            }else if(deuVelha((*raizIA)->tab)){
                //se deu velha
                (*raizIA)->valor = 0;
                return;
            }

        }else{
            //se não for folha
            (*raizIA)->valor = 0;
        }
    }

    //se o jogo ainda não acabou
    //fazer chamada recursiva com for, e if para ver se os filhos são nulos ou não
    for(int k=0; k<9; k++)
        if((*raizIA)->filhos[k]!=NULL){
            minimax(meuCaracter, oponenteCaracter, &(*raizIA)->filhos[k]);
        }

}

void criarArvore(char meuCaracter, char oponenteCaracter, struct noIA** raizIA, bool minhaVez){

    if((*raizIA)!=NULL){

        //rodando todas as posições do tabuleiro pai
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){

                //1 - para cada espaço em branco no tabuleiro do pai...
                if((*raizIA)->tab[i][j] == ' '){

                    //2 - alocar/criar um novo filho
                    (*raizIA)->filhos[(2*i)+j+i] = (struct noIA*) malloc(sizeof(struct noIA));
                    (*raizIA)->filhos[(2*i)+j+i]->valor = 0;

                    //3 - copiar tabuleiro do pai nos filhos
                    for(int k=0; k<3; k++){
                        for(int l=0; l<3; l++){
                            (*raizIA)->filhos[(2*i)+j+i]->tab[k][l] = (*raizIA)->tab[k][l];
                        }
                    }


                    //4 - fazer a jogada no tabuleiro do filho, de acordo com a rodada
                    if(minhaVez){
                        (*raizIA)->filhos[(2*i)+j+i]->tab[i][j] = meuCaracter;
                    }else{
                        (*raizIA)->filhos[(2*i)+j+i]->tab[i][j] = oponenteCaracter;
                    }

                    //poda alpha-beta
                    if(!marcouPonto(oponenteCaracter, (*raizIA)->tab) &&
                       !marcouPonto(meuCaracter, (*raizIA)->tab) &&
                       !deuVelha((*raizIA)->tab)){

                        //5 - repetir o processo para cada filho criado
                        criarArvore(meuCaracter, oponenteCaracter, &(*raizIA)->filhos[(2*i)+j+i], !minhaVez);

                       }else{
                            //1.2 - senão o filho será nulo naquela posição
                            (*raizIA)->filhos[(2*i)+j+i] = NULL;
                        }
                }else{
                    //1.2 - senão tiver espaço em branco, o filho será nulo naquela posição
                    (*raizIA)->filhos[(2*i)+j+i] = NULL;
                }
            }
        }
    }
}

void mostrarArvore(struct noIA** raizIA){

    if((*raizIA)!=NULL){

        printf("\nmostrarArvore() heurístico[%d]\n tabuleiro:",(*raizIA)->valor);

        for(int k=0; k<3; k++){
            printf("\n    %c. %c. %c.", (*raizIA)->tab[k][0], (*raizIA)->tab[k][1], (*raizIA)->tab[k][2]);
        }
        puts("\n");

        for(int k=0; k<9; k++){
            mostrarArvore(&(*raizIA)->filhos[k]);
        }
    }
}

int encontraFolhaArvore(struct noIA** raizIAlocal){

    if((*raizIAlocal) != NULL){

        bool folha = true;
        //teste se é folha
        for(int k=0; k<9; k++){
            if((*raizIAlocal)->filhos[k]!=NULL){
                folha = false;
                break;
            }
        }
        if(folha){
            return (*raizIAlocal)->valor;
        }else{
            for(int k=0; k<9; k++){
                if((*raizIAlocal) != NULL){
                    (*raizIAlocal)->valor = (*raizIAlocal)->valor + encontraFolhaArvore(&(*raizIAlocal)->filhos[k]);
                }
            }
            return (*raizIAlocal)->valor;
        }
	}else{
        return 0;
	}
}

//algoritmo responsável por 'pensar' qual é a melhor jogada a seguir
void IA(char meuCaracter, char oponenteCaracter, char t[3][3]){

    //alocando árvore usada pela IA
    raizIA = (struct noIA*)malloc(sizeof(struct noIA));
    int melhorFilho = -1;
    int maiorHeuristica = -9999999;

    //criando cópia do tabuleiro principal, para a àrvore de simulação da IA
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            raizIA->tab[i][j] = t[i][j];
        }
    }

    //Passo 1 - criar a árvore de possibilidades
    criarArvore(meuCaracter, oponenteCaracter, &raizIA, true);

    //Passo 2 - calcular minimax
    minimax(meuCaracter, oponenteCaracter, &raizIA);
    //se IA ganhar logo na próxima jogada, é ela que queremos...
    for(int i=0; i<9; i++){
        if(raizIA->filhos[i] != NULL){

            if(marcouPonto(meuCaracter, raizIA->filhos[i]->tab)){
                raizIA->filhos[i]->valor += 1000;
            }
        }
    }

    //para cada filho não nulo da raiz, somar heurísticas
    for(int i=0; i<9; i++){
        if(raizIA->filhos[i] != NULL){
            raizIA->filhos[i]->valor += encontraFolhaArvore(&raizIA->filhos[i]);

            //Passo 3 - decidir a melhor jogada
            if(raizIA->filhos[i]->valor > maiorHeuristica){
                maiorHeuristica = raizIA->filhos[i]->valor;
                melhorFilho = i;
            }

        }
    }
    printf("\nmelhor filho para jogar = %d", melhorFilho);
    printf("\nvalor h do filho        = %d", maiorHeuristica);

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){

            //ver onde está a jogada do filho
            if(raizIA->filhos[melhorFilho]->tab[i][j] != t[i][j]){

                //Passo 4 - jogar
                t[i][j] = raizIA->filhos[melhorFilho]->tab[i][j];
                i=j=3;
            }

        }
    }


    //t[linha][coluna];

    //resetar a árvore da IA
    free(raizIA);
}











