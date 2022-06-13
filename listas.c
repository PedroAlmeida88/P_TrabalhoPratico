// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include <stdlib.h>
#include <stdio.h>
#include "listas.h"

pJogada insere_final(pJogada p,int n_jogada,int tab, int pos, int jogador){
    pJogada novo,aux;
    novo = malloc(sizeof (Jogada));
    if(novo == NULL){
        printf("Erro na alocação de memoria\n");
        return p;
    }
    //preencher infomacao
    novo->n_jogada = n_jogada;
    novo->jogador = jogador;
    novo->posicao = pos;
    novo->tabuleiro = tab;
    novo->prox = NULL;

    if(p == NULL){//caso a lista esteja vazia
        p = novo;
    }else{
        aux = p;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    return p;
}

void mostra_n_jogadas_anteriores(pJogada p,int n,int n_jogada){
    int start = n_jogada - n; //para saber onde começo a ler a lista
    if(n >= n_jogada) {//caso o numero de jogadar a ver for maior que o numero de jogadas já efetuadas
        printf("Ainda nao foram efetudas %d jogadas!\n",n);
        while (p != NULL){
            printf("%2d. O Jogador:%d jogou no tabuleiro:%d, na posicao:%d.\n", p->n_jogada, p->jogador, p->tabuleiro,p->posicao);
            p = p->prox;
        }
        return;
    }
    while(p != NULL && p->n_jogada != start)
        p = p->prox;
    if(p != NULL){ //encontra o start
        while (p != NULL) {
            printf("%2d. O Jogador:%d jogou no tabuleiro:%d, na posicao:%d.\n", p->n_jogada, p->jogador, p->tabuleiro,p->posicao);
            p = p->prox;
        }
    }
    else
        printf("Erro no num da jogada\n");


}

void liberta_lista(pJogada p){
    pJogada aux;
    while (p != NULL){
        aux = p;
        p = p->prox;
        free(aux);
    }
}

void mostra_lista(pJogada p){
    while (p != NULL){
        printf("%2d. Jogador:%d\tTabuleiro:%d\tPosicao:%d\n",p->n_jogada,p->jogador, p->tabuleiro, p->posicao);
        p = p->prox;
    }
}
