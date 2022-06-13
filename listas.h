// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980

#ifndef TP_LISTAS_H
#define TP_LISTAS_H

typedef struct jogada Jogada, *pJogada;

struct jogada{
    int n_jogada;   //numero da jogada
    int tabuleiro;  //tabuleiro onde o jogador jogou
    int posicao;    //posição onde o jogador jogou
    int jogador;    //jogador que jogou
    pJogada prox;   //ponteiro para a próxima jogada
};

pJogada insere_final(pJogada p,int n_jogada,int tab, int pos, int jogador);
void mostra_n_jogadas_anteriores(pJogada p,int n,int n_jogada);
void mostra_lista(pJogada p);
void liberta_lista(pJogada p);
#endif //TP_LISTAS_H
