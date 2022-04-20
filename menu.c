//
// Created by pedro on 15/04/2022.
//
#include <stdio.h>
#include "menu.h"

int menu(){
    int res,opc;
    do {
        printf("1-Novo Jogo\n");
        printf("2-Carregar Jogo\n");
        printf("9-Ajuda\n");
        res = scanf("%d",&opc);
        fflush(stdin);
    }while(res == 0);
    return opc;
}

int menu_jogo(){
    int res,opc;
    do {
        printf("1-Jogar contra um humano\n");
        printf("2-Jogar com o computador\n");
        res = scanf("%d",&opc);
        fflush(stdin);
    }while(res == 0);
    return opc;
}