// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// José Pedro Sousa Almeida-a2020141980
#include <stdio.h>
#include "menu.h"

int menu(){
    int res,opc;
    do {
        printf("1-Jogar\n");
        printf("2-Regras\n");
        res = scanf("%d",&opc);
        fflush(stdin);
    }while(res == 0 || opc < 1 || opc > 2);
    return opc;
}

int menu_jogo(){
    int res,opc;
    do {
        printf("1-Jogar contra um humano\n");
        printf("2-Jogar contra o computador\n");
        res = scanf("%d",&opc);
        fflush(stdin);
    }while(res == 0 || opc < 1 || opc > 2);
    return opc;
}

int escolhe(){
    int res,num;

    do{
        printf("\nDeseja guardar a informacao do jogo?\n");
        printf("1-Sim\n");
        printf("2-Nao\n");
        res = scanf("%d",&num);
        fflush(stdin);
    }while(res == 0 || num < 1 || num > 2);
    return num;
}

int menu_jogada(){
    int opt,res;

    do{
        printf("\nQue acao deseja realizar?\n");
        printf("1-Jogar\n");
        printf("2-Ver jogadas anteriores (10 no maximo)\n");
        printf("3-Guardar jogo e sair\n");
        res = scanf("%d",&opt);
        fflush(stdin);
    }while(res == 0 || opt < 1 || opt > 3);
    return opt;
}

int menu_continua_jogo(){
    int res,num;
    do{
        printf("\nDeseja continuar o jogo anterior?\n");
        printf("1-Sim\n");
        printf("2-Nao\n");
        res = scanf("%d",&num);
        fflush(stdin);
    }while(res == 0 || num < 1 || num > 2);

    return num;
}

int menu_regras(){
    int res,num;
    printf("\n-------------------------------ULTIMATE TIC-TAC-TOC--------------------------------\n");
    printf("\n-O jogador inicial e definido aleatoriamente.\n");
    printf("\n-O jogador inicial escolhe em qual mini-tabuleiro dejesa iniciar o jogo\n");
    printf("\n-Na sua vez, cada jogador coloca a sua peca num dos 9 mini-tabuleiros.\n");
    printf("\n-Um jogador que faca 3 em linha num dos mini-tabuleiros ganha essa seccao.\n");
    printf("\n-Um jogador que ganhe 3 mini-tabuleiros em linha (no tabuleiro grande) ganha o jogo\n");
    printf("\n-A escolha do mini-tabuleiro em que se joga nao e livre, sendo determinada pela"
                   "\njogada anterior do adversario. A posicao escolhida pelo adversario identifica o "
                   "\nmini-tabuleiro onde deve ser continuado o jogo.\n");
    printf("\n-Verifica-se um empate se o jogo chegar ao final sem que nenhum dos jogadores"
                   "\nconsiga fazer 3 mini-tabuleiros em linha.\n");


    printf("\n-----------------------------------------------------------------------------------\n");
    do{

        printf("1-Voltar\n");
        res = scanf("%d",&num);
        fflush(stdin);
    }while(res == 0 || num !=1);

    return num;
}