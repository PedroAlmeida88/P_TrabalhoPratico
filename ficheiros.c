// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include "stdio.h"
#include "listas.h"
#include "ficheiros.h"
#include "matdin.h"
#include "jogo.h"

void guarda_lista_txt(pJogada p){
    char fileName[20];
    FILE *f;

    printf("Qual o nome que deseja atribuir ao ficheiro?");
    scanf("%20s",fileName);
    fflush(stdin);


    f = fopen(fileName,"wt");
    if(f==NULL){
        printf("Erro ao abrir o ficheiro");
        return;
    }else{
        while (p != NULL){
            fprintf(f,"%2d. O Jogador:%d jogou no tabuleiro:%d, na posicao:%d.\n", p->n_jogada, p->jogador, p->tabuleiro,p->posicao);
            p = p->prox;
        }

    }
    fclose(f);
}

void guarda_lista_bin(pJogada p,int n_jogadas,int tipo_jogo){
    int num_jogadas,modo_jogo; //modo_jogo == 0 -> jogador | modo_jogo == 1 -> bot
    num_jogadas = n_jogadas;
    modo_jogo = tipo_jogo;
    FILE *f;
    f = fopen("jogo.bin","wb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");
        return;
    }
    //escrever se está a jogar contra um jogador ou contra o computador
    fwrite(&modo_jogo,sizeof (int),1,f);

    //escrever o numero de jogadas no inicio do ficheiro
    fwrite(&num_jogadas,sizeof (int),1,f);

    while(p != NULL){
        fwrite(p,sizeof (Jogada),1,f);
        p= p->prox;
    }
    fclose(f);

}

char ***reconstroi_tabuleiro(char *filename,char **vencedores){
    int num_jogadas,x,y,modo_jogo;
    char ***mat;
    mat = criaTabuleiro(9,3,3);
    FILE *f;
    Jogada a;
    f = fopen(filename,"rb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");//manda o tabuleiro vazio
        return mat;
    }
    //le o modo de jogo(contra jogador ou contra o computador)
    fread(&modo_jogo,sizeof (int),1,f);

    //le o num de jogadas
    fread(&num_jogadas,sizeof (int),1,f);
    //reconstroi tabuleiro
    while (fread(&a,sizeof (Jogada),1,f)==1){
        converte_posicao(a.posicao,&x,&y);

        if(a.jogador == 1)
            setPos(mat, a.tabuleiro - 1, x, y, 'X');
        else
            setPos(mat, a.tabuleiro - 1, x, y, 'O');

        //verificar se alguem ganhou um mini-tab
        if(modo_jogo == 0)
            ganha_mini_tabuleiro(mat,a.tabuleiro,3,a.jogador,vencedores);
        else if(modo_jogo != 0){
            if(a.jogador == 2) {
                ganha_mini_tabuleiro(mat, a.tabuleiro, 3, 4, vencedores);//jogador 4 == bot
            }else{
                ganha_mini_tabuleiro(mat, a.tabuleiro, 3, 1, vencedores);
            }
        }

    }
    fclose(f);
    return mat;
}

void ultima_jogada(char *filename,int *mini_tab,int *jogador,int *n_jogada){
    int num_jogadas,modo_jogo;
    FILE *f;
    Jogada a;
    f = fopen(filename,"rb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");
        return;
    }
    //le o modo de jogo(contra jogador ou contra o computador)
    fread(&modo_jogo,sizeof (int),1,f);

    //le o num de jogadas
    fread(&num_jogadas,sizeof (int),1,f);
    *n_jogada = num_jogadas + 1;
    //reconstroi tabuleiro
    while (fread(&a,sizeof (Jogada),1,f)==1){
        if(a.n_jogada == num_jogadas){ //encontrar a ultima jogada
            *jogador = a.jogador;
            *mini_tab = a.posicao;
        }
    }
    fclose(f);
}

int verifica_existencia_ficheiro(char *filename) {
    FILE *f;
    f = fopen(filename, "rb");
    if (f != NULL) { //se der null o ficheiro n existe.Caso contrário existe.
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

pJogada reconstroi_lista(char *filename,pJogada p){
    int num_jogadas,modo_jogo;
    Jogada a;
    FILE *f;
    f = fopen(filename,"rb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");
        return p;
    }
    //le o modo de jogo(contra jogador ou contra o computador)
    fread(&modo_jogo,sizeof (int),1,f);

    fread(&num_jogadas,sizeof (int),1,f);//le num de jogadas
    p = NULL;

    while (fread(&a,sizeof (Jogada),1,f)==1) {
        p = insere_final(p, a.n_jogada, a.tabuleiro, a.posicao, a.jogador);
    }
    fclose(f);
    return p;
}

void le_lista_bin(pJogada p){
    FILE *f;
    int num_jogadas,modo_jogo;
    f = fopen("jogo.bin","rb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");
        return;
    }

    fread(&modo_jogo,sizeof (int),1,f);
    if(modo_jogo == 0)
        printf("Jogo com um jogador\n");
    else
        printf("Jogo com o computador\n");


    fread(&num_jogadas,sizeof (int),1,f);
    printf("\nNum de jogadas->%d\n",num_jogadas);
    while(p != NULL){
        fread(p,sizeof (Jogada),1,f);
        printf("\nJogada %d, jogador %d,tab %d, pos %d.",p->n_jogada,p->jogador,p->tabuleiro,p->posicao);
        p= p->prox;
    }

    fclose(f);
}

int modo_jogo(){
    FILE *f;
    int modo_jogo;
    f = fopen("jogo.bin","rb");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro");
        return -1;
    }
    fread(&modo_jogo,sizeof (int),1,f);
    fclose(f);
    return modo_jogo;
}