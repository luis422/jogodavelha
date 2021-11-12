#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

//configs
#define JOGADAS_ALEATORIAS      0

struct noIA{

    //tabuleiro
	char tab[3][3];

    //nós filhos
	struct noIA* filhos[9];//número filhos

    //valor da heuristica
	int valor;
};

//raiz da árvore
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

//verifica se o jogador ganhou
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

void vezDoPlayer(char caractere, char nome[100], char t[3][3]){
    int  linha, coluna;
    printf("Digite a posição da jogada(linha coluna). Vez de: %s ", nome);
    scanf("%d %d", &linha, &coluna);

    if(t[linha][coluna] == ' '){
        t[linha][coluna] = caractere;
    }else{
        printf("Essa posição já está ocupada!\n");
        vezDoPlayer(caractere, nome, t);
    }

}

//Executa um teste para saber se o jogo acabou e se tem algum vencedor
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

    //o jogo ainda esta em andamento
    return false;
}

void calcHeuristico(char meuCaracter, char oponenteCaracter, struct noIA** raizIA){

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
            //calcular a heurística

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
            calcHeuristico(meuCaracter, oponenteCaracter, &(*raizIA)->filhos[k]);
        }

}

void criarArvore(char meuCaracter, char oponenteCaracter, struct noIA** raizIA, bool minhaVez){

    if((*raizIA)!=NULL){

        //percorrendo todas as posições do tabuleiro pai
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){

                //1 - para cada espaço em branco no tabuleiro do pai...
                if((*raizIA)->tab[i][j] == ' '){

                    //alocar/criar um novo nó filho
                    (*raizIA)->filhos[(2*i)+j+i] = (struct noIA*) malloc(sizeof(struct noIA));
                    //definir valor do nó filho = 0
                    (*raizIA)->filhos[(2*i)+j+i]->valor = 0;

                    //copiar tabuleiro do pai nos filhos
                    for(int k=0; k<3; k++){
                        for(int l=0; l<3; l++){
                            (*raizIA)->filhos[(2*i)+j+i]->tab[k][l] = (*raizIA)->tab[k][l];
                        }
                    }


                    //fazer a jogada no tabuleiro do filho, de acordo com a rodada
                    if(minhaVez){
                        (*raizIA)->filhos[(2*i)+j+i]->tab[i][j] = meuCaracter;
                    }else{
                        (*raizIA)->filhos[(2*i)+j+i]->tab[i][j] = oponenteCaracter;
                    }

                    //poda alpha-beta
                    if(!marcouPonto(oponenteCaracter, (*raizIA)->tab) &&
                       !marcouPonto(meuCaracter, (*raizIA)->tab) &&
                       !deuVelha((*raizIA)->tab)){

                        //chamar função recursivamente para cada nó filho criado
                        criarArvore(meuCaracter, oponenteCaracter, &(*raizIA)->filhos[(2*i)+j+i], !minhaVez);

                       }else{
                            //senão o filho será nulo naquela posição
                            (*raizIA)->filhos[(2*i)+j+i] = NULL;
                        }
                }else{
                    //senão tiver espaço em branco, o filho será nulo naquela posição
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

int encontraFolhaArvore(struct noIA** no){

    if((*no) != NULL){

        bool folha = true;
        //testar se os nós filhos são folhas
        for(int k=0; k<9; k++){
            if((*no)->filhos[k]!=NULL){
                folha = false;
                break;
            }
        }

        //se for folha, retornar o valor do nó
        if(folha){
            return (*no)->valor;

        //senão, chamar recursivamente para os nós filhos do nó atual
        }else{
            for(int k=0; k<9; k++){
                if((*no) != NULL){
                    (*no)->valor += encontraFolhaArvore(&(*no)->filhos[k]);
                }
            }
            return (*no)->valor;
        }
	}else{
        return 0;
	}
}

//função para vezDoPlayer de acordo com a heurística
int melhorJogada(struct noIA** no, bool somarHeuristica){

    int melhorFilho = -1;
    int maiorHeuristica = -9999999;

    //percorrer todos os nós filhos do nó raiz
    for(int i=0; i<9; i++){
        
        //se o nó filho não for nulo
        if((*no)->filhos[i] != NULL){
            
            if(somarHeuristica){
                (*no)->filhos[i]->valor += encontraFolhaArvore(&(*no)->filhos[i]);
            }
            
            //decidir a melhor jogada
            //se for o primeiro nó filho, ou se a heurística do nó atual for maior que a heurística do melhor nó filho atual
            if((*no)->filhos[i]->valor > maiorHeuristica){
                maiorHeuristica = (*no)->filhos[i]->valor;
                melhorFilho = i;
            }
        }
    }

    //retornar a posição do melhor nó filho
    return melhorFilho;
}

//função para exclusão de nós da árvore
void excluirArvore(struct noIA** no){

    //se o nó não for nulo
    if((*no) != NULL){

        //percorrer todos os nós filhos do nó raiz
        for(int k=0; k<9; k++){

            excluirArvore(&(*no)->filhos[k]);

        }
        
        //liberar memória do nó
        free(*no);
        //free((*no));
            
	}
}

//função responsável por decidir qual a melhor jogada a seguir
void IA(char meuCaracter, char oponenteCaracter, char t[3][3]){
    
    int melhorFilho = -1;
    struct noIA* auxFree = NULL;

    if(raizIA==NULL){
        //alocando a árvore usada pela IA
        raizIA = (struct noIA*)malloc(sizeof(struct noIA));

        //passando tabuleiro principal para o tabuleiro da árvore
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                raizIA->tab[i][j] = t[i][j];
            }
        }

        //criar a árvore
        criarArvore(meuCaracter, oponenteCaracter, &raizIA, true);

        //calcular valor heurístico de cada nó da árvore
        calcHeuristico(meuCaracter, oponenteCaracter, &raizIA);

        //somar heuristica até os filhos da raiz
        melhorFilho = melhorJogada(&raizIA, true);
        
    }else{

        //guardo a raiz atual para libearar memória depois
        auxFree = raizIA;

        //atualizar jogada do player na árvore...
        bool achouJogadaAtual;
        int c;

        //percorrer todos os nós filhos do nó raiz
        for(c=0; c<9; c++){

            //se o nó filho não for nulo
            if(raizIA->filhos[c]){

                //se o nó filho atual for igual ao tabuleiro atual
                achouJogadaAtual = true;

                //comparar tabuleiro atual com tabuleiro do nó filho
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){

                        //se o nó filho atual for diferente do tabuleiro atual
                        if(raizIA->filhos[c]->tab[i][j] != t[i][j]){

                            //não encontrou jogada atual
                            achouJogadaAtual = false;
                        }
                    }
                }
                
                if(achouJogadaAtual){
                    break;
                }
            }
        }

        if(achouJogadaAtual){
            
            //excluir os nós da árvore, exceto o nó melhor jogada
            for(int i=0; i<9; i++){
                if(auxFree->filhos[i] != NULL){
                    if(i!=c){
                        excluirArvore(&auxFree->filhos[i]);
                    }
                }
            }
			
			//atualiza a raiz da árvore
            raizIA = raizIA->filhos[c];
        }else{
            printf("Erro fatal!");
        }

        melhorFilho = melhorJogada(&raizIA, false);


    }

    //se IA ganhar logo na próxima jogada
    for(int i=0; i<9; i++){
        if(raizIA->filhos[i] != NULL){

            if(marcouPonto(meuCaracter, raizIA->filhos[i]->tab)){
                raizIA->filhos[i]->valor += 1000;
                melhorFilho = i;
            }
        }
    }

    

    //printf("\nmelhor filho para vezDoPlayer = %d", melhorFilho);

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){

            //ver onde está a jogada que a IA deve fazer
            if(raizIA->filhos[melhorFilho]->tab[i][j] != t[i][j]){

                //marcar a jogada
                t[i][j] = raizIA->filhos[melhorFilho]->tab[i][j];
                //i=j=3;
            }
        }
    }

    raizIA = raizIA->filhos[melhorFilho];
    
}







